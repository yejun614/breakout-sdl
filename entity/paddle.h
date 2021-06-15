#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#include "../utility/shapes.h"

class Paddle {
  public:
    SDL_FPoint position;
    float width;
    float height;

    Paddle(SDL_Renderer *_renderer, float _speed);

    void draw();
    
    void moveLeft();
    void moveRight();

    void setPosition(float x, float y);
    void setWidth(float w);

  private:
    SDL_Renderer *renderer;
    float speed;
    int screen_width;
};

#endif // PADDLE_H