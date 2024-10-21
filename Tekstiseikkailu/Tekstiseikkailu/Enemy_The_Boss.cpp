#include "Enemy_The_Boss.h"


Enemy_The_Boss::Enemy_The_Boss(char n[30],int hp, int a, int d, int md,int im_loc, int im_size):Enemy(n,hp,a,d,md,im_loc, im_size)
{
	
}


Enemy_The_Boss::~Enemy_The_Boss(void)
{
}

int Enemy_The_Boss::Actions(int counter, int defence, int com)
{
	int damage = 0;

	if(counter == 1)
	{
		damage = b_methods.Damage(Attack,defence);

		printf("%s attacks with %i damage\n\n",Name,damage);
		
		//Boss vihollisen suojausten muuttaminen
		Defence = 100;
		M_Defence = -20;
		printf("%s is slowing down\n",Name);
		printf("%s is glowing Blue\n\n", Name);

	}
	else if(counter == 2)
	{
		printf("Boss is watching you\n\n");
		
		Defence = -20;//Boss vihollisen suojausten muuttaminen
		M_Defence = 100;
		printf("%s is glowing Red\n\n", Name);
	}
	else if(counter == 3)
	{
		if(com == 1||com == 2)//Tarkastaa käyttikkö pelaaja hyökkäyskomentoa ja ja iskee voimakkaalla iskulla jos käytti
		{
			damage = b_methods.Damage(Attack * 4 ,defence);

			printf("%s counters your attack with %i damage \n\n",Name, damage);
		}
		else
		{
			printf("%s is failed to attack you \n\n",Name);
		}
		Defence = 100;//Boss vihollisen suojausten muuttaminen
		M_Defence = -20;
		printf("%s is glowing Blue\n\n", Name);
	}
	else if(counter == 4)
	{
		damage = b_methods.Damage(Attack ,defence);
		printf("%s attacks with %i damage\n\n",Name,damage);

		Defence = -20;
		M_Defence = 100;
		printf("%s is gathering power\n", Name);
		printf("%s is glowing Red\n\n", Name);

	}
	else if(counter == 5)
	{
		printf("%s is a about to release a powerful attack\n\n",Name);
		Defence = 100;//Boss vihollisen suojausten muuttaminen
		M_Defence = -20;
		printf("%s is glowing Blue\n\n",Name);
	}
	else if(counter == 6)
	{
		damage = b_methods.Damage(Attack ,defence);
		printf("%s attacks with %i damage\n\n",Name,damage);
		Defence = -20;//Boss vihollisen suojausten muuttaminen
		M_Defence = 100;
		printf("%s is glowing Red\n\n",Name);
	}
	return damage;
}
