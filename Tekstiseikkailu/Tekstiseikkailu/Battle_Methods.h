#pragma once
class Battle_Methods
{
public:
	Battle_Methods(void);
	~Battle_Methods(void);

	int Damage(int attack, int defence);//Hyökkäyksen tekemä vahinko
	int Guard(int defence);//Pelaajan suojaus
};

