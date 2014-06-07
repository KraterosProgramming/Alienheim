#pragma once
#include "EffectInstance.h"
#include <SDL2/SDL_mixer.h>

class Attack
{
public:
    static const float energyFactor;
    static const float randomFactor;

    Attack(int damage, Uint32 duration, Effect* effect, Mix_Chunk* sound);

    int getRandomDamage(int maxEnergy);

    Uint32 duration;
    Effect* effect;
    Mix_Chunk* sound;

private:
    int damage;
};
