#include "Bar.h"
#include "App.h"
#include "util.h"
#include <algorithm>

Bar::Bar(int x, int y, int w, int h, float (*getter)(), SDL_Color backColor, SDL_Color foreColor)
    :Object(x, y)
{
    this->w = w;
    this->h = h;
    this->getter = getter;
    this->backColor = backColor;
    this->foreColor = foreColor;
}

Bar::~Bar()
{

}

void Bar::draw()
{
    SDL_Rect rect = {this->x, this->y, this->w, this->h};

    renderRect(rect, backColor);

    rect.x += 2;
    rect.y += 2;
    rect.w -= 4;
    rect.h -= 4;

    if (this->getter)
    {
        rect.w = std::min<int>(std::max<int>(1, rect.w * getter()), rect.w);
    }

    renderRect(rect, foreColor);

    rect.x += rect.w - 2;
    rect.w = 2;
    rect.y -= 1;
    rect.h += 2;

    renderRect(rect, white * 0.65f + foreColor);
}
