#include "MaxAttrChange.h"
#include "App.h"
#include <cstdio>
#include <sstream>
#include <cmath>

void MaxAttrChange::perform()
{
    int& attr = this->getAttr();
    int& maxAttr = this->getMaxAttr();

    maxAttr += this->quantity;

    if (attr > maxAttr)
    {
        attr = maxAttr;
    }
}

int& MaxHealthChange::getAttr()
{
    return App::character->health;
}

int& MaxHealthChange::getMaxAttr()
{
    return App::character->maxHealth;
}

std::string MaxHealthChange::getName()
{
    return "Max Health";
}

int& MaxEnergyChange::getAttr()
{
    return App::character->energy;
}

int& MaxEnergyChange::getMaxAttr()
{
    return App::character->maxEnergy;
}

std::string MaxEnergyChange::getName()
{
    return "Max Energy";
}

int& MaxFoodChange::getAttr()
{
    return App::character->food;
}

int& MaxFoodChange::getMaxAttr()
{
    return App::character->maxFood;
}

std::string MaxFoodChange::getName()
{
    return "Max Food";
}
