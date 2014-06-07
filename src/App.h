#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "DataBase.h"
#include "Character.h"
#include "Alien.h"
#include "Sector.h"

class App
{
public:
    static SDL_Window* window;
    static SDL_Renderer* renderer;

    static Uint32 mouseButton;
    static int mouseX, mouseY;
    static const Uint8* keyboard;

    static bool quit;

    static DataBase db;

    static Scene* currentScene;
    static Image* buttonNormal;
    static Image* buttonOver;
    static Image* buttonDown;
    static Image* buttonDisable;
    static Event* currentEvent;
    static Character* character;
    static Alien* alien;
    static Sector* sector;

    static void newGame(const std::string& characterName);
    static void exit();
    static void turnMusic(bool on);
    static void turnSound(bool on);
    static void captureScreen();

    static void changeScene(const std::string& scene);
    static void changeWeapon(const std::string& weapon);
    static void changeWeapon(int level);
    static void downgradeWeapon();
    static void upgradeWeapon();
    static void changeSector(const std::string& sector);

    static void startRandomEvent(const std::string& category);

    static float percentHealth();
    static float percentEnergy();
    static float percentFood();
    static float alienPercentHealth();
    static float percentMusicVolume();
    static float percentSoundVolume();

    static bool init();
    static bool loadContent();
    static void close();
    static void loop();

    App();
    ~App();

    int run();
};
