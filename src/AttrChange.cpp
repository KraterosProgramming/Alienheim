#include "AttrChange.h"
#include "App.h"
#include "util.h"
#include <cstdio>
#include <sstream>
#include <cmath>
#include <iostream>

const float AttrChange::healthFactor = 0.01f;
const float AttrChange::randomFactor = 0.3f;

AttrChange::AttrChange(int quantity) : Change()
{
    this->quantity = quantity;
    this->increment = quantity;
}

void AttrChange::perform()
{
    int& attr = this->getAttr();
    int& maxAttr = this->getMaxAttr();

    this->increment = this->getIncrement();

    if (attr + increment < 0)
    {
        App::character->health += 2*(attr + increment);
        attr = 0;
    }
    else if (attr + increment < maxAttr)
    {
        attr += increment;
    }
    else
    {
        attr = maxAttr;
    }
}

int AttrChange::getIncrement()
{
    float hf = (this->quantity < 0 ? 0.0f : std::pow(AttrChange::healthFactor, 2.0f) * App::character->maxHealth);
    float rf = AttrChange::randomFactor * (randFloat() - randFloat());

    return ((this->quantity < 0 ? 1 : App::sector->goodness + 0.5f) * this->quantity + 0.5f) * (1.0f + hf + rf);
}

SDL_Color AttrChange::getColor()
{
    if (this->increment < 0)
    {
        return red;
    }
    else
    {
        return green;
    }
}

std::string AttrChange::getString()
{
     std::stringstream ss;
     ss << this->getSign() << std::abs(this->increment) << " " << this->getName();
     return ss.str();
}

char AttrChange::getSign()
{
    if (this->increment < 0)
    {
        return '-';
    }
    else
    {
        return '+';
    }
}

int& HealthChange::getAttr()
{
    return App::character->health;
}

int& HealthChange::getMaxAttr()
{
    return App::character->maxHealth;
}

std::string HealthChange::getName()
{
    return "Health";
}

int& EnergyChange::getAttr()
{
    return App::character->energy;
}

int& EnergyChange::getMaxAttr()
{
    return App::character->maxEnergy;
}

std::string EnergyChange::getName()
{
    return "Energy";
}

int& FoodChange::getAttr()
{
    return App::character->food;
}

int& FoodChange::getMaxAttr()
{
    return App::character->maxFood;
}

std::string FoodChange::getName()
{
    return "Food";
}
