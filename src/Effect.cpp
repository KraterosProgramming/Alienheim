#include "Effect.h"

Effect::Effect(Image* image, int cols, int rows, float fps)
{
    this->image = image;
    this->frameCount = cols * rows;
    this->cols = cols;
    this->rows = rows;
    this->frameW = image->w / cols;
    this->frameH = image->h / rows;
    this->fps = fps;

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            SDL_Rect frame = {this->frameW * c, this->frameH * r, this->frameW, this->frameH};
            this->frames.push_back(frame);
        }
    }
}

void Effect::render(int x, int y, int frame)
{
    this->image->renderSubrect(x, y, this->frames[frame]);
}
