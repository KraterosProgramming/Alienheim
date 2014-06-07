#include "Picture.h"

Picture::Picture(int x, int y, Image* image)
        :Object(x, y)
{
    this->image = image;
}

Picture::~Picture()
{
    // do not delete image
}

void Picture::draw()
{
    if (this->image)
    {
        this->image->render(x, y);
    }
}
