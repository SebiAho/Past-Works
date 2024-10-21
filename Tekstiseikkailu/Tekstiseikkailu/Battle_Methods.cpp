#include "Battle_Methods.h"

#include <iostream>

Battle_Methods::Battle_Methods(void)
{
}


Battle_Methods::~Battle_Methods(void)
{
}

int Battle_Methods::Damage(int attack, int defence)//laskee hyökkayksen vahinkon
{
	int damage = attack-defence;//Suojauksen vähennys hykkäyksestä
	if(damage < 0)//estää hyökkäystä muuttumasta negatiiviseksi suojauksen takia
	{
		damage = 0;
	}
	return damage;
}

int Battle_Methods::Guard(int _defence)
{
	int defence = _defence + 20 * 10;
	std::cout<<"Player is Guarding"<<std::endl;

	return defence;
}