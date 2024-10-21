#include "Enemy.h"


Enemy::Enemy(char n[30], int hp, int a, int d, int md, int im_loc, int im_size)
{
	strcpy(Name,n);

	HP = hp;
	Attack = a;
	Defence = d;
	M_Defence = md;

	Image_Location = im_loc;
	image_size = im_size;

	b_methods = Battle_Methods();
}


Enemy::~Enemy(void)
{
}

int Enemy::Actions(int counter, int p_defence, int com)
{
	return 0;
}


