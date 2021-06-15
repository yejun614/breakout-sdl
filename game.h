#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
#include <cstdlib>
#include <iostream>

#include "entity/ball.h"
#include "entity/paddle.h"
#include "entity/block.h"

#include "utility/text.h"

static const int RANDOM_BLOCK_COLOR_SIZE = 7;
static const SDL_Color RANDOM_BLOCK_COLORS[] = {
  { 255, 0, 0, 255 },
  { 255, 94, 0, 255 },
  { 255, 191, 0, 255 },
  { 72, 255, 0, 255 },
  { 0, 26, 255, 255 },
  { 85, 0, 255, 255 },
  { 174, 0, 255, 255 }
};

class Game {
public:
  Game(SDL_Renderer *_renderer);

  void init();
  void play();
  void stop();

private:
  void draw_entities();

  void show_fps();
  void show_timer();
  void show_gameover();
  void show_gameclear();

  void display();
  void clear();
  void update();
  void event_listener();

  int fps_ticks;
  int timer_ticks;
  int timer;

  bool is_show_fps;
  float FPS;

  int screen_width;
  int screen_height;

  bool key_left;
  bool key_right;

  bool is_play;
  bool is_gameover;

  SDL_Renderer *renderer;
  SDL_Event event;

  Ball ball;
  Paddle paddle;
  Block *blocks;
  int block_size;
  int block_count;

  Text text;
  Text text_bold;

  Mix_Chunk *audio_block;
  Mix_Chunk *audio_paddle;
  Mix_Chunk *audio_start;
  Mix_Music *audio_gameover;
  Mix_Music *audio_gameclear;
};

#endif // GAME_H