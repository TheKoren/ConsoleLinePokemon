#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>

using namespace std;

enum Type{Water, Fire, Grass, Neutral};  //Neutral csak ability lehet

class Creature {
private:
	double hp;
	string name;
	double basedmg;
	const int maxhp;
public:
	Creature();
	Creature(double hp, string name, double basedmg, int maxhp); // Konstruktor && Destuktor
	~Creature() {};
	Creature(const Creature & other);

	string getName()const; // Getterek
	double getHp()const;
	double getBaseDmg() const;
	int getMaxHp()const;

	virtual void Print(); //Mindenféle diagnosztika, lekérdezõ, harc
	virtual bool isAlive();
	virtual void setHp(double newhp);
	virtual double attack();; // Ez valami sima crit chances legyen
};
