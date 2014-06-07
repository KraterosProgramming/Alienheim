#pragma once
#include "Object.h"
#include "Image.h"
#include "Behavior.h"

class Button : public Object
{
public:
    static SDL_Color color;

    Button(int x, int y, const std::string& text, Behavior* behavior);
    virtual ~Button();

    virtual void draw();

    virtual void click();

    bool enable;
    Image text;
    Behavior* behavior;
    bool over, down;
};

