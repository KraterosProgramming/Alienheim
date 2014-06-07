#pragma once
#include <string>

class Behavior
{
public:
    virtual ~Behavior();
    virtual void call() = 0;
};

class VoidBehavior : public Behavior
{
public:
    VoidBehavior(void (*f)());
    virtual ~VoidBehavior();
    virtual void call();

    void (*f)();
};

template<typename FT, typename DT = FT>
class TBehavior : public Behavior
{
public:
    TBehavior(void (*f)(FT), DT data);
    virtual ~TBehavior();
    virtual void call();

    void (*f)(FT);
    DT data;
};

template<typename FT, typename DT>
TBehavior<FT, DT>::TBehavior(void (*f)(FT), DT data)
{
	this->f = f;
	this->data = data;
}

template<typename FT, typename DT>
TBehavior<FT, DT>::~TBehavior()
{

}

template<typename FT, typename DT>
void TBehavior<FT, DT>::call()
{
	this->f(data);
}

typedef TBehavior<bool> BoolBehavior;
typedef TBehavior<int> IntBehavior;
typedef TBehavior<const std::string&, std::string> StringBehavior;
