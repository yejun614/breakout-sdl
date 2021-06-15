#ifndef SHAPES_H
#define SHAPES_H

#include <SDL2/SDL.h>
#include <cmath>

static float SHAPE_DENSITY_RATE = 0.01f;

void draw_rect(SDL_Renderer *renderer, float x, float y, float width, float height);
void draw_fillRect(SDL_Renderer *renderer, float x, float y, float width, float height);

void draw_circle(SDL_Renderer *renderer, float x, float y, float radius);
void draw_fillCircle(SDL_Renderer *renderer, float x, float y, float radius);

#endif // SHAPES_H