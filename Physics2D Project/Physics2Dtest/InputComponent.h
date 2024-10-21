#pragma once
#include "Component.h"

#include <vector>
#define InpComponent(x) dynamic_cast<InputComponent*>(x.getComponent(Comp::INPUT))

class InputComponent : public Component
{
public:
	InputComponent();
	~InputComponent();

	std::vector<int> input; //Contains info of what input applies to the object
};

