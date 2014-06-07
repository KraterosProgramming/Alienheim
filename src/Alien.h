#pragma once
#include <string>
#include <SDL2/SDL_mixer.h>
#include "Image.h"
#include "Attack.h"

// TODO treasures
class Alien
{
public:
    Alien(const std::string& name, Image* image, Mix_Chunk* battleCry, int maxHealth, int energy, const Attack& attack, int level, int probability);

    int getProbability();

    std::string name;
    Image* image;
    Mix_Chunk* battleCry;
    int health, maxHealth;
    int energy;
    Attack attack;
    int level;

private:
    int probability;
};
