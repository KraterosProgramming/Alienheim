#pragma once
#include "Object.h"
#include "Image.h"

class Picture : public Object
{
public:
    Picture(int x, int y, Image* image);
    virtual ~Picture();

    virtual void draw();

    Image* image;
};
