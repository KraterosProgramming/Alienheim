#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <SDL2/SDL.h>
#include "tinydir.h"

extern const SDL_Color white;
extern const SDL_Color lightGray;
extern const SDL_Color gray;
extern const SDL_Color darkGray;
extern const SDL_Color black;

extern const SDL_Color red;
extern const SDL_Color green;
extern const SDL_Color blue;

extern const SDL_Color cyan;
extern const SDL_Color magenta;
extern const SDL_Color yellow;

SDL_Color operator+(SDL_Color c1, SDL_Color c2);
SDL_Color operator-(SDL_Color c1, SDL_Color c2);
SDL_Color operator*(SDL_Color c1, SDL_Color c2);
SDL_Color operator/(SDL_Color c1, SDL_Color c2);
SDL_Color operator*(SDL_Color c1, float f);
SDL_Color operator/(SDL_Color c1, float f);

std::map<std::string, std::string> filesInDir(const std::string& basePath);

template<typename T>
T* selectRandom(const std::vector<T*>& vec)
{
    T* result = nullptr;

    if (vec.size() > 0)
    {
        int totalCases = 0;

        for (auto &item : vec)
        {
            int p = item->getProbability();
            totalCases += std::max(1, p);
        }


        int randomCase = rand() % totalCases;

        for (auto &item : vec)
        {
            if (0 <= randomCase && randomCase < item->getProbability())
            {
                result = item;
            }

            randomCase -= item->getProbability();
        }
    }

    return result;
}

float randFloat();

void renderRect(const SDL_Rect& rect, SDL_Color color);
