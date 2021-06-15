/**
 * 2021-06-12
 * BreakOut Game with SDL2
 *
 * YeJun, Jung (yejun614@naver.com)
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
using namespace std;

#include "game.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 700;

int main() {
  // SDL Initialize
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return 1;
  }

  // SDL Create Window
  SDL_Window *window = SDL_CreateWindow("BreakOut Game",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);

  if (window == nullptr) {
    cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;

    SDL_Quit();
    return 1;
  }

  // Get Icon Image
  SDL_Surface *icon = IMG_Load("assets/icon/icon.png");
  SDL_SetWindowIcon(window, icon);

  // SDL Create Renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
  }

  // SDL TTF Initalize
  TTF_Init();

  // Game Start
  Game game(renderer);
  game.play();

  // Clearning Up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  TTF_Quit();
  Mix_Quit();

  return 0;
}
