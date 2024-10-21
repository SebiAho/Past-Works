#include "Player.h"
#include <iostream>
#include <string>

Player::Player(char n[31])
{
	strcpy(Name,n);
	Strength = 20;
	Magick = 20;
	Defence = 0;
	Gold = 0;
	Rank = 1;
	HP = 100;

	weapon_rank = 0;
	spell_rank = 0;
	armor_rank = 0;
}


Player::Player(char n[31], int str, int mag, int def, int gold, int rank, int wrank, int srank, int arank)
{
	HP = 100;

	strcpy(Name,n);

	Strength = str;
	Magick = mag;
	Defence = def;
	Gold = gold;
	Rank = rank;
	weapon_rank = wrank;
	spell_rank = srank;
	armor_rank = arank;
}


Player::~Player(void)
{
}

void Player::PlayerStats()
{
	std::cout<< Name<< std::endl;
	std::cout<< "\nHP: " << HP << std::endl;
	std::cout<< "\nStrength: "<< Strength <<std::endl;
	std::cout<< "\nMagick: "<< Magick << std::endl;
	std::cout<< "\nDefence: "<< Defence << std::endl;
	std::cout<< "\nGold: "<< Gold << std::endl;
	std::cout<< "\nRank: "<< Rank << std::endl << std::endl;

}