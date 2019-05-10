#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Trainer.h"

class Story {
private:
	int id;
	char text[4000];
	int nextright;
	int nextleft;
	static int wildstart;
	static int arenastart;
	static int elementnum;
public:
	Story();
	Story(int id, int nextright, int nextleft, char * szoveg);
	~Story();
	void Print();
	int getright();
	int getleft();
	int getarena();
	int getwild();
	int getid();
};


