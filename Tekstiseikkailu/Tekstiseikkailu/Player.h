#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player(char n[31]);
	Player(char n[31], int str, int mag, int def, int gold, int rank, int wrank, int srank, int arank);
	~Player(void);

	void PlayerStats();//N‰ytt‰‰ pelaajan tiedot

	//Get Set Methods
	std::string getName();
	void setName(char v[]);
	
	char Name[31];
	int HP, Strength, Magick, Defence, Gold, Rank;
	int weapon_rank, spell_rank, armor_rank;
	
private:

};

