#include "BattleScene.h"
#include "util.h"
#include "App.h"
#include <sstream>
#include <cstdlib>

BattleScene::BattleScene()
{
    this->ericAttacking = false;
    this->ericFleed = false;
    this->alienAttacking = false;

    this->health = new Label(155, 15, 95, "0/0", white);
    this->character = new Picture(15, 105, nullptr);
    this->weapon = new Picture(15, 105, nullptr);
    this->background = new Picture(15, 105, nullptr);

    this->alienHealth = new Label(670, 15, 95, "0/0", white);
    this->alien = new Picture(530, 105, nullptr);

    this->attackButton = new Button(280, 395, "Attack!", new VoidBehavior(BattleScene::attack));
    this->fleeButton = new Button(280, 435, "Flee", new VoidBehavior(BattleScene::flee));

    // Eric health
    this->objects[MIDDLE].push_back(new Label(15, 15, 120, "Health", white));
    this->objects[MIDDLE].push_back(new Bar(135, 15, 135, 23, App::percentHealth, {63, 0, 0, 255}, {191, 0, 0, 255}));
    this->objects[FRONT].push_back(this->health);

    // Eric picture
    this->objects[BACKGROUND].push_back(this->background);
    this->objects[BACK].push_back(this->weapon);
    this->objects[MIDDLE].push_back(this->character);

    // Alien health
    this->objects[MIDDLE].push_back(new Label(530, 15, 120, "Health", white));
    this->objects[MIDDLE].push_back(new Bar(650, 15, 135, 23, App::alienPercentHealth, {63, 0, 0, 255}, {191, 0, 0, 255}));
    this->objects[FRONT].push_back(this->alienHealth);

    // Alien picture
    this->objects[MIDDLE].push_back(this->alien);

    // Buttons
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_a] = this->attackButton);
    this->objects[MIDDLE].push_back(this->hotkeys[SDLK_f] = this->fleeButton);
}

void BattleScene::open()
{
    this->ericAttacking = false;
    this->ericFleed = false;
    this->alienAttacking = false;

    std::stringstream ss;

    ss.str("");
    ss << std::max(0, App::character->health) << "/" << App::character->maxHealth;
    this->health->text = ss.str();
    this->health->renderText();

    this->character->image = App::character->image;
    this->background->image = App::character->background;
    this->weapon->image = App::character->weapon->image;

    ss.str("");
    ss << std::max(0, App::alien->health) << "/" << App::alien->maxHealth;
    this->alienHealth->text = ss.str();
    this->alienHealth->renderText();

    this->alien->image = App::alien->image;

    Mix_PlayChannel(-1, App::alien->battleCry, 0);
}

void BattleScene::update()
{
    if (App::character->health <= 0 && !this->alienAttacking)
    {
        App::changeScene("Game over");
    }
    else if (this->ericAttacking)
    {
        BattleScene::checkAttack();
    }
    else  if (this->ericFleed)
    {
        BattleScene::checkFlee();
    }
    else if (App::alien->health <= 0)
    {
        App::character->maxHealth += 0.05f * App::alien->maxHealth;
        App::character->maxEnergy += 0.05f * App::alien->energy;
        ++App::character->killCount;
        App::changeScene("Shelter menu");
    }
    else if (this->alienAttacking)
    {
        BattleScene::checkAlienAttack();
    }

    this->attackButton->enable = this->fleeButton->enable = !(this->ericAttacking || this->alienAttacking || this->ericFleed);
}

void BattleScene::attack()
{
    BattleScene* bs = (BattleScene*)App::currentScene;
    bs->ericAttacking = true;
    bs->ticks = SDL_GetTicks();

    Mix_PlayChannel(-1, App::character->weapon->attack.sound, 0);
    App::alien->health -= App::character->weapon->attack.getRandomDamage(App::character->maxEnergy);

    std::stringstream ss;
    ss.str("");
    ss << std::max(0, App::alien->health) << "/" << App::alien->maxHealth;
    bs->alienHealth->text = ss.str();
    bs->alienHealth->renderText();

    int x = bs->alien->x + (bs->alien->image->w - App::character->weapon->attack.effect->frameW) / 2;
    int y = bs->alien->y + (bs->alien->image->h - App::character->weapon->attack.effect->frameH) / 2;
    bs->objects[FOREGROUND].push_back(new EffectInstance(x, y, App::character->weapon->attack.effect));
}

void BattleScene::flee()
{
    BattleScene* bs = (BattleScene*)App::currentScene;
    bs->ericFleed = true;
    bs->ticks = SDL_GetTicks();

    Mix_PlayChannel(-1, App::db.sounds["flee"], 0);

    if (BattleScene::randomFleeFunction())
    {
        App::changeScene("Shelter menu");
    }
}

void BattleScene::alienAttack()
{
    BattleScene* bs = (BattleScene*)App::currentScene;
    bs->alienAttacking = true;
    bs->ticks = SDL_GetTicks();

    Mix_PlayChannel(-1, App::alien->attack.sound, 0);
    App::character->health -= App::alien->attack.getRandomDamage(App::alien->energy);

    std::stringstream ss;

    ss.str("");
    ss << std::max(0, App::character->health) << "/" << App::character->maxHealth;
    bs->health->text = ss.str();
    bs->health->renderText();

    int x = bs->weapon->x + (bs->weapon->image->w - App::alien->attack.effect->frameW) / 2;
    int y = bs->weapon->y + (bs->weapon->image->h - App::alien->attack.effect->frameH) / 2;
    bs->objects[FOREGROUND].push_back(new EffectInstance(x, y, App::alien->attack.effect));
}

void BattleScene::checkAttack()
{
    BattleScene* bs = (BattleScene*)App::currentScene;

    if (SDL_GetTicks() - bs->ticks >= 500)
    {
        bs->ericAttacking = false;
		if (App::alien->health > 0)
		{
			bs->alienAttack();
		}
    }
}

void BattleScene::checkFlee()
{
    BattleScene* bs = (BattleScene*)App::currentScene;

    if (SDL_GetTicks() - bs->ticks >= 500)
    {
        bs->ericFleed = false;
		if (App::alien->health > 0)
		{
			bs->alienAttack();
		}
    }
}

void BattleScene::checkAlienAttack()
{
    BattleScene* bs = (BattleScene*)App::currentScene;

    if (SDL_GetTicks() - bs->ticks >= 500)
    {
        bs->alienAttacking = false;
    }
}

bool BattleScene::randomFleeFunction()
{
    int a = App::character->energy;
    int b = App::alien->energy;

    return rand() % (a + b) < a;
}
