#include "text.h"

Text::Text(SDL_Renderer *_renderer, std::string font_name, int font_size) : renderer(_renderer) {
  // Load a font.
  font = TTF_OpenFont(font_name.c_str(), font_size);

  // Set default position.
  setPosition(0, 0);

  // Set text align to left.
  // -1: Left, 0: Center, 1: Right
  setAlign(-1);

  // Set default color to white.
  setColor(255, 255, 255, 255);
}

void Text::setPosition(int x, int y) {
  position.x = x;
  position.y = y;
}

void Text::setAlign(short flag) {
  align = flag;
}

void Text::setColor(int r, int g, int b, int a) {
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
}


void Text::print(std::string str) {
  SDL_Surface *surface = TTF_RenderText_Solid(font, str.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  // Y Position is fixed.
  rect.y = position.y;

  switch (align) {
    case 1:
      // Right
      rect.x = position.x + surface->w;
      break;

    case 0:
      // Centered
      rect.x = position.x - (surface->w/2);
      break;

    case -1:
    default:
      // Left (Default)
      rect.x = position.x;
      break;
  }

  rect.w = surface->w;
  rect.h = surface->h;

  SDL_RenderCopy(renderer, texture, NULL, &rect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void Text::print_lines(std::string str, int line_height) {
  std::stringstream ss(str);
  std::string line;

  while (getline(ss, line)) {
    // Set y position.
    position.y += line_height;

    // Print text.
    print(line);
  }
}

void Text::close() {
  // Close the font.
  TTF_CloseFont(font);
}
