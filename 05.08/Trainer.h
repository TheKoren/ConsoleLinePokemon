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
	Trainer(string name, int balls, int potions, int pokemoncount, int selectedIndex = 0);
	~Trainer();
	Trainer(const Trainer & other);

	void Print();
	void catchPokemon(Pokemon & newpokemon); //Új Pokemon kerül a tömbünkbe
	void switchtoIndex(int index); //Kiválasztjuk a Pokemonunkat
	void usePotion(); // Adott indexûre elhasználhatjuk a potinkat
	void linkArray(Pokemon * Pokemons, int Pokemoncount); // Hozzá csatolunk egy pokemonokból álló tömböt emberünkhöz
	void linktoArray(Pokemon & newpokemon);
	void list(); //Ki listázzuk pokemonjainkat
	void setBalls(int count); //(labdák számán változtatunk)
	void setPotions(int count); // Potik számán változtatunk
	void battle(Creature & enemy); // Ha trainerünk csatázik (A user!!) akkor egy creaturrel áll majd szemben. (Ha nem Trainerrel) Ezen belül switches case-s megoldás lesz + dowhile mert minden addig megy míg valaki elhal
	void battle(Pokemon & enemy);
	bool alivePokemons();
	Pokemon * getpokemons() { return pokemons; }
	Trainer& operator=(const Trainer & other) {
		this->name = other.name;
		this->balls = other.balls;
		this->selectedIndex = other.selectedIndex;
		this->pokemoncount = other.pokemoncount;
		this->potions = other.potions;
		Pokemon * tmp = new Pokemon[pokemoncount];
		for (int i = 0; i < pokemoncount; i++)
		{
			tmp[i] = other.pokemons[i];
		}
		pokemons = tmp;
		return *this;
	}
};