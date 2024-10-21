#include "Battle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Print_Text_Image.h"
#include "Battle_Methods.h"
#include "Input.h"

#include "Enemy_Basic.h"
#include "Enemy_Zombie.h"
#include "Enemy_The_Boss.h"
#include "Enemy_Secret_Boss.h"

Battle::Battle()
{
	Enemies.push_back(new Enemy_Basic("Wolf",100,30,-10,-10, 97, 12));
	Enemies.push_back(new Enemy_Zombie("Zombie",200,50,10,-10,109,9));
	Enemies.push_back(new Enemy_Basic("Ghost",300,40,100,-30, 119,16));
	Enemies.push_back(new Enemy_The_Boss("The Boss",500,50,0,0,134,19));
	Enemies.push_back(new Enemy_Secret_Boss("Secret Boss",1000,100,-30,-30,191,22));

}


Battle::~Battle(void)
{
	for(int i = 0; i < Enemies.size(); i++)
		{
			delete Enemies[i];
		}
}

void Battle::Fight(Player* player, int _enem)
{
	enem = _enem;

	int playerD = player->Defence;//Asettaa suojauksen normaaliksi
	
	int round = 1, counter = 1, com = 0, damage;

	playerHP = player->HP;
	enemyHP = Enemies[enem]->HP;

	Input input;
	Battle_Methods b_methods;

	Print_Enemy_Image();//Print enemy image

	while(playerHP > 1 && enemyHP > 1)//Taistelu silmukka
	{
		printf("----------Round %i----------\n",round);//Tulostaa taistelu erän ruudulle
		printf("enemy Hit-points %i \nplayer hit-points %i\n\n",enemyHP, playerHP);//Printaa pelaajan ja vastustajan tiedot

		com = input.Ninput("Choose the fight command\n1 Attack\n2 Magick\n3=Guard\n");
		damage = 0;
		if(com == 1)//Suorittaa hyökkays komennon
		{
			damage = b_methods.Damage(player->Strength,Enemies[enem]->Defence);
			enemyHP -= damage;
			
			printf("Your attack did %i damage to the %s\n", damage,Enemies[enem]->Name);
		}
		else if(com == 2)
		{
			damage = b_methods.Damage(player->Magick,Enemies[enem]->M_Defence);
			enemyHP -= damage;
			
			printf("Your spell did %i damage to the %s\n", damage,Enemies[enem]->Name);
		}
		else//Suorittaa suojaus komennon
		{
			playerD = b_methods.Guard(player->Defence);//Nostaa sadalla erän ajaksi
		}


		playerHP -= Enemies[enem]->Actions(counter, playerD, com);
		playerD = 0;
		//Laskuri --------------------------------------
		if(counter == 6)//Nollaa laskurin
		{
			counter = 1;
		}
		else
		{
			counter++;
		}
		round++;//Nostaa erän numeroa
		}
	Result(player);
}

void Battle::Print_Enemy_Image()
{
	Print_Text_Image print;
	char temp[20][17];
	print.PrintTextImage(temp,Enemies[enem]->Image_Location,Enemies[enem]->image_size);
}

void Battle::Result(Player *player)
{
	int Gold = 0,Rank = 0;
	if(playerHP <= 0)
	{
		printf("GAME OVER\n\n");
	}
	else if(enemyHP <= 0)
	{
		if(enem == 0)
		{
			Rank = 2;
			Gold = 300;
			printf("You have Slayed the Wolf\n\n");
		}
		if(enem == 1)
		{
			Rank = 3;
			Gold = 500;
			printf("You have Rekilled the Zombie\n\n"); 
		}
		if(enem == 2)
		{
			Rank = 4;
			Gold = 1000;
			printf("The Ghost is Dead....Again\n\n");
		}
		if(enem == 3)
		{
			Rank = 5;
			Gold = 10000;
			printf("Conratulations you have defeated The Boss and with it this game!!!\n\n");
		}
		if(enem == 4)
		{
			Rank = 5;
			Gold = 100000;
			printf("The Secret Boss has fallen!!!\n\n");
		}
		player->Gold += Gold;
		if(player->Rank < Rank)//Tarkastaa onko uusi taso enemmän kuin pelaajalla
		{
			player->Rank = Rank;
		}
	}
	else
	{
		printf("%s has slayed you before it's final breath",Enemies[enem]->Name);
	}

}


void Battle::EnemyList(int rank)
{
	printf("What enemy do you want to fight?\n");
	for(int i = 0; i < rank; i++)
	{
		printf("%i. %s\n",i+1,Enemies[i]->Name);
	}
	printf("%i. Exit",Enemies.size()+1);
}