#pragma once
#include "Change.h"

class WeaponChange : public Change
{
public:
    WeaponChange() : Change() { }
    virtual ~WeaponChange() { }
};

class UpgradeWeaponChange : public WeaponChange
{
public:
    UpgradeWeaponChange() : WeaponChange() { }

    virtual SDL_Color getColor() override;
    virtual std::string getString() override;
    virtual void perform() override;
};

class DowngradeWeaponChange : public WeaponChange
{
public:
    DowngradeWeaponChange() : WeaponChange() { }

    virtual SDL_Color getColor() override;
    virtual std::string getString() override;
    virtual void perform() override;
};
