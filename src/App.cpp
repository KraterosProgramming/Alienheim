#include "App.h"
#include "Options.h"
#include "util.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

SDL_Window* App::window = nullptr;
SDL_Renderer* App::renderer = nullptr;

Uint32 App::mouseButton = 0;
int App::mouseX = 0, App::mouseY = 0;
const Uint8* App::keyboard = nullptr;

bool App::quit = false;

DataBase App::db;

Scene* App::currentScene = nullptr;
Image* App::buttonNormal = nullptr;
Image* App::buttonOver = nullptr;
Image* App::buttonDown = nullptr;
Image* App::buttonDisable = nullptr;
Event* App::currentEvent = nullptr;
Character* App::character = nullptr;
Alien* App::alien = nullptr;
Sector* App::sector = nullptr;

App::App()
{

}

App::~App()
{
    this->close();
}

float App::percentHealth()
{
    return (float)(App::character->health) / (float)(App::character->maxHealth);
}

float App::percentEnergy()
{
    return (float)(App::character->energy) / (float)(App::character->maxEnergy);
}

float App::percentFood()
{
    return (float)(App::character->food) / (float)(App::character->maxFood);
}

float App::alienPercentHealth()
{
    return (float)(App::alien->health) / (float)(App::alien->maxHealth);
}

float App::percentMusicVolume()
{
    return (float)Mix_VolumeMusic(-1) / (float)MIX_MAX_VOLUME;
}

float App::percentSoundVolume()
{
    return (float)Mix_Volume(-1, -1) / (float)MIX_MAX_VOLUME;
}

void App::newGame(const std::string& characterName)
{
    if (App::character)
    {
        delete App::character;
    }

    App::character = new Character(App::db.images[characterName], App::db.images[characterName + "Background"], App::db.weapons["Club"]);
    App::sector = App::db.sectors["Mountains"];

    App::changeScene("Shelter menu");
}

void App::exit()
{
    Mix_FadeOutMusic(500);
    App::quit = true;
}

void App::turnMusic(bool on)
{
    if (on)
    {
        Mix_VolumeMusic(MIX_MAX_VOLUME);
    }
    else
    {
        Mix_VolumeMusic(0);
    }

//    ((Options*)App::db.scenes["options"])->musicOn->enable = !on;
//    ((Options*)App::db.scenes["options"])->musicOff->enable = on;
}

void App::turnSound(bool on)
{
    if (on)
    {
        Mix_Volume(-1, MIX_MAX_VOLUME);
    }
    else
    {
        Mix_Volume(-1, 0);
    }

//    ((Options*)App::db.scenes["options"])->soundOn->enable = !on;
//    ((Options*)App::db.scenes["options"])->soundOff->enable = on;
}

int App::run()
{
    std::ifstream creditsFile("credits.txt");
    if (creditsFile.good())
    {
        while (!creditsFile.eof())
        {
            char buffer[2048];
            creditsFile.getline(buffer, 2048);
            std::cout << buffer << std::endl;
        }
    }
    creditsFile.close();

    std::cout << std::endl;
    std::cout << "INITIATING" << std::endl;
    if (App::init())
    {
        std::cout << std::endl;
        std::cout << "RUNNING" << std::endl;
        while (!quit || Mix_PlayingMusic())
        {
            App::loop();
        }
    }

    std::cout << std::endl;
    std::cout << "CLOSING" << std::endl;
    App::close();

    return 0;
}

