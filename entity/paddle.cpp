#include "paddle.h"

Paddle::Paddle(SDL_Renderer *_renderer, float _speed) : renderer(_renderer), speed(_speed) {
  width = 100.0f;
  height = 5.0f;

  // Get window width size.
  SDL_GetRendererOutputSize(renderer, &screen_width, NULL);
}

void Paddle::draw() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  draw_fillRect(renderer, position.x, position.y, width, height);
}

void Paddle::moveLeft() {
  position.x -= speed;

  // Collision Check
  if (position.x < 0) {
    position.x = 0;
  }
}

void Paddle::moveRight() {
  position.x += speed;

  // Collision Check
  if (position.x+width > screen_width) {
    position.x = screen_width - width;
  }
}

void Paddle::setPosition(float x, float y) {
  position.x = x;
  position.y = y;
}

void Paddle::setWidth(float w) {
  width = w;
}
