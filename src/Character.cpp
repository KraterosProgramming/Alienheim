#include "Character.h"
#include "App.h"

Character::Character(Image* image, Image* background, Weapon* weapon)
{
    this->health = this->maxHealth = 100;
    this->energy = this->maxEnergy = 100;
    this->food = 0.25f * (this->maxFood = 100);
    this->image = image;
    this->background = background;
    this->weapon = weapon;
    this->dayCount = 0;
    this->killCount = 0;
}

