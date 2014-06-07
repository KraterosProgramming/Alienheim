#pragma once
#include "Object.h"
#include "Button.h"
#include "Bar.h"
#include "Label.h"
#include "Picture.h"
#include "EffectInstance.h"
#include <vector>
#include <map>

enum Layer
{
    BACKGROUND,
    BACK,
    MIDDLE,
    FRONT,
    FOREGROUND,
    nLayer
};

class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void draw();

    virtual void update() { }
    virtual void open() { }
    virtual void close() { }
    virtual void takeEvent(const SDL_Event& event);

    std::vector<Object*> objects[nLayer];
    std::map<SDL_Keycode, Button*> hotkeys;
};
