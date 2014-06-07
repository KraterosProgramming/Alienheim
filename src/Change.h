#pragma once
#include <SDL2/SDL.h>
#include <string>

class Change
{
public:
    Change();
    virtual ~Change() { }

    virtual void perform() = 0;
    virtual std::string getString() = 0;
    virtual SDL_Color getColor() = 0;
};
