#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include "Windows.h"
#define WAIT cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl;
using namespace std;

enum Type { Water, Fire, Grass, Neutral };  //Neutral csak ability lehet

class Pokemon;

/*class Base{
private:
double hp;
string name;
double basedmg;
const int maxhp;
public:
Base()
~Base()
---
TODO: Ez, hogy működjön a heterogén kollekció?
}*/

class Creature {
private:
	double hp;
	string name;
	double basedmg;
	int maxhp;
public:
	Creature();
	Creature(double hp, string name, double basedmg, int maxhp); // Konstruktor && Destuktor
	~Creature();
	Creature(const Creature & other);

	string getName()const; // Getterek
	double getHp()const;
	double getBaseDmg() const;
	int getMaxHp()const;

	void setBaseDmg(double a) { basedmg = a; }
	void setMaxHp(int a) { maxhp = a; }
	void setName(string a) { name = a; }

	virtual void Print(); //Mindenféle diagnosztika, lekérdezõ, harc
	virtual bool isAlive();
	virtual void setHp(double newhp);
	virtual double attack(Pokemon & enemy); // Ez valami sima crit chances legyen
	Creature& operator=(const Creature & other) {
		this->hp = other.hp;
		this->name = other.name;
		this->basedmg = other.basedmg;
		this->maxhp = other.maxhp;
		return *this;
	}
};