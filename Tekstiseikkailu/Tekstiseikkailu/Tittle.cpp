#include "Tittle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Battle.h"
#include "Shop.h"

#define EXIT 0//sammutus tilan arvo
#define DEFAULT -1//vakio tilan arvo

Tittle::Tittle(void)
{
	GameState = DEFAULT;
	
	std::cout<<"SEBI'S TEXT-TOURNAMENT\n\n";
	
	Start();
	Main_loop();

}


Tittle::~Tittle(void)
{
	delete player;
}

void Tittle::Main_loop()
{
	int Select = 0;
	Shop shop = Shop();
	while(GameState != EXIT)
	{
		switch(Select)//Pää valikko
		{
		case 1:
			player->PlayerStats();
			Select = DEFAULT;
			break;

		case 2:
			Battle_Select();
			Select = DEFAULT;
			break;

		case 3:
			
			shop.Shop_Selection(player);

			Select = DEFAULT;
			break;

		case 4:
			Exit();
			Select = DEFAULT;
			break;

		default:
			Select = input.Ninput("Select what you want to do\n 1 Player Status \t 2 Battle \t 3 Shop \t 4 Exit Game\n");		
		}		
	}
}

void Tittle::Start()
{
	bool i = input.Cinput("Do you want to start a new game?\nY = new\nN = continue\n");
	
	if(i == true)
	{
		i = input.Cinput("Are you sure?\nYes \t No\n");
				
		if(i == true)
		{
			printf("Write player name\n");
			char temp[31];
			scanf("%s",temp);

			player = new Player(temp);
		}
	}
	else
	{
		if(saveGame.error != 1)
		{
			player = saveGame.Load();		
		}
		
	}
}

void Tittle::Exit()//Lopetus metodi
{
	bool i = false;
	i = input.Cinput("Do you want to end your game?\n y = Yes \t n = No\n");
	if(i == true)
	{
		saveGame.Save(*player);
		GameState = EXIT;
	}
}

void Tittle::Battle_Select()
{
	Battle call_battle = Battle();
	call_battle.EnemyList(player->Rank);
	int enem = input.Ninput("");
	if(enem <= player->Rank)
	{
		call_battle.Fight(player,enem-1);
	}
}