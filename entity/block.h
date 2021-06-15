#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>

#include "../utility/shapes.h"

class Block {
  public:
    SDL_FPoint position;
    SDL_Color color;
    float width;
    float height;
    bool is_broken;

    Block(SDL_Renderer *_renderer, SDL_FPoint _position, SDL_Color _color);
    void draw();

  private:
    SDL_Renderer *renderer;
};

#endif // BLOCK_H