#include "SaveGame.h"
#include <stdio.h>
#include <stdlib.h>

SaveGame::SaveGame(void)
{
}


SaveGame::~SaveGame(void)
{
}

void SaveGame::Save(Player player)//Tallentaa pelaajan tiedot tekstitiedostoon
{
	Player &pplayer = player;
	char name;
	fpos_t pos;
	FILE *file;
	file=fopen("Saves.txt","w+");
	if(!file)//Tarkastaa saako tiedoston avattua
	{
		printf("error can't open file");
		error = 1;
	}
	fprintf(file,"%s %i %i %i %i %i %i %i %i",player.Name,player.Strength,player.Magick,player.Defence,player.Gold,
										player.Rank,player.weapon_rank,player.spell_rank,player.armor_rank);//Tallentaa pelaajan tiedot

	fclose(file);
}

Player* SaveGame::Load()//Hakee pelaajan tiedot tekstitiedostosta
{
	char n[31];
	int str=0, mag=0,def=0,gold=0,rank=1,wrank=0,srank=0,arank=0;
	FILE *file;
	file=fopen("Saves.txt","r");
	if(!file)//Tarkastaa saako tiedoston avattua
	{
		printf("error can't open file");
	}
	
	fscanf(file,"%s",&n);//Lis‰‰ pelaajan tiedot listaan
		
	fscanf(file,"%i",&str);

	fscanf(file,"%i",&mag);

	fscanf(file,"%i",&def);

	fscanf(file,"%i",&gold);

	fscanf(file,"%i",&rank);
	
	fscanf(file,"%i",&wrank);

	fscanf(file,"%i",&srank);

	fscanf(file,"%i",&arank);

	fclose(file);

	return new Player(n,str,mag,def,gold,rank,wrank,srank,arank);
}
