#pragma once
#include "Scene.h"

class BattleScene : public Scene
{
public:
    BattleScene();

    virtual void open() override;
    virtual void update() override;

    static void attack();
    static void alienAttack();
    static void flee();

    static void checkAttack();
    static void checkAlienAttack();
    static void checkFlee();

    static bool randomFleeFunction();

    Label* health;
    Label* energy;
    Picture* character;
    Picture* background;
    Picture* weapon;
    Label* alienHealth;
    Picture* alien;

    Button* attackButton;
    Button* fleeButton;

    bool ericAttacking;
    bool ericFleed;
    bool alienAttacking;
    Uint32 ticks;
};
