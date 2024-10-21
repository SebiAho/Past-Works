#include "Input.h"


Input::Input(void)
{
}


Input::~Input(void)
{
}

int Input::Ninput(std::string description)
{
	char i = -1;
	std::cout << description << std::endl;//Valinnan esittely
	std::cin >> i;
	std::cout << std::endl;//Asettaa valin

	return (int)i - (int)'0';
}

bool Input::Cinput(std::string description)
{
	bool b = false;
	std::string c;
	std::cout << description << std::endl;//Valinnan esittely
	std::cin >> c;
	std::cout << std::endl;//Asettaa valin

	if(c == "y" || c == "Y" ||c == "yes"||c == "Yes")
	{
		b = true; 
	}
	else
	{
		b = false;
	}
	
	return b;
}