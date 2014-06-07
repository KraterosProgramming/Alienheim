#include "ShelterMenu.h"
#include "App.h"
#include "util.h"
#include <sstream>

ShelterMenu::ShelterMenu()
{
    this->health = new Label(155, 15, 95, "0/0", white);
    this->energy = new Label(155, 45, 95, "0/0", white);
    this->food = new Label(155, 75, 95, "0/0", white);
    this->sector = new Picture(285, 15, nullptr);
    this->character = new Picture(15, 105, nullptr);
    this->background = new Picture(15, 105, nullptr);
    this->weapon = new Picture(15, 105, NULL);
    this->weaponName = new Label(15, 390, 255, "No weapon", cyan);
    this->dayCount = new Label(15, 435, 255, "Day Count: 0", cyan);

    // Character
    this->objects[MIDDLE].push_back(new Label(15, 15, 120, "Health", white));
    this->objects[MIDDLE].push_back(new Label(15, 45, 120, "Energy", white));
    this->objects[MIDDLE].push_back(new Label(15, 75, 120, "Food", white));

    this->objects[MIDDLE].push_back(new Bar(135, 15, 135, 23, App::percentHealth, {63, 0, 0, 255}, {191, 0, 0, 255}));
    this->objects[MIDDLE].push_back(new Bar(135, 45, 135, 23, App::percentEnergy, {0, 0, 63, 255}, {0, 0, 191, 255}));
    this->objects[MIDDLE].push_back(new Bar(135, 75, 135, 23, App::percentFood, {0, 63, 0, 255}, {0, 191, 0, 255}));

    this->objects[FRONT].push_back(this->health);
    this->objects[FRONT].push_back(this->energy);
    this->objects[FRONT].push_back(this->food);

    this->objects[FRONT].push_back(this->weaponName);
    this->objects[FRONT].push_back(this->dayCount);

    // Pictures
    this->objects[BACKGROUND].push_back(this->background);
    this->objects[BACK].push_back(this->weapon);
    this->objects[MIDDLE].push_back(this->character);

    this->objects[MIDDLE].push_back(this->sector);

    // Buttons
    this->objects[FRONT].push_back(this->hotkeys[SDLK_r] = new Button(285, 345, "Rest", new StringBehavior(App::startRandomEvent, "rest")));
    this->objects[FRONT].push_back(this->hotkeys[SDLK_t] = new Button(545, 345, "Train", new StringBehavior(App::startRandomEvent, "train")));

    this->objects[FRONT].push_back(this->hotkeys[SDLK_f] = new Button(285, 390, "Search food", new StringBehavior(App::startRandomEvent, "searchFood")));
    this->objects[FRONT].push_back(this->hotkeys[SDLK_w] = new Button(545, 390, "Search weapons", new StringBehavior(App::startRandomEvent, "searchWeapon")));

    this->objects[FRONT].push_back(this->hotkeys[SDLK_e] = new Button(285, 435, "Explore", new StringBehavior(App::startRandomEvent, "explore")));
    this->objects[FRONT].push_back(this->hotkeys[SDLK_m] = new Button(545, 435, "Main menu", new StringBehavior(App::changeScene, "Main menu")));
}

ShelterMenu::~ShelterMenu()
{

}

void ShelterMenu::open()
{
    if (App::character->health <= 0)
    {
        App::changeScene("Game over");
    }
    else
    {
        std::stringstream ss;

        ss.str("");
        ss << std::max(0, App::character->health) << "/" << App::character->maxHealth;
        this->health->text = ss.str();
        this->health->renderText();

        ss.str("");
        ss << std::max(0, App::character->energy) << "/" << App::character->maxEnergy;
        this->energy->text = ss.str();
        this->energy->renderText();

        ss.str("");
        ss << std::max(0, App::character->food) << "/" << App::character->maxFood;
        this->food->text = ss.str();
        this->food->renderText();

        this->sector->image = App::sector->image;
        this->character->image = App::character->image;
        this->background->image = App::character->background;
        this->weapon->image = App::character->weapon->image;

        this->weaponName->text = App::character->weapon->name;
        this->weaponName->renderText();

        ss.str("");
        ss << "Day count: " << App::character->dayCount;
        if (App::sector->startDay != 0)
        {
            ss << ", " << App::character->dayCount - App::sector->startDay;
        }
        this->dayCount->text = ss.str();
        this->dayCount->renderText();
    }
}

