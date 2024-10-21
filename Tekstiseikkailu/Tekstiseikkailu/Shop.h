#pragma once

#include <vector>
#include "Item.h"
#include "Player.h"
#include "Input.h"
#include "Print_Text_Image.h"

class Shop
{
public:
	Shop(void);
	~Shop(void);
	void Shop_Selection(Player* player);

private:
	Input input;

	std::vector<Item*> Weapons;
	std::vector<Item*> Spells;
	std::vector<Item*> Armors;
	Print_Text_Image print;

	bool is_better(int item, int rank);
	bool can_afford(int item, int gold);

	void Weapon_transaction(Player* player);
	void Spell_transaction(Player* player);
	void Armor_transaction(Player* player);

};

