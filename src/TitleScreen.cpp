#include "TitleScreen.h"
#include "App.h"
#include <iostream>

const Uint32 TitleScreen::duration = 3500;
const Uint32 TitleScreen::fadeDuration = 500;

TitleScreen::TitleScreen() : Scene()
{
    this->picture = new Picture(0, 0, App::db.images["title"]);
    this->objects[BACKGROUND].push_back(this->picture);
}

void TitleScreen::open()
{
    this->startTime = SDL_GetTicks();
}

void TitleScreen::update()
{
    if (SDL_GetTicks() - startTime >= duration)
    {
        App::changeScene("Main menu");
    }
    else
    {
        Uint8 mod = TitleScreen::opacity(SDL_GetTicks() - startTime);
        SDL_SetTextureColorMod(this->picture->image->texture, mod, mod, mod);
    }
}

void TitleScreen::takeEvent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
    {
        App::changeScene("Main menu");
    }
}

Uint8 TitleScreen::opacity(Uint32 t)
{
    if (t < TitleScreen::fadeDuration)
    {
        return t * 255 / TitleScreen::fadeDuration;
    }
    else if (t < TitleScreen::duration - TitleScreen::fadeDuration)
    {
        return 255;
    }
    else
    {
        return 255 - (t % TitleScreen::fadeDuration) * 255 / TitleScreen::fadeDuration;
    }
}
