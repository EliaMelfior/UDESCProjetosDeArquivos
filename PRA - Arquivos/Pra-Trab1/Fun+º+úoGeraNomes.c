#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RelatoriosClimaticos.bin"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

char NamePrefix[][6] = {
 //who said we need to add a prefix?
	"join", //lets say that means "the good"
	"curi", //"The not so good as Bel"
	"são", //"The evil"
	"bom", //"the good"
	"flori", //"the neutral/natral"
	"jara", //Man am I original
};

char NameSuffix[][5] = {
	"wat", "rio", "lua", "sol", "marte"
};

const char NameStems[][5] = {
	"ba", "ville", "paulo", "joao", "teste"
};

void NameGen(char* PlayerName)
{
	PlayerName[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(PlayerName, NamePrefix[(rand() % 7)]);
	//add the stem...
	fflush(stdin);
	strcat(PlayerName, NameStems[(rand() % 20)]);
	//add the suffix...
	fflush(stdin);
	strcat(PlayerName, NameSuffix[(rand() % 16)]);
	//Make the first letter capital...
	fflush(stdin);
	PlayerName[0]=toupper(PlayerName[0]);
	fflush(stdin);
	return;
}

int main(void)
{
		srand((long)time(NULL));
		char playerName[21];
		NameGen(playerName);
		printf("%s", playerName);	
}	