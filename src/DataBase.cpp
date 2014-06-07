#include "DataBase.h"
#include "TitleScreen.h"
#include "MainMenu.h"
#include "Options.h"
#include "CharacterCreation.h"
#include "ShelterMenu.h"
#include "EventScene.h"
#include "BattleScene.h"
#include "GameOverScene.h"
#include "AttrChange.h"
#include "MaxAttrChange.h"
#include "WeaponChange.h"
#include "SectorChange.h"
#include "ChangeEvent.h"
#include "BattleEvent.h"
#include "DataFile.h"
#include "util.h"
#include <iostream>
#include <fstream>

const std::string DataBase::cursorNames[SDL_NUM_SYSTEM_CURSORS] =
{
    "arrow", "iBeam", "wait", "crossHair", "waitArrow",
    "sizeNWSE", "sizeNESW", "sizeWE", "sizeNS", "sizeAll", "no", "hand"
};

bool DataBase::preloadContent()
{
    Image* newImage = new Image();
    if (!newImage->loadFromFile("images/loading.png"))
    {
        delete newImage;
        std::cout << "Error loading images/loading.png" << std::endl;
        return false;
    }
    else
    {
        this->images["loading"] = newImage;
        return true;
    }
}

bool DataBase::loadContent()
{
    // Font
    if (!(this->font = TTF_OpenFont("font.ttf", 22)))
    {
        std::cerr << "Error opening TTF font: " << TTF_GetError() << std::endl;
        return false;
    }


    // Cursors
    for (int i = 0; i < SDL_NUM_SYSTEM_CURSORS; ++i)
    {
        SDL_Cursor* c = SDL_CreateSystemCursor((SDL_SystemCursor)i);
        if (!c)
        {
            std::cout << "Error creating cursor: " << SDL_GetError() << std::endl;
        }
        else
        {
            this->cursors[cursorNames[i]] = c;
        }
    }


    // Images
    std::map<std::string, std::string> imageFiles = filesInDir("images/");

    for (auto &it : imageFiles)
    {
        if (!this->images.count(it.first))
        {
            Image* newImage = new Image();
            if (!newImage->loadFromFile(it.second))
            {
                delete newImage;
                std::cout << "Error loading " << it.second << std::endl;
            }
            else
            {
                this->images[it.first] = newImage;
                std::cout << "Image " << it.first << " loaded" << std::endl;
            }
        }
    }


    // Musics
    std::map<std::string, std::string> musicFiles = filesInDir("musics/");

    for (auto &it : musicFiles)
    {
        if (!this->musics.count(it.first))
        {
            Mix_Music* newMusic = Mix_LoadMUS(it.second.c_str());
            if (!newMusic)
            {
                std::cout << "Error loading " << it.second << std::endl;
            }
            else
            {
                this->musics[it.first] = newMusic;
                std::cout << "Music " << it.first << " loaded" << std::endl;
            }
        }
    }


    // Sounds
    std::map<std::string, std::string> soundFiles = filesInDir("sounds/");

    for (auto &it : soundFiles)
    {
        if (!this->sounds.count(it.first))
        {
            Mix_Chunk* newSound = Mix_LoadWAV(it.second.c_str());
            if (!newSound)
            {
                std::cout << "Error loading " << it.second << std::endl;
            }
            else
            {
                this->sounds[it.first] = newSound;
                std::cout << "Sound " << it.first << " loaded" << std::endl;
            }
        }
    }


    // CONFIGURATIONS

    DataFile file;


    // Effects
    if (!file.parse("data/effects.txt"))
    {
        std::cerr << "Error reading file data/effects.txt" << std::endl;
    }
    else
    {
        DataFile::String name;
        std::string imageID; // TODO effects sounds
        int cols, rows, fps;

        while (!file.lines.empty())
        {
            std::stringstream* line = file.lines.front();
            file.lines.pop();
            (*line) >> name >> imageID >> cols >> rows >> fps;
            this->effects[name] = new Effect(this->images[imageID], cols, rows, fps);
            delete line;
        }
    }


    // Weapons
    if (!file.parse("data/weapons.txt"))
    {
        std::cerr << "Error reading file data/weapons.txt" << std::endl;
    }
    else
    {
        DataFile::String name, attackEffectID;
        std::string imageID, attackSoundID;
        int attackDamage = 0, attackDuration = 0, level = 0, probability = 0;

        while (!file.lines.empty())
        {
            std::stringstream* line = file.lines.front();
            file.lines.pop();
            (*line) >> name >> imageID >> attackDamage >> attackDuration >> attackEffectID >> attackSoundID >> level >> probability;
            this->weapons[name] = new Weapon(name, this->images[imageID],
                                             Attack(attackDamage, attackDuration, this->effects[attackEffectID], this->sounds[attackSoundID]),
                                             level, probability);
            delete line;
        }
    }


    // Aliens
    if (!file.parse("data/aliens.txt"))
    {
        std::cerr << "Error reading file data/aliens.txt" << std::endl;
    }
    else
    {
        DataFile::String name, attackEffectID;
        std::string imageID, soundID, attackSoundID;
        int maxHealth = 0, energy = 0, attackDamage = 0, attackDuration = 0, level = 0, probability = 0;

        while (!file.lines.empty())
        {
            std::stringstream* line = file.lines.front();
            file.lines.pop();
            (*line) >> name >> imageID >> soundID >> maxHealth >> energy >> attackDamage >> attackDuration >> attackEffectID >> attackSoundID >> level >> probability;
            this->aliens[name] = new Alien(name, this->images[imageID], this->sounds[soundID], maxHealth, energy,
                                           Attack(attackDamage, attackDuration, this->effects[attackEffectID], this->sounds[attackSoundID]),
                                           level, probability);
            delete line;
        }
    }


    // Sectors
    if (!file.parse("data/sectors.txt"))
    {
        std::cerr << "Error reading file data/sectors.txt" << std::endl;
    }
    else
    {
        DataFile::String name;
        std::string imageID;
        int level = 0, probability = 0, daysToDoubleSpawn = 0;
        float spawn = 0.0f, goodness = 0.0f;

        while (!file.lines.empty())
        {
            std::stringstream* line = file.lines.front();
            file.lines.pop();
            (*line) >> name >> imageID >> level >> probability >> spawn >> goodness >> daysToDoubleSpawn;
            this->sectors[name] = new Sector(name, this->images[imageID], level, probability, spawn, goodness, daysToDoubleSpawn);
            delete line;
        }
    }


    // Events
    if (!file.parse("data/events.txt"))
    {
        std::cerr << "Error reading file data/events.txt" << std::endl;
    }
    else
    {
        DataFile::String description;
        std::string category, imageID, type, changeType;
        int probability = 0, nChanges = 0, changeValue = 0;
        Event* event = nullptr;
        Change* change = nullptr;
        std::vector<Change*> changes;
        bool positive = 0;

        while (!file.lines.empty())
        {
            std::stringstream* line = file.lines.front();
            file.lines.pop();
            (*line) >> category >> probability >> type;

            if (type == "battle")
            {
                event = new BattleEvent(probability);
            }
            else if (type == "change")
            {
                (*line) >> positive >> imageID >> nChanges;

                changes.clear();
                for (int i = 0; i < nChanges; ++i)
                {
                    (*line) >> changeType;

                    if (changeType == "health" || changeType == "energy" || changeType == "food" ||
                        changeType == "HEALTH" || changeType == "ENERGY" || changeType == "FOOD")
                    {
                        (*line) >> changeValue;
                    }

                    if (changeType == "health")
                    {
                        change = new HealthChange(changeValue);
                    }
                    else if (changeType == "energy")
                    {
                        change = new EnergyChange(changeValue);
                    }
                    else if (changeType == "food")
                    {
                        change = new FoodChange(changeValue);
                    }
                    else if (changeType == "HEALTH")
                    {
                        change = new MaxHealthChange(changeValue);
                    }
                    else if (changeType == "ENERGY")
                    {
                        change = new MaxEnergyChange(changeValue);
                    }
                    else if (changeType == "FOOD")
                    {
                        change = new MaxFoodChange(changeValue);
                    }
                    else if (changeType == "upgrade")
                    {
                        change = new UpgradeWeaponChange();
                    }
                    else if (changeType == "downgrade")
                    {
                        change = new DowngradeWeaponChange();
                    }
                    else if (changeType == "sectorChange")
                    {
                        change = new SectorChange();
                    }

                    changes.push_back(change);
                }

                (*line) >> description;

                event = new ChangeEvent(probability, positive, this->images[imageID], description, changes);
            }

            this->events[category].push_back(event);
            delete line;
        }
    }


    // Scenes
    this->scenes["Title screen"] = new TitleScreen();
    this->scenes["Main menu"] = new MainMenu();
    this->scenes["Options"] = new Options();
    this->scenes["Character creation"] = new CharacterCreation();
    this->scenes["Shelter menu"] = new ShelterMenu();
    this->scenes["Change event scene"] = new EventScene();
    this->scenes["Battle scene"] = new BattleScene();
    this->scenes["Game over"] = new GameOverScene();

    return true;
}

