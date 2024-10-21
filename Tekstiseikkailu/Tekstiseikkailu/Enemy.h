#pragma once
#include <string>

#include "Battle_Methods.h"

class Enemy
{
public:
	Enemy(char n[30], int hp, int a, int d, int md, int im_loc, int im_size);
	virtual ~Enemy(void);
	virtual int Actions(int counter, int defence, int com);
	
	char Name[30];
	int HP, Attack, Defence, M_Defence, Price, Image_Location, image_size;

protected:

	Battle_Methods b_methods;
};

