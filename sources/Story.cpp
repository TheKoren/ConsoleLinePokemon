#include "../includes/Story.h"

int Story::arenastart = 7;
int Story::wildstart = 3;

Story::Story()
{
}

Story::Story(int id, int nextright, int nextleft, char * szoveg) :id(id), nextright(nextright), nextleft(nextleft)
{
	strcpy(text, szoveg);
}

Story::~Story()
{
}

void Story::Print()
{
	cout << text << endl;
}

int Story::getright()const
{
	return nextright;
}

int Story::getleft()const
{
	return nextleft;
}

int Story::getarena()const
{
	return arenastart;
}

int Story::getwild()const
{
	return wildstart;
}

int Story::getid()const
{
	return id;
}
