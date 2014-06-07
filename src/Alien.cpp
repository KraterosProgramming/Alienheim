#include "Alien.h"
#include "App.h"
#include "Sector.h"
#include <algorithm>
#include <iostream>

Alien::Alien(const std::string& name, Image* image, Mix_Chunk* battleCry, int maxHealth, int energy, const Attack& attack, int level, int probability)
      :attack(attack)
{
    this->name = name;
    this->image = image;
    this->battleCry = battleCry;
    this->health = 0;
    this->maxHealth = maxHealth;
    this->energy = energy;
    this->level = level;
    this->probability = probability;
}

int Alien::getProbability()
{
    if (this->level - App::sector->level > 1 + App::character->dayCount / 100)
    {
        return 0;
    }
    else
    {
        return this->probability / (1.0f + 2.0f * std::abs(this->level - App::sector->level)) + 0.05f * std::pow<double>(this->level, std::min(1000, App::character->dayCount) / 100);
    }
}
