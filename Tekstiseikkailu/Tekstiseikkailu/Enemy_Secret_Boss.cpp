#include "Enemy_Secret_Boss.h"


Enemy_Secret_Boss::Enemy_Secret_Boss(char n[30],int hp, int a, int d, int md, int im_loc, int im_size):Enemy(n,hp,a,d,md,im_loc,im_size)
{
}


Enemy_Secret_Boss::~Enemy_Secret_Boss(void)
{
}

int Enemy_Secret_Boss::Actions(int counter, int p_defence, int com)
{
	int damage = 0;

	if(counter == 2)
	{
		damage = Attack/5;
		Defence = -40;
		M_Defence = -20;
		printf("%s does a guard piercing attack for %i damagen\n\n", Name,damage);
	}
	else if(counter == 3)
	{
		damage = 0;
		Defence = 20;
		M_Defence = 40;
		printf("%s is doing notting\n\n", Name);
	}
	else if(counter == 6)
	{
		damage = -100;
		Defence = 100;
		M_Defence = 100;
		printf("%s does a weird attacks\n\n",Name);
	}
	else
	{
		damage = b_methods.Damage(Attack,p_defence);
		Defence = -30;
		M_Defence = -30;
		printf("%s attacks with %i damage\n\n",Name,damage);
	}

	return damage;
}