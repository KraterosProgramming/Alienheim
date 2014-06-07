#include "ChangeEvent.h"
#include "App.h"

ChangeEvent::ChangeEvent(int probability, bool positive, Image* image, const std::string description, const std::vector<Change*>& changes)
            :Event(probability)
{
    this->image = image;
    this->description = description;
    this->changes = changes;
    this->positive = positive;
}

ChangeEvent::~ChangeEvent()
{
    for (std::vector<Change*>::iterator it = this->changes.begin(); it != this->changes.end(); ++it)
    {
        if (*it)
        {
            delete *it;
        }
    }

    this->changes.clear();
}

void ChangeEvent::start()
{
    App::currentEvent = this;

    for (auto &c : this->changes)
    {
        c->perform();
    }

    App::changeScene("Change event scene");
}

int ChangeEvent::getProbability()
{
    if (this->positive)
    {
        return Event::getProbability() * App::sector->goodness;
    }
    else
    {
        return Event::getProbability() * (1.0f - App::sector->goodness);
    }
}
