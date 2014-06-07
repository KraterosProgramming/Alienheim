#pragma once
#include "Image.h"
#include <string>

class Sector
{
public:
    Sector(const std::string& name, Image* image, int level, int probability, float spawn, float goodness, int daysToDoubleSpawn);

    int getProbability();

    int startDay;
    std::string name;
    Image* image;
    int level;
    int probability;
    float spawn, goodness;
    int daysToDoubleSpawn;
};
