#pragma once
#include "Pokemon.h"

class Trainer {
private:
	string name;
	int pokemoncount;
	Pokemon * pokemons;
	int balls;
	int selectedIndex;
	int potions;
public:
	Trainer();
	Trainer(string name, int balls, int potions, int pokemoncount, int selectedIndex=0);
	~Trainer();
	Trainer(const Trainer & other);

	void Print();
	void catchPokemon(Pokemon & newpokemon); //�j Pokemon ker�l a t�mb�nkbe
	void switchtoIndex(int index); //Kiv�lasztjuk a Pokemonunkat
	void usePotion(); // Adott index�re elhaszn�lhatjuk a potinkat
	void linkArray(Pokemon * Pokemons, int Pokemoncount); // Hozz� csatolunk egy pokemonokb�l �ll� t�mb�t ember�nkh�z
	void linktoArray(Pokemon & newpokemon);
	void list(); //Ki list�zzuk pokemonjainkat
	void setBalls(int count); //(labd�k sz�m�n v�ltoztatunk)
	void setPotions(int count); // Potik sz�m�n v�ltoztatunk
	void battle(Creature & enemy); // Ha trainer�nk csat�zik (A user!!) akkor egy creaturrel �ll majd szemben. (Ha nem Trainerrel) Ezen bel�l switches case-s megold�s lesz + dowhile mert minden addig megy m�g valaki elhal
	bool alivePokemons();
};