#include "Item.h"
#include <string>

Item::Item(char n[30], int pow, int cost, int r, int im_loc,int im_size)
{
	strcpy(name,n);
	power = pow;
	price = cost;
	rank = r;

	image_loc = im_loc;
	image_size = im_size;

}


Item::~Item(void)
{
}
