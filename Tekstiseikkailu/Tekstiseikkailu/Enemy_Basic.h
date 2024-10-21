#pragma once
#include "Enemy.h"

class Enemy_Basic : public Enemy
{
public:
	Enemy_Basic(char n[30],int hp, int a, int d, int md, int im_loc, int im_size);
	~Enemy_Basic(void);

	int Actions(int counter, int p_defence, int com);//Vihollisen toiminnot
};

