#pragma once
#include "Enemy.h"

class Enemy_The_Boss : public Enemy
{
public:
	Enemy_The_Boss(char n[30],int hp, int a, int d, int md,int im_loc, int im_size);
	~Enemy_The_Boss(void);

	int Actions(int counter, int p_defence, int com);
};

