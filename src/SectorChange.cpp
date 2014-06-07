#include "SectorChange.h"
#include "App.h"
#include "util.h"

void SectorChange::perform()
{
    std::vector<Sector*> sectorsOk;

    for (auto &i : App::db.sectors)
    {
        if (i.second->level - App::sector->level <= 1)
        {
            sectorsOk.push_back(i.second);
        }
    }

    this->sector = selectRandom(sectorsOk)->name;

    App::changeSector(this->sector);
}

std::string SectorChange::getString()
{
    return this->sector + " discovered";
}

SDL_Color SectorChange::getColor()
{
    return blue;
}
