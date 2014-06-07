#include "Label.h"

Label::Label(int x, int y, int w, const std::string& text, SDL_Color color)
      :Object(x, y)
{
    this->w = w;
    this->text = text;
    this->color = color;
    this->renderText();
}

Label::~Label()
{

}

void Label::draw()
{
    this->image.render(this->x, this->y);
}

void Label::renderText()
{
	this->image.renderText(this->text, this->color, this->w);
}
