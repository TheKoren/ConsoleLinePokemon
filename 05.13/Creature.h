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

	string getName()const;							// Getterek
	double getHp()const;
	double getBaseDmg() const;
	int getMaxHp()const;

	void setBaseDmg(double a);						//Setterek
	void setMaxHp(int a);
	void setName(string a);

	virtual void Print();							//Adatok kiírása
	virtual bool isAlive();							//Él még?
	virtual void setHp(double newhp);				//Szintén setter, de virtual
	virtual double attack(Pokemon & enemy);			// Ahogy kiértékelődik egy lény támadása. aka. mennyit sebez.
	virtual Creature& operator=(const Creature & other);	//= operátor túlterhelése, hogy működjön lények között is.
};