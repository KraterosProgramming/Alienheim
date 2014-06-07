#include "BattleEvent.h"
#include "App.h"
#include "util.h"
#include <iostream>

BattleEvent::BattleEvent(int probability)
            :Event(probability)
{

}

int BattleEvent::getProbability()
{
    return Event::getProbability() * (App::sector->spawn + ((1.1f * App::character->dayCount - App::sector->startDay) / App::sector->daysToDoubleSpawn));
}

void BattleEvent::start()
{
    App::currentEvent = this;

    std::vector<Alien*> aliensOk;

    for (auto &a : App::db.aliens)
    {
        aliensOk.push_back(a.second);
    }

    Alien* alien = selectRandom(aliensOk);

    if (!alien)
    {
        std::cout << "Warning no alien of level " << App::character->weapon->level << std::endl;
    }
    else
    {
        App::alien = alien;
        App::alien->health = App::alien->maxHealth;

        App::changeScene("Battle scene");
    }
}
