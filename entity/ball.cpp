#include "ball.h"

Ball::Ball(SDL_Renderer *_renderer, float _speed) : renderer(_renderer), speed(_speed) {
  // Get screen size.
  SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
}

void Ball::move(float x, float y) {
  direction.x = x;
  direction.y = y;
}

void Ball::flip(bool x, bool y) {
  if (x) direction.x *= -1;
  if (y) direction.y *= -1;
}

bool Ball::update() {
  // Position
  position.x += direction.x * speed;
  position.y += direction.y * speed;

  // Check collision with window.
  if (position.x < 0) {
    direction.x *= -1;
    position.x = 0;
  } else if (position.x > screen_width) {
    direction.x *= -1;
    position.x = screen_width;
  }

  if (position.y < 0) {
    direction.y *= -1;
    position.y = 0;
  } else if (position.y > screen_height) {
    // Stop Moving
    direction.x = 0;
    direction.y = 0;

    // Game Over
    return true;
  }

  return false;
}

void Ball::draw() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  draw_fillCircle(renderer, position.x, position.y, size);
}

void Ball::setPosition(float x, float y) {
  position.x = x;
  position.y = y;
}

SDL_FPoint Ball::getPosition() {
  return position;
}

bool Ball::collision(SDL_FPoint rect, float width, float height, bool isFlip) {
  const float h_d1 = rect.x - (position.x+size);
  const float h_d2 = (position.x-size) - (rect.x+width);
  const float horizontal = abs(h_d1) < abs(h_d2) ? h_d1 : h_d2;

  const float v_d1 = rect.y - (position.y+size);
  const float v_d2 = (position.y-size) - (rect.y+height);
  const float vertical = abs(v_d1) < abs(v_d2) ? v_d1 : v_d2;

  if (horizontal > 0 || vertical > 0) {
    return false;
  }

  if (isFlip) {
    // Flipping
    if (position.x > rect.x && position.x < rect.x+width) {
      direction.y *= -1;
    } else {
      direction.x *= -1;
    }
  }

  return true;
}
