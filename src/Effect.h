#pragma once
#include "Image.h"
#include <vector>

class Effect
{
public:
    Effect(Image* image, int cols, int rows, float fps);

    void render(int x, int y, int frame);

    Image* image;
    std::vector<SDL_Rect> frames;
    int frameCount, cols, rows;
    int frameW, frameH;
    float fps;
};
