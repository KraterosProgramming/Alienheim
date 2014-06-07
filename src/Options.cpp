#include "Options.h"
#include "App.h"
#include "util.h"
#include <iostream>

const int Options::volumeStep = MIX_MAX_VOLUME / 8;
bool Options::inFullScreen = false;

Options::Options()
{
    this->fullScreen = new Button(15, 255, "Full screen", new VoidBehavior(Options::switchFullScreen));
    this->windowed = new Button(285, 255, "Windowed", new VoidBehavior(Options::switchWindowed));
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_f] = this->fullScreen);
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_w] = this->windowed);

    this->objects[MIDDLE].push_back(new Button(15, 300, "Music -", new VoidBehavior(Options::decreaseMusic)));
    this->objects[MIDDLE].push_back(new Button(525, 300, "Music +", new VoidBehavior(Options::increaseMusic)));
    this->objects[MIDDLE].push_back(new Button(15, 345, "Sound -", new VoidBehavior(Options::decreaseSound)));
    this->objects[MIDDLE].push_back(new Button(525, 345, "Sound +", new VoidBehavior(Options::increaseSound)));

    this->objects[MIDDLE].push_back(new Bar(285, 307, 210, 16, App::percentMusicVolume, darkGray, lightGray));
    this->objects[MIDDLE].push_back(new Bar(285, 352, 210, 16, App::percentSoundVolume, darkGray, lightGray));

    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_r] = this->hotkeys[SDLK_RETURN] = new Button(15, 390, "Return", new StringBehavior(App::changeScene, "Main menu")));

    this->objects[BACK].push_back(new Picture(0, 0, App::db.images["mainMenuBackground"]));
}

void Options::open()
{
    this->fullScreen->enable = !Options::inFullScreen;
    this->windowed->enable = Options::inFullScreen;
}

void Options::switchFullScreen()
{
    if (SDL_SetWindowFullscreen(App::window, SDL_WINDOW_FULLSCREEN) < 0)
    {
        std::cerr << "Error switching to full screen mode: " << SDL_GetError() << std::endl;
    }
    else
    {
        Options::inFullScreen = true;
        App::currentScene->open();
    }
}

void Options::switchWindowed()
{
    if (SDL_SetWindowFullscreen(App::window, SDL_WINDOW_MAXIMIZED) < 0)
    {
        std::cerr << "Error switching to windowed mode: " << SDL_GetError() << std::endl;
    }
    else
    {
        Options::inFullScreen = false;
        App::currentScene->open();
    }
}

void Options::decreaseMusic()
{
    Mix_VolumeMusic(std::max(0, Mix_VolumeMusic(-1) - Options::volumeStep));
}

void Options::increaseMusic()
{
    Mix_VolumeMusic(std::min(MIX_MAX_VOLUME, Mix_VolumeMusic(-1) + Options::volumeStep));
}

void Options::decreaseSound()
{
    Mix_Volume(-1, std::max(0, Mix_Volume(-1, -1) - Options::volumeStep));
}

void Options::increaseSound()
{
    Mix_Volume(-1, std::max(0, Mix_Volume(-1, -1) + Options::volumeStep));
}
