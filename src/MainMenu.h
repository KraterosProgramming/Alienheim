#pragma once
#include "Scene.h"

class MainMenu : public Scene
{
public:
    MainMenu();

    virtual void open() override;

    Button* continueButton;
};
