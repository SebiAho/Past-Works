#pragma once

#include <vector>
#include "Enemy.h"
#include "Player.h"

class Battle
{
public:
	Battle();
	~Battle(void);

	void Fight(Player* _player, int _enem);
	void EnemyList(int rank);

private:
	int enem, playerHP, enemyHP;
	std::vector<Enemy*> Enemies;
	Player* player;

	void Print_Enemy_Image();
	void Result(Player *player);//Suorittaa voiton/häviön seuraukset
	

};

