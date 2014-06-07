#include "Attack.h"
#include "App.h"
#include "util.h"

const float Attack::energyFactor = 0.01f;
const float Attack::randomFactor = 0.3f;

Attack::Attack(int damage, Uint32 duration, Effect* effect, Mix_Chunk* sound)
{
    this->damage = damage;
    this->duration = duration;
    this->effect = effect;
    this->sound = sound;
}

int Attack::getRandomDamage(int maxEnergy)
{
    float ef = std::pow(Attack::energyFactor, 2.0f) * maxEnergy;
    float rf = Attack::randomFactor * (randFloat() - randFloat());

    return (this->damage + 0.5f) * (1.0f + ef + rf);
}
