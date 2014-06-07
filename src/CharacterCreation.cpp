#include "CharacterCreation.h"
#include "App.h"

CharacterCreation::CharacterCreation()
{
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_e] = new Button(15, 255, "Play as Ernok", new StringBehavior(App::newGame, "Ernok")));
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_n] = new Button(15, 300, "Play as Natoman", new StringBehavior(App::newGame, "Natoman")));

    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_c] = new Button(15, 390, "Cancel", new StringBehavior(App::changeScene, "Main menu")));

    this->objects[BACKGROUND].push_back(new Picture(0, 0, App::db.images["mainMenuBackground"]));
}

