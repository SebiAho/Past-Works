#include "Print_Text_Image.h"
#include <stdio.h>
#include <stdlib.h>

Print_Text_Image::Print_Text_Image(void)
{
}


Print_Text_Image::~Print_Text_Image(void)
{
}

int Print_Text_Image::PrintTextImage(char t[][17], int r, int k)//Tulostaa annettujen tietojen m‰‰rittelem‰n kohdan teksti tiedostosta
{
	char f[] = "C_kirjain_kuvat.txt";
	int rivi = 18* r;//Laskee rivinumeron ja asettaa sen muuttujaan
	FILE *file;
	file=fopen(f,"r");

	if(!file)//Tarkastaa saako tiedoston avattua
	{
		printf("error can't open file");
	}

	fseek(file,rivi,SEEK_SET);//Siirtyy haluuttuun kohtaan tiedostossa
	for(int i = 0; i < k; i++)//Tulostaa tiedoston
	{
		fscanf(file, "%s", t[0]);
		printf("%s\n",t[0]);
	}

	fclose(file);
	return 0;
}