bool App::init()
{
    bool ok = false;

    srand(time(NULL));

    std::cout << "Initiating SDL... ";
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error Initiating SDL: " << SDL_GetError() << std::endl;
    }
    else
    {
        std::cout << "OK" << std::endl << "Initiating Image support... ";
        if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG) != (IMG_INIT_JPG|IMG_INIT_PNG))
        {
            std::cerr << "Error Initiating Image support: " << IMG_GetError() << std::endl;
        }
        else
        {
            std::cout << "OK" << std::endl << "Initiating True Type Font support... ";
            if (TTF_Init() < 0)
            {
                std::cerr << "Error Initiating True Type Font support: " << TTF_GetError() << std::endl;
            }
            else
            {
                std::cout << "OK" << std::endl << "Initiating Mixer...";
                if (Mix_Init(MIX_INIT_OGG|MIX_INIT_FLAC) != (MIX_INIT_OGG|MIX_INIT_FLAC))
                {
                    std::cerr << "Error Initiating Mixer: " << Mix_GetError() << std::endl;
                }
                else
                {
                    std::cout << "OK" << std::endl << "Opening audio...";
                    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                    {
                        std::cerr << "Error opening audio: " << Mix_GetError() << std::endl;
                    }
                    else
                    {
                        std::cout << "OK" << std::endl << "Creating window... ";
                        if (!(App::window = SDL_CreateWindow("Eric vs Aliens", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 480, SDL_WINDOW_SHOWN)))
                        {
                            std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
                        }
                        else
                        {
                            std::cout << "OK" << std::endl << "Creating renderer... ";
                            if (!(App::renderer = SDL_CreateRenderer(App::window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC)))
                            {
                                std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
                            }
                            else
                            {
                                std::cout << "OK" << std::endl;
                                SDL_SetRenderDrawColor(App::renderer, 0, 0, 0, 255);
                                SDL_RenderClear(App::renderer);
                                SDL_RenderPresent(App::renderer);

                                std::cout << "Loading data base... " << std::endl;
                                if (!App::db.preloadContent())
                                {
                                    std::cerr << "Error loading data base" << std::endl;
                                }
                                else
                                {
                                    App::db.images["loading"]->render(0, 480 - App::db.images["loading"]->h);
                                    SDL_RenderPresent(App::renderer);

                                    if (!db.loadContent())
                                    {
                                        std::cerr << "Error loading data base" << std::endl;
                                    }
                                    else
                                    {
                                        std::cout << "DONE" << std::endl;

                                        App::buttonNormal = App::db.images["buttonNormal"];
                                        App::buttonOver = App::db.images["buttonOver"];
                                        App::buttonDown = App::db.images["buttonDown"];
                                        App::buttonDisable = App::db.images["buttonDisable"];

                                        App::changeScene("Title screen");

                                        Mix_FadeInMusic(App::db.musics["music"], -1, 1000);

                                        ok = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return ok;
}

void App::close()
{
    std::cout << "Unloading data base" << std::endl;
    App::db.unloadContent();

    std::cout << "Destroying renderer" << std::endl;
    if (App::renderer)
    {
        SDL_DestroyRenderer(App::renderer);
        App::renderer = nullptr;
    }

    std::cout << "Destroying window" << std::endl;
    if (App::window)
    {
        SDL_DestroyWindow(App::window);
        App::window = nullptr;
    }

    std::cout << "Closing audio" << std::endl;
    Mix_CloseAudio();

    std::cout << "Closing libraries" << std::endl;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

#include "EffectInstance.h"

void App::loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                App::exit();
            }
            break;

            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_PRINTSCREEN:
                    {
                        App::captureScreen();
                    }
                    break;

                    default:;
                }
            }
            break;

            default:;
        }

        App::currentScene->takeEvent(event);
    }

    SDL_SetCursor(App::db.cursors["arrow"]);

    App::mouseButton = SDL_GetMouseState(&App::mouseX, &App::mouseY);
    App::keyboard = SDL_GetKeyboardState(NULL);

    App::currentScene->update();

    SDL_SetRenderDrawColor(App::renderer, 0, 0, 0, 255);
    SDL_RenderClear(App::renderer);

    if (App::currentScene)
    {
        App::currentScene->draw();
    }

    SDL_RenderPresent(App::renderer);
}

void App::startRandomEvent(const std::string& category)
{
    Event* event = selectRandom(App::db.events[category]);

    if (!event)
    {
        std::cerr << "Error no events in category \"" << category << "\"" << std::endl;
    }
    else
    {
        event->start();
    }

    ++App::character->dayCount;
}

void App::changeScene(const std::string& scene)
{
    if (!App::db.scenes.count(scene))
    {
        std::cout << "Error changing scene: scene \"" << scene << "\" does not exist" << std::endl;
    }
    else
    {
        if (App::currentScene)
        {
            App::currentScene->close();
        }

        App::currentScene = App::db.scenes[scene];

        if (App::currentScene)
        {
            App::currentScene->open();
        }
    }
}

void App::changeWeapon(const std::string& weapon)
{
    if (!App::db.weapons.count(weapon))
    {
        std::cout << "Error changing weapons: weapon \"" << weapon << "\" does not exist" << std::endl;
    }
    else
    {
        App::character->weapon = App::db.weapons[weapon];
    }
}

void App::changeWeapon(int level)
{
    std::vector<Weapon*> weapons_ok;

    for (auto &w : App::db.weapons)
    {
        if (w.second->level == level)
        {
            weapons_ok.push_back(w.second);
        }
    }

    Weapon* weapon = selectRandom(weapons_ok);

    if (weapon)
    {
        App::character->weapon = weapon;
    }
}

void App::downgradeWeapon()
{
    App::changeWeapon(App::character->weapon->level - 1);
}

void App::upgradeWeapon()
{
    App::changeWeapon(App::character->weapon->level + 1);
}

void App::changeSector(const std::string& sector)
{
    App::sector = App::db.sectors[sector];
    App::sector->startDay = App::character->dayCount;
}

void App::captureScreen()
{
    char pixels[800 * 480 * 4];
    if (SDL_RenderReadPixels(App::renderer, NULL, 0, pixels, 4*800) < 0)
    {
        std::cerr << "Error reading screen pixels: " << SDL_GetError() << std::endl;
    }
    else
    {
        SDL_Surface* screenShot = SDL_CreateRGBSurfaceFrom(pixels, 800, 480, 32, 4*800, 0x00FF0000, 0x0000FF00, 0x000000FF, 0);
        if (!screenShot)
        {
            std::cerr << "Error taking shot of screen: " << SDL_GetError() << std::endl;
        }
        else
        {
            time_t now = time(nullptr);

            char fileName[255];
            strftime(fileName, 255, "screenshots/%Y_%m_%d__%H_%M_%S.bmp", localtime(&now));

            if (SDL_SaveBMP(screenShot, fileName) < 0)
            {
                std::cerr << "Error saving screen shot: " << SDL_GetError() << std::endl;
            }
            else
            {
                std::cout << "Screen shot taken: size=" << screenShot->w << "x" << screenShot->h << "x" << (int)(screenShot->format->BitsPerPixel) << ", pitch=" << screenShot->pitch << std::endl;
            }

            SDL_FreeSurface(screenShot);
        }
    }
}
