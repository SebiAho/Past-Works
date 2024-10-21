#pragma once
#include "Enemy.h"

class Enemy_Zombie : public Enemy
{
public:
	Enemy_Zombie(char n[30],int hp, int a, int d, int md, int im_loc, int im_size);
	~Enemy_Zombie(void);

	int Actions(int counter, int p_defence, int com);

};

