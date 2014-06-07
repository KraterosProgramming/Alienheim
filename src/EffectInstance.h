#pragma once
#include "Object.h"
#include "Effect.h"

class EffectInstance : public Object
{
public:
    EffectInstance(int x, int y, Effect* effect);
    EffectInstance(int x, int y, Effect* effect, Uint32 delay, float speed);

    virtual void draw() override;

    int getFrame();

    Uint32 startTime;
    Effect* effect;
    Uint32 delay;
    float speed;
};
