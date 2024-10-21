#include "Enemy_Basic.h"


Enemy_Basic::Enemy_Basic(char n[30], int hp, int a, int d, int md, int im_loc, int im_size):Enemy(n,hp,a,d,md, im_loc, im_size)
{
}


Enemy_Basic::~Enemy_Basic(void)
{
}

int Enemy_Basic::Actions(int counter, int p_defence, int com)
{
	int damage = 0;

	if(counter == 2 || counter == 3 || counter == 5 || counter == 6)
	{
		damage = b_methods.Damage(Attack,p_defence);
		printf("%s attacks with %i damage\n\n",Name,damage);
	}
	else
	{
		printf("%s is preparing to attack\n\n",Name);
	}

	return damage;
}


