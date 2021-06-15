#include "shapes.h"

void draw_rect(SDL_Renderer *renderer, float x, float y, float width, float height) {
  SDL_FPoint points[5] = {
    {x, y},
    {x+width, y},
    {x+width, y+height},
    {x, y+height},
    {x, y}
  };

  SDL_RenderDrawLinesF(renderer, points, 5);
}

void draw_fillRect(SDL_Renderer *renderer, float x, float y, float width, float height) {
  for (float t=0; t<height; t+=SHAPE_DENSITY_RATE) {
    SDL_RenderDrawLineF(renderer, x, y+t, x+width, y+t);
  }
}

void draw_circle(SDL_Renderer *renderer, float x, float y, float radius) {
  SDL_FPoint point;

  for (float t=0; t<2*M_PI; t+=SHAPE_DENSITY_RATE) {
    point.x = x + (cos(t) * radius);
    point.y = y + (sin(t) * radius);

    SDL_RenderDrawPointF(renderer, point.x, point.y);
  }
}

void draw_fillCircle(SDL_Renderer *renderer, float x, float y, float radius) {
  while (radius > 0) {
    draw_circle(renderer, x, y, radius);

    radius -= SHAPE_DENSITY_RATE*50;
  }
}
