#pragma once
#include <SDL2/SDL.h>

class Object
{
public:
    Object(int x, int y);
    virtual ~Object();

    virtual void draw() = 0;

    bool dead;
    int x, y;
};
