#include "EffectInstance.h"

EffectInstance::EffectInstance(int x, int y, Effect* effect)
               :Object(x, y)
{
    this->effect = effect;
    this->startTime = SDL_GetTicks();
    this->delay = 0;
    this->speed = 1.0f;
}

EffectInstance::EffectInstance(int x, int y, Effect* effect, Uint32 delay, float speed)
               :Object(x, y)
{
    this->effect = effect;
    this->startTime = SDL_GetTicks();
    this->delay = delay;
    this->speed = speed;
}

void EffectInstance::draw()
{
    if (SDL_GetTicks() - this->startTime >= this->delay)
    {
        if (this->getFrame() >= this->effect->frameCount)
        {
            this->dead = true;
        }
        else
        {
            if (this->effect)
            {
                this->effect->render(this->x, this->y, this->getFrame() % this->effect->frameCount);
            }
        }
    }
}

int EffectInstance::getFrame()
{
    return (int)(0.001f * (SDL_GetTicks() - this->startTime - this->delay) * this->effect->fps * this->speed);
}
