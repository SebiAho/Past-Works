#include "Enemy_Zombie.h"


Enemy_Zombie::Enemy_Zombie(char n[30],int hp, int a, int d, int md, int im_loc, int im_size):Enemy(n,hp,a,d,md, im_loc, im_size)
{
}


Enemy_Zombie::~Enemy_Zombie(void)
{
}

int Enemy_Zombie::Actions(int counter, int p_defence, int com)
{
	int damage = 0;

	if(counter % 2 == 1)
	{
		printf("Zombie is slowly moving towards you\n\n");
	}
	else
	{
		damage = b_methods.Damage(Attack,p_defence);
		printf("%s attacks with %i damage\n\n",Name,damage);
	}

	return damage;
}