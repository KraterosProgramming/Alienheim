#include "Sector.h"
#include "App.h"
#include <algorithm>

Sector::Sector(const std::string& name, Image* image, int level, int probability, float spawn, float goodness, int daysToDoubleSpawn)
{
    this->name = name;
    this->startDay = 0;
    this->image = image;
    this->level = level;
    this->probability = probability;
    this->spawn = spawn;
    this->goodness = goodness;
    this->daysToDoubleSpawn = daysToDoubleSpawn;
}

int Sector::getProbability()
{
    return this->probability * (std::min<float>(App::sector->level, this->level) / (std::max<float>(App::sector->level, this->level)));
}
