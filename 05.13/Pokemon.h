#pragma once
#include "Creature.h"

/*Mivel a Pokemon és a Move elég szoros kapcsolatban állnak, így kényelmesebb együtt kezelni õket.*/
class Move;

class Pokemon : public Creature {
private:
	Type own;
	Type weakness;
	int lvl;
	int growth;
	Move * ability;
	int abilitycount;
public:
	Pokemon();
	Pokemon(double hp, string name, double basedmg, int maxhp, Type own, Type weakness, int lvl = 1, int growth = 0);			// Konstuktorok && destruktor
	~Pokemon();

	string getName()const;																//Getterek
	double getBaseDmg()const;
	Type getWeakness()const;
	Type getOwn()const;
	double getHp()const;
	int getcount()const;
	Move getAbility(int idx)const;
	int getlvl()const;


	void Print();										// Adatok kiírása standard kimenetre
	bool lvlup(int newgrowth);							// Fejlődés
	bool isAlive();										// Él még a Pokemon?
	void setHp(double newhp);							//Setter
	void listAbility();									//Képességek listázása
	double attack(Pokemon & enemy);						//Ha ez egy AI pokemon, hogyan értékelődik ki a támadása
	void linkAbilitys(Move * abilitys, int count);		// NEM HASZNÁLT
	void linkAbility(Move & Ability);					//Hozzá csatol egy képességet a pokemonhoz
	Pokemon& operator=(const Pokemon & other);			//= operátor túlterhelése.

};

class Move {
private:
	Type own; 
	string name;
	double succfaktor;
	double failfaktor;
public:
	Move();																							//Konstruktorok
	Move(Type own , string name, double succfaktor = 1.25, double failfaktor = 0.75);
	~Move();
	Move(const Move & other);

	string getName();																				//Getter

	double use(Pokemon & owner, Pokemon & enemy);													//Képességek használata különböző ellenfelek esetén.
	double use(Pokemon & owner, Creature & enemy);
	void Print() { cout << "Name: " << name << endl; }												//Adatok kiírása
};