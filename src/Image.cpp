#include "Image.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "App.h"

Image::Image()
{
    this->texture = nullptr;
    this->w = 0;
    this->h = 0;
}

Image::~Image()
{
    if (this->texture)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

bool Image::loadFromFile(const std::string& path)
{
    if (this->texture)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Error loading image: " << TTF_GetError() << std::endl;
    }
    else
    {
        this->w = surface->w;
        this->h = surface->h;

        this->texture = SDL_CreateTextureFromSurface(App::renderer, surface);
        if (!this->texture)
        {
            std::cerr << "Error converting surface: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(surface);
    }

    return (this->texture != nullptr);
}

bool Image::renderText(const std::string& text, SDL_Color color, int width)
{
    if (this->texture)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    SDL_Surface* surface = nullptr;
    if (width)
    {
        surface = TTF_RenderText_Blended_Wrapped(App::db.font, text.c_str(), color, width);
    }
    else
    {
        surface = TTF_RenderText_Blended(App::db.font, text.c_str(), color);
    }

    if (!surface)
    {
        std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
    }
    else
    {
        this->w = surface->w;
        this->h = surface->h;

        this->texture = SDL_CreateTextureFromSurface(App::renderer, surface);
        if (!this->texture)
        {
            std::cerr << "Error converting surface: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(surface);
    }

    return (this->texture != nullptr);
}

void Image::render(int x, int y)
{
    if (!this->texture)
    {
        std::cerr << "Error rendering: Null texture" << std::endl;
    }
    else
    {
        SDL_Rect src = {0, 0, this->w, this->h};
        SDL_Rect dst = {x, y, this->w, this->h};
        SDL_RenderCopy(App::renderer, this->texture, &src, &dst);
    }
}

void Image::renderSubrect(int x, int y, const SDL_Rect& rect)
{
    if (!this->texture)
    {
        std::cerr << "Error rendering: Null texture" << std::endl;
    }
    else
    {
        SDL_Rect dst = {x, y, rect.w, rect.h};
        SDL_RenderCopy(App::renderer, this->texture, &rect, &dst);
    }
}
