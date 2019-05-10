#pragma once
#include "Creature.h"

/*Mivel a Pokemon és a Move elég szoros kapcsolatban állnak, így kényelmesebb együtt kezelni õket.  /TODO: Jó ez így? /*/
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
	Pokemon(double hp, string name, double basedmg, int maxhp, Type own, Type weakness, int lvl = 1, int growth = 0);
	~Pokemon();
	Pokemon(const Pokemon & other); // Konstuktorok && destruktor

	string getName()const; //Getterek
	double getBaseDmg()const;
	Type getWeakness()const;
	Type getOwn()const;
	double getHp()const;
	int getcount()const;
	Move getAbility(int idx)const;


	void Print(); //Diagnosztika && harc &&  other shit
	bool lvlup(int newgrowth);
	bool isAlive();
	void setHp(double newhp);
	void listAbility();
	double attack(Pokemon & enemy); // AI!
	void linkAbilitys(Move * abilitys, int count);
	void linkAbility(Move & Ability);
	Pokemon& operator=(const Pokemon & other);

};

class Move {
private:
	Type own;  //TODO: Nem lenne rossz, csak nem jó Ez igazából nem is kéne, ha meglehetne azt oldani, hogy pl. Víz pokemonhoz csak víz ability menjen. (vagy neutral) / TODO: Kérdezd Labvezt /
	string name;
	double succfaktor;
	double failfaktor;
public:
	Move();
	Move(Type own , string name, double succfaktor = 1.25, double failfaktor = 0.75);
	~Move();
	Move(const Move & other);

	string getName(); //Getter

	double use(Pokemon & owner, Pokemon & enemy);
	double use(Pokemon & owner, Creature & enemy);
	void Print() { cout << "Name: " << name << endl; }
};