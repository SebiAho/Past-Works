#include "Battle_Methods.h"

#include <iostream>

Battle_Methods::Battle_Methods(void)
{
}


Battle_Methods::~Battle_Methods(void)
{
}

int Battle_Methods::Damage(int attack, int defence)//laskee hy�kkayksen vahinkon
{
	int damage = attack-defence;//Suojauksen v�hennys hykk�yksest�
	if(damage < 0)//est�� hy�kk�yst� muuttumasta negatiiviseksi suojauksen takia
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