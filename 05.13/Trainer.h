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
	Trainer(string name, int balls, int potions, int pokemoncount, int selectedIndex = 0);		//Konstruktorok
	~Trainer();
	
	void Print();																				//A datok kiírása standard kimenetre
	bool catchPokemon(Pokemon & newpokemon);													// Új pokemonkerülhet gyűjteményünkbe
	void switchtoIndex(int index);																// Kiválasztjuk a Pokemonunkat
	void usePotion();																			// Jelenleg kiválasztottra elhasználjuk a potinkat
	void usePotion(int a);																		// Adott indexûre elhasználhatjuk a potinkat
	void linkArray(Pokemon * Pokemons, int Pokemoncount);										// Hozzá csatolunk egy pokemonokból álló tömböt emberünkhöz
	void linktoArray(Pokemon & newpokemon);														// Egyetlen egy pokemont hozzácsatolunk tömbünkhöz.
	void list();																				// Ki listázzuk pokemonjainkat
	void setBalls(int count);																	//(labdák számán változtatunk)
	void setPotions(int count);																	// Potik számán változtatunk
	void battle(Creature & enemy);																// Harc egy Creature ellen
	void battle(Pokemon & enemy);																// Harc egy Pokemon ellen
	bool alivePokemons();																		// Van-e még használható pokemon?
	bool currentisUsable();																		// Jelenleg kiválasztott használható még?
	Pokemon * getpokemons();																	// Getter a tömbünkre
	Trainer& operator=(const Trainer & other);													// = túl terhelése
};