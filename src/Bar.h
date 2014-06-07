#pragma once
#include "Object.h"

class Bar : public Object
{
public:
    Bar(int x, int y, int w, int h, float (*getter)(), SDL_Color backColor, SDL_Color foreColor);
    virtual ~Bar();

    virtual void draw();

    float (*getter)();
    int w, h;
    SDL_Color backColor, foreColor;
};
