#pragma once
#include "Scene.h"
#include "Image.h"
#include "Weapon.h"
#include "Event.h"
#include "Alien.h"
#include "Effect.h"
#include "Sector.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class DataBase
{
public:
    static const std::string cursorNames[SDL_NUM_SYSTEM_CURSORS];

    TTF_Font* font;
    std::map<std::string, SDL_Cursor*> cursors;
    std::map<std::string, Scene*> scenes;
    std::map<std::string, Image*> images;
    std::map<std::string, Weapon*> weapons;
    std::map<std::string, Mix_Music*> musics;
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, std::vector<Event*> > events;
    std::map<std::string, Alien*> aliens;
    std::map<std::string, Effect*> effects;
    std::map<std::string, Sector*> sectors;

    bool preloadContent();
    bool loadContent();
    void unloadContent();
};
