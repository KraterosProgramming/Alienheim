#include "Behavior.h"

Behavior::~Behavior()
{

}

VoidBehavior::VoidBehavior(void (*f)())
{
	this->f = f;
}

VoidBehavior::~VoidBehavior()
{

}

 void VoidBehavior::call()
{
	this->f();
}

