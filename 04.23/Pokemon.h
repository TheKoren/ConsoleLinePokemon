#pragma once
#include "Creature.h"

/*Mivel a Pokemon �s a Move el�g szoros kapcsolatban �llnak, �gy k�nyelmesebb egy�tt kezelni �ket.  /TODO: J� ez �gy? /*/ 
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
	Move getAbility(int idx)const;

	void Print(); //Diagnosztika && harc &&  other shit
	bool lvlup(int newgrowth);
	bool isAlive();
	void setHp(double newhp);
	void listAbility();
	double attack( Pokemon & enemy); // AI!
	void linkAbilitys(Move * abilitys, int count);
	void linkAbility(Move & Ability);
	Pokemon& operator=(Pokemon & other);

};

class Move {
private:
	Type own;  // Ez igaz�b�l nem is k�ne, ha meglehetne azt oldani, hogy pl. V�z pokemonhoz csak v�z ability menjen. (vagy neutral) / TODO: K�rdezd Labvezt /
	Type weakness;
	string name;
	double succfaktor;
	double failfaktor;
public:
	Move();
	Move(Type own, Type weakness, string name, double succfaktor = 1.25, double failfaktor = 0.75);
	~Move();
	Move(const Move & other);

	string getName(); //Getter

	double use(Pokemon & owner, const Creature & enemy);//Valamilyen sz�m�t�s alapj�n ki adja a sebz�st, + ki irog�l diagnosztikai adatokat
	void Print() { cout << "Name: " << name << endl; }
};

