#pragma once
#include "Scene.h"

class EventScene : public Scene
{
public:
    EventScene();
    virtual ~EventScene();

    virtual void draw();

    virtual void open();

    Picture* picture;
    Label* description;
    std::vector<Label*> changes;
};
