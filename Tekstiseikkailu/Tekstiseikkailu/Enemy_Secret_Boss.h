#pragma once
#include "Enemy.h"

class Enemy_Secret_Boss:public Enemy
{
public:
	Enemy_Secret_Boss(char n[30],int hp, int a, int d, int md, int im_loc, int im_size);
	~Enemy_Secret_Boss(void);

	int Actions(int counter, int p_defence, int com);//Vihollisen toiminnot
};

