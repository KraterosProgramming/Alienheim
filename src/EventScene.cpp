#include "EventScene.h"
#include "ChangeEvent.h"
#include "App.h"
#include "util.h"
#include <iostream>

EventScene::EventScene()
{
    this->picture = new Picture(150, 15, NULL);
    this->description = new Label(15, 165, 770, "no event", white);

    this->objects[MIDDLE].push_back(this->picture);
    this->objects[MIDDLE].push_back(this->description);
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_r] = this->hotkeys[SDLK_RETURN] = new Button(280, 435, "Return", new StringBehavior(App::changeScene, "Shelter menu")));
}

EventScene::~EventScene()
{
    for (auto &it : this->changes)
    {
        if (it)
        {
            delete it;
        }
    }

    this->changes.clear();
}

void EventScene::draw()
{
    Scene::draw();

    for (auto &it : this->changes)
    {
        if (it)
        {
            it->draw();
        }
    }
}

void EventScene::open()
{
    if (!App::currentEvent)
    {
        std::cout << "Warning no current event" << std::endl;
    }
    else
    {
        for (auto &it : this->changes)
        {
            if (it)
            {
                delete it;
            }
        }

        this->changes.clear();

        this->picture->image = ((ChangeEvent*)App::currentEvent)->image;
        this->description->text = ((ChangeEvent*)App::currentEvent)->description;
        this->description->renderText();

        int y = this->description->y + this->description->image.h;

        for (auto &c : ((ChangeEvent*)App::currentEvent)->changes)
        {
            this->changes.push_back(new Label(280, y, 0, c->getString(), c->getColor()));
            y += 30;
        }
    }
}
