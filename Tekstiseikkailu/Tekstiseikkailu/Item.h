#pragma once
class Item
{
public:
	Item(char n[30], int pow, int cost, int r, int im_loc,int im_size);
	~Item(void);

	char name[30];
	int power, price, rank, image_loc, image_size;
};

