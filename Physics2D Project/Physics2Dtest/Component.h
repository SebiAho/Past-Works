#pragma once

#include "SystemEnums.h"

class Component
{
public:
	Component(Comp _id);
	virtual ~Component();

	Comp getId(){ return id; };

private:
	Comp id;
};

