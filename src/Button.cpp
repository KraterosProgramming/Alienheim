#include "Button.h"
#include "App.h"
#include <iostream>

SDL_Color Button::color = {43, 41, 71, 255};

Button::Button(int x, int y, const std::string& text, Behavior* behavior)
       :Object(x, y)
{
    this->enable = true;
    this->text.renderText(text, Button::color, 0);
    this->behavior = behavior;
    this->over = false;
    this->down = false;
}

Button::~Button()
{
    if (this->behavior)
    {
        delete this->behavior;
        this->behavior = nullptr;
    }
}

void Button::draw()
{
    if (!enable)
    {
        App::buttonDisable->render(this->x, this->y);
    }
    else
    {
        bool over = App::mouseX > this->x && App::mouseX < this->x + App::buttonNormal->w &&
                    App::mouseY > this->y && App::mouseY < this->y + App::buttonNormal->h;
        bool down = App::mouseButton & SDL_BUTTON_LMASK;

        if (this->down && !down)
        {
            this->click();
        }

        if (!over)
        {
            App::buttonNormal->render(this->x, this->y);
        }
        else
        {
            SDL_SetCursor(App::db.cursors["hand"]);

            if (!down)
            {
                App::buttonOver->render(this->x, this->y);
            }
            else
            {
                App::buttonDown->render(this->x, this->y);
            }
        }

        this->over = over;
        this->down = over && down;
    }

    this->text.render(this->x + (App::buttonNormal->w - this->text.w) / 2, this->y);
}

void Button::click()
{
    if (this->enable)
    {
        Mix_PlayChannel(-1, App::db.sounds["click"], 0);
        if (this->behavior)
        {
            this->behavior->call();
        }
    }
}
