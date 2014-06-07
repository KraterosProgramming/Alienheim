#pragma once
#include <string>
#include "Change.h"

class AttrChange : public Change
{
public:
    static const float healthFactor;
    static const float randomFactor;

    AttrChange(int quantity);
    virtual ~AttrChange() { }

    virtual void perform() override;
    virtual int getIncrement();

    virtual SDL_Color getColor() override;
    virtual std::string getString() override;


    char getSign();

    virtual int& getAttr() = 0;
    virtual int& getMaxAttr() = 0;
    virtual std::string getName() = 0;

    int quantity, increment;
};

class HealthChange : public AttrChange
{
public:
    HealthChange(int quantity) : AttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};

class EnergyChange : public AttrChange
{
public:
    EnergyChange(int quantity) : AttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};

class FoodChange : public AttrChange
{
public:
    FoodChange(int quantity) : AttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};
