#include "util.h"
#include "App.h"

const SDL_Color white = {255, 255, 255, 255};
const SDL_Color lightGray = {191, 191, 191, 255};
const SDL_Color gray = {127, 127, 127, 255};
const SDL_Color darkGray = {63, 63, 63, 255};
const SDL_Color black = {0, 0, 0, 255};

const SDL_Color red = {255, 0, 0, 255};
const SDL_Color green = {0, 255, 0, 255};
const SDL_Color blue = {0, 0, 255, 255};

const SDL_Color cyan = {0, 255, 255, 255};
const SDL_Color magenta = {255, 0, 255, 255};
const SDL_Color yellow = {255, 255, 0, 255};

SDL_Color operator+(SDL_Color c1, SDL_Color c2)
{
    SDL_Color c;
    c.r = std::min<int>(255, c1.r + c2.r);
    c.g = std::min<int>(255, c1.g + c2.g);
    c.b = std::min<int>(255, c1.b + c2.b);
    c.a = std::min<int>(255, c1.a + c2.a);
    return c;
}

SDL_Color operator-(SDL_Color c1, SDL_Color c2)
{
    SDL_Color c;
    c.r = std::min<int>(0, c1.r - c2.r);
    c.g = std::min<int>(0, c1.g - c2.g);
    c.b = std::min<int>(0, c1.b - c2.b);
    c.a = std::min<int>(0, c1.a - c2.a);
    return c;
}

SDL_Color operator*(SDL_Color c1, SDL_Color c2)
{
    SDL_Color c;
    c.r = 1.0f/256.0f * c1.r * c2.r;
    c.g = 1.0f/256.0f * c1.g * c2.g;
    c.b = 1.0f/256.0f * c1.b * c2.b;
    c.a = 1.0f/256.0f * c1.a * c2.a;
    return c;
}

SDL_Color operator/(SDL_Color c1, SDL_Color c2)
{
    SDL_Color c;
    c.r = 256.0f * c1.r / c2.r;
    c.g = 256.0f * c1.g / c2.g;
    c.b = 256.0f * c1.b / c2.b;
    c.a = 256.0f * c1.a / c2.a;
    return c;
}

SDL_Color operator*(SDL_Color c1, float f)
{
    SDL_Color c;
    c.r = c1.r * f;
    c.g = c1.g * f;
    c.b = c1.b * f;
    c.a = c1.a * f;
    return c;
}

SDL_Color operator/(SDL_Color c1, float f)
{
    SDL_Color c;
    c.r = c1.r / f;
    c.g = c1.g / f;
    c.b = c1.b / f;
    c.a = c1.a / f;
    return c;
}

std::map<std::string, std::string> filesInDir(const std::string& basePath)
{
    std::map<std::string, std::string> result;
    tinydir_dir dir;
    tinydir_open(&dir, basePath.c_str());

    while (dir.has_next)
    {
        tinydir_file file;
        tinydir_readfile(&dir, &file);

        if (!file.is_dir)
        {
            std::string path = basePath + file.name;
            std::string name = file.name;
            name = name.substr(0, name.find_last_of('.'));

            result[name] = path;
        }

        tinydir_next(&dir);
    }

    tinydir_close(&dir);

    return result;
}

float randFloat()
{
    return 1.0f * rand() / RAND_MAX;
}

void renderRect(const SDL_Rect& rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(App::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(App::renderer, &rect);
}
