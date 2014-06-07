#pragma once
#include "Scene.h"

class TitleScreen : public Scene
{
public:
    const static Uint32 duration;
    const static Uint32 fadeDuration;

    TitleScreen();

    virtual void open() override;
    virtual void update() override;
    virtual void takeEvent(const SDL_Event& event);

    static Uint8 opacity(Uint32 t);

    Uint32 startTime;
    Picture* picture;
};
