#pragma once

#include "Player.h"

class SaveGame
{
public:
	SaveGame(void);
	~SaveGame(void);

	void Save(Player player);
	Player* Load();

	int error;
};

