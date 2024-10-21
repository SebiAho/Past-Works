#pragma once
#include <string>

#include <iostream>

class Input
{
public:
	Input(void);
	~Input(void);

	int Ninput(std::string description);//Ottaa int tyyppisen valinnan
	bool Cinput(std::string description);//Ottaa yes/no tyyppisen valinnan
};

