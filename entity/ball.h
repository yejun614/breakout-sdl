#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <cmath>

#include "../utility/shapes.h"

class Ball {
  public:
    Ball(SDL_Renderer *_renderer, float _speed);

    void move(float x, float y);
    void flip(bool x, bool y);
    bool update();
    void draw();

    void setPosition(float x, float y);
    SDL_FPoint getPosition();

    bool collision(SDL_FPoint rect, float width, float height, bool isFlip=true);

  private:
    SDL_Renderer *renderer;
    SDL_FPoint position;
    SDL_FPoint direction;
    const float size = 5.0f;
    float speed;
    int screen_width;
    int screen_height;
};

#endif // BALL_H