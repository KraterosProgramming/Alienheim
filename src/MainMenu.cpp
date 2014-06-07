#include "MainMenu.h"
#include "App.h"

MainMenu::MainMenu()
{
    this->continueButton = new Button(15, 300, "Continue game", new StringBehavior(App::changeScene, "Shelter menu"));
    this->continueButton->enable = false;

    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_n] = new Button(15, 255, "New game", new StringBehavior(App::changeScene, "Character creation")));
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_c] = this->continueButton);
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_o] = new Button(15, 345, "Options", new StringBehavior(App::changeScene, "Options")));
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_e] = this->hotkeys[SDLK_ESCAPE] = new Button(15, 390, "Exit", new VoidBehavior(App::exit)));

    this->objects[BACKGROUND].push_back(new Picture(0, 0, App::db.images["mainMenuBackground"]));
}

void MainMenu::open()
{
    this->continueButton->enable = App::character;
}

