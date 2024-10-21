#pragma once
#include "Input.h"
#include "Player.h"
#include "SaveGame.h"

class Tittle
{
public:
	Tittle(void);
	~Tittle(void);

	int getGameState;
	int setGameState;
	Player *player;
	SaveGame saveGame;

private:
	int GameState;

	void Main_loop();

	void Start();
	void Exit();
	void Battle_Select();
	Input input;
};