void DataBase::unloadContent()
{
    for (auto it = this->effects.begin(); it != this->effects.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
        }
    }
    this->effects.clear();

    for (auto it = this->sectors.begin(); it != this->sectors.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
        }
    }
    this->sectors.clear();

    for (auto it = this->aliens.begin(); it != this->aliens.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
        }
    }

    this->aliens.clear();

    for (auto it = this->events.begin(); it != this->events.end(); ++it)
    {
        std::vector<Event*>& vec = it->second;
        for (auto it2 = vec.begin(); it2 != vec.end(); ++it2)
        {
            if (*it2)
            {
                delete *it2;
            }
        }

        vec.clear();
    }

    this->events.clear();

    for (std::map<std::string, Scene*>::iterator it = this->scenes.begin(); it != this->scenes.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
        }
    }

    this->scenes.clear();

    for (std::map<std::string, Weapon*>::iterator it = this->weapons.begin(); it != this->weapons.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
        }
    }

    this->weapons.clear();

    for (std::map<std::string, Mix_Chunk*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it)
    {
        if (it->second)
        {
            Mix_FreeChunk(it->second);
            std::cout << "Sound " << it->first << " unloaded" << std::endl;
        }
    }

    this->sounds.clear();

    for (std::map<std::string, Mix_Music*>::iterator it = this->musics.begin(); it != this->musics.end(); ++it)
    {
        if (it->second)
        {
            Mix_FreeMusic(it->second);
            std::cout << "Music " << it->first << " unloaded" << std::endl;
        }
    }

    this->musics.clear();

    for (std::map<std::string, Image*>::iterator it = this->images.begin(); it != this->images.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
            std::cout << "Image " << it->first << " unloaded" << std::endl;
        }
    }

    this->images.clear();

    for (std::map<std::string, SDL_Cursor*>::iterator it = this->cursors.begin(); it != this->cursors.end(); ++it)
    {
        if (it->second)
        {
            SDL_FreeCursor(it->second);
            std::cout << "Cursor " << it->first << " unloaded" << std::endl;
        }
    }

    this->cursors.clear();

    if (this->font)
    {
        TTF_CloseFont(this->font);
        this->font = nullptr;
    }
}
