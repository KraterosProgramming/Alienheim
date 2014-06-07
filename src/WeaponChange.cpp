#include "WeaponChange.h"
#include "App.h"
#include "util.h"

void UpgradeWeaponChange::perform()
{
    App::upgradeWeapon();
}

SDL_Color UpgradeWeaponChange::getColor()
{
    return green;
}

std::string UpgradeWeaponChange::getString()
{
    return "Better weapon";
}

void DowngradeWeaponChange::perform()
{
    App::downgradeWeapon();
}

SDL_Color DowngradeWeaponChange::getColor()
{
    return red;
}

std::string DowngradeWeaponChange::getString()
{
    return "Lost your weapon";
}
