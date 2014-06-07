#include "GameOverScene.h"
#include "App.h"
#include "util.h"
#include <sstream>
#include <iostream>

GameOverScene::GameOverScene() : Scene()
{
    this->description = new Label(15, 165, 770, "Your journey has ended. With your breath fading, you damn this planet and rise your middle finger against it.", white);
    this->days = new Label(280, 195 + this->description->image.h, 0, "Days survived: 0", blue);
    this->killed = new Label(280, 225 + this->description->image.h, 0, "Aliens killed: 0", blue);

    this->objects[MIDDLE].push_back(new Picture(150, 15, App::db.images["gameOver"]));
    this->objects[MIDDLE].push_back(this->description);
    this->objects[MIDDLE].push_back(this->days);
    this->objects[MIDDLE].push_back(this->killed);

    this->objects[FRONT].push_back(this->hotkeys[SDLK_r] = this->hotkeys[SDLK_RETURN] = new Button(280, 435, "Restart", new StringBehavior(App::changeScene, "Main menu")));
}


void GameOverScene::open()
{
    std::stringstream ss;


    ss.str("");
    ss << "Days survived: " << App::character->dayCount;

    this->days->text = ss.str();
    this->days->renderText();


    ss.str("");
    ss << "Aliens killed: " << App::character->killCount;

    this->killed->text = ss.str();
    this->killed->renderText();


    delete App::character;
    App::character = nullptr;
}
