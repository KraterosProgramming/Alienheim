#include "Event.h"

Event::Event(int probability)
{
    this->probability = probability;
}

int Event::getProbability()
{
    return this->probability;
}
