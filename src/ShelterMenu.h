#pragma once
#include "Scene.h"

class ShelterMenu : public Scene
{
public:
    ShelterMenu();
    ~ShelterMenu();

    virtual void open();

    Label* health;
    Label* energy;
    Label* food;
    Picture* sector;
    Picture* background;
    Picture* character;
    Picture* weapon;
    Label* weaponName;
    Label* dayCount;
};
