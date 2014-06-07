#pragma once
#include "Event.h"
#include "Alien.h"

class BattleEvent : public Event
{
public:
    BattleEvent(int probability);

    virtual int getProbability() override;
    virtual void start() override;
};
