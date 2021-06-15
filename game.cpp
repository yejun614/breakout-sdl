#include "game.h"

Game::Game(SDL_Renderer *_renderer) :
  renderer(_renderer),
  ball(renderer, 10.0f),
  paddle(renderer, 20.0f),
  text(renderer, "assets/fonts/D2Coding.ttf", 25),
  text_bold(renderer, "assets/fonts/D2CodingBold.ttf", 25)
{
  is_show_fps = false;
  is_play = false;

  key_left = false;
  key_right = false;

  // Set FPS
  FPS = 60.0f;

  // Get screen size.
  SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);

  // Init blocks vector.
  block_size = 49;
  blocks = (Block*)malloc(sizeof(Block) * block_size);

  // Initialize Audio
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 500);

  // Load audio files.
  audio_block = Mix_LoadWAV("assets/audio/523762__matrixxx__select-granted-05.wav");
  audio_paddle = Mix_LoadWAV("assets/audio/515823__matrixxx__select-granted-04.wav");
  audio_start = Mix_LoadWAV("assets/audio/523763__matrixxx__select-granted-06.wav");
  audio_gameover = Mix_LoadMUS("assets/audio/364929__jofae__game-die.wav");
  audio_gameclear = Mix_LoadMUS("assets/audio/518308__mrthenoronha__world-clear-8-bit.wav");
}

void Game::init() {
  is_gameover = false;

  timer = 3;
  fps_ticks = SDL_GetTicks();
  timer_ticks = SDL_GetTicks();

  // Set ball position.
  ball.setPosition(screen_width/2, screen_height/2);
  // Set ball initial direction.
  ball.move(1, -1);

  // Set paddle position.
  paddle.setPosition(screen_width/2-50, screen_height-50);

  // Set block arguments.
  SDL_FPoint position = {0, 50};
  SDL_Color *color;

  // Vector index
  int index = 0;

  // Create blocks.
  for (int y=0; y<7; y++) {
    position.x = 50;

    // Set color by lines
    color = (SDL_Color*)(RANDOM_BLOCK_COLORS+y);

    for (int x=0; x<7; x++) {
      // Add new block.
      blocks[index++] = Block(renderer, position, *color);

      position.x += 100;
    }
    position.y += 20;
  }

  // Set block count.
  block_count = block_size;

  // Play start audio
  Mix_PlayChannel(-1, audio_start, 0);
}

void Game::play() {
  // Initalize the game.
  init();

  // Set game play flag.
  is_play = true;

  while (is_play) {
    // Game loop
    update();

    // Check Events
    event_listener();
  }
}

void Game::stop() {
  // Close the fonts
  text.close();
  text_bold.close();

  // Free the audio files.
  Mix_FreeChunk(audio_block);
  Mix_FreeChunk(audio_paddle);
  Mix_FreeChunk(audio_start);
  Mix_FreeMusic(audio_gameover);

  // Free memory
  free(blocks);

  // Game stop
  is_play = false;
}

void Game::draw_entities() {
  // Draw a ball.
  ball.draw();

  // Draw a paddle.
  paddle.draw();

  // Draw blocks.
  for (int i=0; i<block_size; i++) {
    blocks[i].draw();
  }
}

void Game::show_fps() {
  // Show FPS
  text.setPosition(10, 10);
  text.setAlign(-1);
  text.print(std::to_string(SDL_GetTicks() - fps_ticks));
}

void Game::show_timer() {
  text.setPosition(screen_width/2, screen_height/2-50);
  text.setAlign(0);
  text.print(std::to_string(timer));
}

void Game::show_gameover() {
  // Game Over Message
  text.setPosition(screen_width/2, screen_height/2 - (35*3));
  text.setAlign(0);
  text.print_lines("Game Over!\nR - Restart\nESC - Exit the game.", 35);
}

void Game::show_gameclear() {
  // Game Clear Message
  text.setPosition(screen_width/2, screen_height/2 - (35*2));
  text.setAlign(0);
  text.print_lines("- CONGRATURATION -\nYOU ARE WINNER!", 35);
}

void Game::display() {
  if (is_show_fps) show_fps();
  
  if (block_count <= 0) {
    show_gameclear();
  } else if (is_gameover) {
    show_gameover();
  }

  // Start timer
  if (timer > 0) {
    show_timer();

    // Timer
    if (SDL_GetTicks()-timer_ticks >= 1000) {
      timer --;
      timer_ticks = SDL_GetTicks();
    }
  }
}

void Game::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
}

void Game::update() {
  // FPS
  if (SDL_GetTicks()-fps_ticks < (1000/FPS)) return;
  fps_ticks = SDL_GetTicks();

  // Paddle Move
  if (key_right) paddle.moveRight();
  if (key_left)  paddle.moveLeft();

  // Check paddle collision with a ball.
  if (ball.collision(paddle.position, paddle.width, paddle.height, false)) {
    // Play audio
    Mix_PlayChannel(-1, audio_paddle, 0);

    // Set position
    SDL_FPoint position = ball.getPosition();
    ball.setPosition(position.x, position.y-5);

    // Ball flipping
    ball.flip(false, true);
  }

  for (int i=0; i<block_size; i++) {
    Block *block = &blocks[i];

    // Check blocks collision with a ball.
    if (!block->is_broken && ball.collision(block->position, block->width, block->height)) {
      // Play audio
      Mix_PlayChannel(-1, audio_block, 0);

      // Check a block broken flag.
      block->is_broken = true;

      // Count
      block_count --;

      // Stop checking.
      break;
    }
  }

  if (timer <= 0 && !is_gameover) {
    // Update ball position.
    is_gameover = ball.update();

    // Play gameover audio
    if (is_gameover) Mix_PlayMusic(audio_gameover, 1);
  }

  if (block_count <= 0 && !is_gameover) {
    // Game Clear!
    // Play audio
    Mix_PlayMusic(audio_gameclear, 1);

    // Set gameover
    is_gameover = true;
  }

  // Clear Screen
  clear();

  // Display
  display();

  // Draw
  draw_entities();
  SDL_RenderPresent(renderer);
}

void Game::event_listener() {
  while (SDL_PollEvent(&event)) {
    // Press 'X' button on window
    if (event.type == SDL_QUIT) {
      // Stop
      stop();
    }

    // Keydown
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
          // EXIT
          stop();
          break;

        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          key_left = true;
          break;

        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          key_right = true;
          break;

        case SDL_SCANCODE_R:
          // Restart the game.
          init();
          break;

        default:
          break;
      }
      
    } else if (event.type == SDL_KEYUP) {
      switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          key_left = false;
          break;

        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          key_right = false;
          break;

        default:
          break;
      }
    }
  }
}

