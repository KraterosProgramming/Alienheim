#pragma once
#include "Scene.h"
#include "Change.h"
#include "Sector.h"
#include <vector>

class Event
{
public:
    Event(int probability);
    virtual ~Event() { }

    virtual void start() = 0;

    virtual int getProbability();

private:
    int probability;
};
