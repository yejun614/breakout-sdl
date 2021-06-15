#include "block.h"

Block::Block(SDL_Renderer *_renderer, SDL_FPoint _position, SDL_Color _color) : renderer(_renderer), position(_position), color(_color) {
  width = 100.0f;
  height = 20.0f;

  is_broken = false;
}

void Block::draw() {
  if (is_broken) return;

  // Rectangle
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  draw_fillRect(renderer, position.x, position.y, width, height);

  // Outline(black)
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  draw_rect(renderer, position.x, position.y, width, height);
}
