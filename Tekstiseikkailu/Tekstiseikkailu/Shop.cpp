#include "Shop.h"
#include <iostream>


Shop::Shop(void)
{
	Weapons.push_back(new Item("Axe",30,100,1,0,17));
	Weapons.push_back(new Item("Sword",60,300,2,17,21));
	Weapons.push_back(new Item("Katana",100,1000,3,153,21));

	Spells.push_back(new Item("Fireball",30,100,1,38,10));
	Spells.push_back(new Item("Ligthning",60,300,2,48,15));
	Spells.push_back(new Item("Meteor",100,1000,3,174,17));
	
	Armors.push_back(new Item("Helmet",5,200,1,76,10));
	Armors.push_back(new Item("Shield",10,200,2,63,13));
	Armors.push_back(new Item("Breastplate",20,500,3,86,10));

}


Shop::~Shop(void)
{
	for(int i = 0; i < Weapons.size(); i++)
	{
		delete Weapons[i];
	}

	for(int i = 0; i < Spells.size(); i++)
	{
		delete Spells[i];
	}

	for(int i = 0; i < Armors.size(); i++)
	{
		delete Armors[i];
	}
}

void Shop::Shop_Selection(Player* player)
{
	
	int select = 4, select2 = 0;
	
	select = input.Ninput("What do want to buy?\n\n 1. Weapon\n 2. Spell\n 3. Armor\n 4. Exit\n");
	if(select == 1)
	{
		Weapon_transaction(player);
	}
	else if(select == 2)
	{
		Spell_transaction(player);

	}
	else if(select == 3)
	{
		Armor_transaction(player);
	}
	else
	{
		return;
	}
}

bool Shop::is_better(int item, int rank)
{
	if(rank < item)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Shop::can_afford(int item, int gold)
{
	if( gold >= item)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Shop::Weapon_transaction(Player* player)
{
	int select = Weapons.size()+2;
	bool choose = false;
	char im[30][17];//Kuvan asetus taulukko

	std::cout<<"Which weapon do you want to buy?"<<std::endl;
	for(int i = 0; i < Weapons.size(); i++)//Print the item list
	{
		if(is_better(Weapons[i]->rank,player->weapon_rank))
		{
			std::cout<< i+1 << ". " << Weapons[i]->name <<std::endl;
		}
	}
	std::cout<<Weapons.size()+1<< ". " << "Exit" <<std::endl;
	select = input.Ninput("");

	if(select-1 >= Weapons.size())//Check if select is larger tha item list
	{
		return;
	}

	if(select <= Weapons.size())
	{
		if(is_better(Weapons[select-1]->rank, player->weapon_rank))//Check the weapon rank
		{
			if(can_afford(Weapons[select-1]->price,player->Gold))//Check item is affordable
			{
				print.PrintTextImage(im,Weapons[select-1]->image_loc,Weapons[select-1]->image_size);//Print image
				std::cout<<"Price: "<< Weapons[select-1]->price <<std::endl;
				std::cout<<"Player gold: " << player->Gold << std::endl;

				choose = input.Cinput("Do you Want to boy this? Yes/No");
				if(choose == true)
				{
					player->weapon_rank = Weapons[select-1]->rank;
					player->Strength = Weapons[select-1]->power;
					player->Gold -= Weapons[select-1]->price;
				}
				else
				{
					return;
				}
			}
			else
			{
				std::cout<<"Not enough gold"<<std::endl;
			}
		}
	}
}

void Shop::Spell_transaction(Player* player)
{
	int select = Spells.size()+2;
	bool choose = false;
	char im[30][17];//Kuvan asetus taulukko

	std::cout<<"Which spell do you want to buy?"<<std::endl;
	for(int i = 0; i < Spells.size(); i++)//Print the item list
	{
		if(is_better(Spells[i]->rank,player->spell_rank))
		{
			std::cout<< i+1 << ". " << Spells[i]->name <<std::endl;
		}
	}
	std::cout<<Spells.size()+1<< ". " << "Exit" <<std::endl;

	select = input.Ninput("");
	if(select-1 >= Spells.size())//Check if select is larger tha item list
	{
		return;
	}

	if(select <= Spells.size()+1)
	{
		if(is_better(Spells[select-1]->rank, player->spell_rank))//Check the weapon rank
		{
			if(can_afford(Spells[select-1]->price,player->Gold))//Check item is affordable
			{
				print.PrintTextImage(im,Spells[select-1]->image_loc,Spells[select-1]->image_size);//Print image
				std::cout<<"Price: "<< Spells[select-1]->price <<std::endl;
				std::cout<<"Player gold: " << player->Gold << std::endl;

				choose = input.Cinput("Do you Want to boy this? Yes/No");
				if(choose == true)
				{
					player->spell_rank = Spells[select-1]->rank;
					player->Magick = Spells[select-1]->power;
					player->Gold -= Spells[select-1]->price;
				}
			}
			else
			{
				std::cout<<"Not enough gold"<<std::endl;
			}
		}
	}
}

void Shop::Armor_transaction(Player* player)
{
	int select = Armors.size()+2;
	bool choose = false;
	char im[30][17];//Kuvan asetus taulukko

	std::cout<<"Which armor do you want to buy?"<<std::endl;
	for(int i = 0; i < Armors.size(); i++)//Print the item list
	{
		if(is_better(Armors[i]->rank,player->armor_rank))
		{
			std::cout<< i+1 << ". " << Armors[i]->name <<std::endl;
		}
	}
	std::cout<<Armors.size()+1<< ". " << "Exit" <<std::endl;
	select = input.Ninput("");
	if(select-1 >= Spells.size())//Check if select is larger tha item list
	{
		return;
	}

	if(select <= Armors.size()+1)
	{
		if(is_better(Armors[select-1]->rank, player->armor_rank))//Check the weapon rank
		{
			if(can_afford(Armors[select-1]->price,player->Gold))//Check item is affordable
			{
				print.PrintTextImage(im,Armors[select-1]->image_loc,Armors[select-1]->image_size);//Print image
				std::cout<<"Price: "<< Spells[select-1]->price <<std::endl;
				std::cout<<"Player gold: " << player->Gold << std::endl;

				choose = input.Cinput("Do you Want to boy this? Yes/No");
				if(choose == true)
				{
					player->armor_rank = Armors[select-1]->rank;
					player->Defence = Armors[select-1]->power;
					player->Gold -= Armors[select-1]->price;
				}
			}
			else
			{
				std::cout<<"Not enough gold"<<std::endl;
			}
		}
	}
}