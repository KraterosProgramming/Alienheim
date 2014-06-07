#pragma once
#include <SDL2/SDL.h>
#include <string>

class Image
{
public:
    Image();
    ~Image();

    bool loadFromFile(const std::string& path);
    bool renderText(const std::string& text, SDL_Color color, int width);

    void render(int x, int y);
    void renderSubrect(int x, int y, const SDL_Rect& rect);

    SDL_Texture* texture;
    int w, h;
};
