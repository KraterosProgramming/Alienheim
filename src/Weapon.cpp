#include "Weapon.h"

Weapon::Weapon(const std::string& name, Image* image, const Attack& attack, int level, int probability)
       :attack(attack)
{
    this->name = name;
    this->image = image;
    this->level = level;
    this->probability = probability;
}

int Weapon::getProbability()
{
    return this->probability;
}
