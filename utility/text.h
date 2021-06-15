#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <sstream>

class Text {
  public:
    Text(SDL_Renderer *_renderer, std::string font_name, int font_size);
    
    void setPosition(int x, int y);
    void setAlign(short flag);
    void setColor(int r, int g, int b, int a=255);

    void print(std::string str);
    void print_lines(std::string str, int line_height);
    void close();

  private:
    SDL_Renderer *renderer;
    SDL_Point position;
    SDL_Color color;
    SDL_Rect rect;
    TTF_Font *font;
    short align;
};

#endif //TEXT_H