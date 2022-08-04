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
	Story();														// Konstuktorok
	Story(int id, int nextright, int nextleft, char * szoveg);
	~Story();

	void Print();													// A story kiírása

	int getright()const;													//Getterek
	int getleft()const;
	int getarena()const;
	int getwild()const;
	int getid()const;
};


