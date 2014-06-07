#include "Scene.h"
#include <iostream>

Scene::Scene()
{

}

Scene::~Scene()
{
    for (int l = 0; l < nLayer; ++l)
    {
        for (std::vector<Object*>::iterator it = this->objects[l].begin(); it != this->objects[l].end(); ++it)
        {
            if (*it)
            {
                delete *it;
            }
        }

        this->objects[l].clear();
    }
}

void Scene::draw()
{
    for (int l = 0; l < nLayer; ++l)
    {
        std::vector<Object*> newList;

	    for (std::vector<Object*>::iterator it = this->objects[l].begin(); it != this->objects[l].end(); ++it)
        {
            if (*it)
            {
                (*it)->draw();
                if ((*it)->dead)
                {
                    delete *it;
                    *it = nullptr;
                }
                else
                {
                    newList.push_back(*it);
                }
            }
            else
            {
                std::cout << "Warning null object" << std::endl;
            }
        }

        this->objects[l].clear();
        this->objects[l].insert(this->objects[l].begin(), newList.begin(), newList.end());
    }
}

void Scene::takeEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            if (this->hotkeys.count(event.key.keysym.sym))
            {
                this->hotkeys[event.key.keysym.sym]->click();
            }
        }
    }
}
