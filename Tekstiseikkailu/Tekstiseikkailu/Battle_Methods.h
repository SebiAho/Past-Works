#pragma once
class Battle_Methods
{
public:
	Battle_Methods(void);
	~Battle_Methods(void);

	int Damage(int attack, int defence);//Hy�kk�yksen tekem� vahinko
	int Guard(int defence);//Pelaajan suojaus
};

