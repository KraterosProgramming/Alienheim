#pragma once
#include "Event.h"
#include <vector>

class ChangeEvent : public Event
{
public:
    ChangeEvent(int probability, bool positive, Image* image, const std::string description, const std::vector<Change*>& changes);
    virtual ~ChangeEvent();

    virtual void start() override;
    virtual int getProbability() override;

    Image* image;
    std::string description;
    std::vector<Change*> changes;
    bool positive;
};
