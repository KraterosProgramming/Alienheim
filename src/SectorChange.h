#pragma once
#include "Change.h"
#include "Sector.h"

class SectorChange : public Change
{
public:
    SectorChange() : Change() { }

    virtual void perform() override;
    virtual std::string getString() override;
    virtual SDL_Color getColor() override;

    std::string sector;
};
