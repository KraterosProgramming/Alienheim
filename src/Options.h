#pragma once
#include "Scene.h"

class Options : public Scene
{
public:
    static const int volumeStep;
    static bool inFullScreen;

    static void switchFullScreen();
    static void switchWindowed();

    static void decreaseMusic();
    static void increaseMusic();
    static void decreaseSound();
    static void increaseSound();

    Options();

    virtual void open();

//    Button* musicOn;
//    Button* musicOff;
//    Button* soundOn;
//    Button* soundOff;
    Button* fullScreen;
    Button* windowed;
};
