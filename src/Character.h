#pragma once
#include "Weapon.h"

class Character
{
public:
    Character(Image* image, Image* background, Weapon* weapon);

    int health, maxHealth;
    int energy, maxEnergy;
    int food, maxFood;
    Image* image;
    Image* background;
    Weapon* weapon;
    int dayCount;
    int killCount;
};
