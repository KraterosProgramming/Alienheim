#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
    GameOverScene();

    virtual void open();

    Label* description;
    Label* days;
    Label* killed;
};
