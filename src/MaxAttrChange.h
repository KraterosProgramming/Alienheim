#pragma once
#include <string>
#include "AttrChange.h"

class MaxAttrChange : public AttrChange
{
public:
    MaxAttrChange(int quantity) : AttrChange(quantity) { }
    virtual void perform() override;
};

class MaxHealthChange : public MaxAttrChange
{
public:
    MaxHealthChange(int quantity) : MaxAttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};

class MaxEnergyChange : public MaxAttrChange
{
public:
    MaxEnergyChange(int quantity) : MaxAttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};

class MaxFoodChange : public MaxAttrChange
{
public:
    MaxFoodChange(int quantity) : MaxAttrChange(quantity) { }
    virtual int& getAttr() override;
    virtual int& getMaxAttr() override;
    virtual std::string getName() override;
};
