#pragma once
#include "Object.h"
#include "Image.h"

class Label : public Object
{
public:
    Label(int x, int y, int w, const std::string& text, SDL_Color color);
    virtual ~Label();

    virtual void draw();

    void renderText();

    int w;
    std::string text;
    SDL_Color color;
    Image image;
};
