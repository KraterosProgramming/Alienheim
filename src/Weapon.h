#pragma once
#include "Image.h"
#include "Attack.h"
#include <string>
#include <SDL2/SDL_mixer.h>

class Weapon
{
public:
    Weapon(const std::string& name, Image* image, const Attack& attack, int level, int probability);

    int getProbability();

    std::string name;
    Image* image;
    Attack attack;
    int level;

private:
    int probability;
};
