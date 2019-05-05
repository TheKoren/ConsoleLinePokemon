#include "Trainer.h"



Trainer::Trainer()
{
}

Trainer::Trainer(string name, int balls, int potions, int pokemoncount, int selectedIndex) : name(name), balls(balls), selectedIndex(selectedIndex), potions(potions), pokemoncount(pokemoncount)
{
	pokemons = nullptr;
}


Trainer::~Trainer()
{
	delete[] pokemons;
}

Trainer::Trainer(const Trainer & other)
{
	name = other.name;
	balls = other.balls;
	selectedIndex = other.selectedIndex;
	potions = other.potions;
	pokemoncount = other.pokemoncount;
	Pokemon * tmp = new Pokemon[pokemoncount];
	for (int i = 0; i < pokemoncount; i++)
	{
		tmp[i] = other.pokemons[i];
	}
	pokemons = tmp;
}

void Trainer::Print()
{
	cout << "Name: " << name << "Number of balls: " << balls << "Number of potions " << potions << endl;
}

void Trainer::catchPokemon(Pokemon & newpokemon)
{
	bool ongoingcatch = true;
	char c; //choice

	while (ongoingcatch && (balls > 0))
	{
		cout << "Balls left: " << balls << "Do you want to continue?" << endl;
		cout << "Type \"Y\", if you want to continue\"N\", if you don't want to continue." << endl;
		cin >> c; cout << endl;
		switch (c) {
		case 'Y':
		{
			balls -= 1;
			if (rand() % 5 > 2)
			{
				cout << "Success!" << endl;
				newpokemon.setHp(5);
				linktoArray(newpokemon);
				ongoingcatch = false;
				break;
			}
			else
			{
				cout << "Failure!" << endl;
				break;
			}

		}
		case 'N': cout << "Pokemon flees away!" << endl; ongoingcatch = false; break;
		default: cout << "Unknown input!" << endl; break;
		}

	}
}

void Trainer::switchtoIndex(int index)
{
	selectedIndex = index - 1; // Mert azt akarom, hogy a listnél ne legyen 0
}

void Trainer::usePotion()
{
	if (potions > 0)
	{
		pokemons[selectedIndex].setHp(pokemons[selectedIndex].getHp() + 10);
		potions -= 1;
		cout << pokemons[selectedIndex].getName() << " healed. Current hp: " << pokemons[selectedIndex].getHp() << ". Amount of potions left: " << potions << endl;
	}
	else
	{
		cout << "You have no potions left. " << endl;
	}

}

void Trainer::linkArray(Pokemon * Pokemons, int Pokemoncount)
{
	pokemons = Pokemons;
	pokemoncount = Pokemoncount;
}

void Trainer::linktoArray(Pokemon & newpokemon)
{
	Pokemon * tmp = new Pokemon[pokemoncount + 1];
	for (int i = 0; i < pokemoncount; i++)
	{
		tmp[i] = pokemons[i];
	}
	tmp[pokemoncount] = newpokemon;
	delete[] pokemons;
	pokemons = tmp;
	pokemoncount += 1;
}

void Trainer::list()
{
	for (int i = 0; i < pokemoncount; i++)
	{
		cout << "[" << i + 1 << "] - " << pokemons[i].getName() << " " << pokemons[i].getHp() << " ";
		if (pokemons[i].getHp() > 5)
		{
			cout << "Usable" << endl;
		}
		else
			cout << "Not usable" << endl;
	}
}

void Trainer::setBalls(int count)
{
	balls = count;
}

void Trainer::setPotions(int count)
{
	potions = count;
}

void Trainer::battle(Creature & enemy)
{
	bool endofbattle = false;
	cout << "Cool battle-music playing" << endl;
	cout << "The battle take place here and now." << endl;
	double atk;
	char c;
	Creature * ptr;
	int idx;
	do {
		cout << "Your pokemon: "; pokemons[selectedIndex].Print();
		cout << "Your enemy: "; enemy.Print();
		cout << "It's your turn!. H - Heal, M - Moves, S - Switch Pokemons, R - Retreat" << endl;
		cin >> c;
		switch (c)
		{
		case 'H': usePotion(); break;
		case 'M': pokemons[selectedIndex].listAbility(); cout << "Index of desired move: " << endl; cin >> idx; cout << endl; 	atk = pokemons[selectedIndex].getAbility(idx).cruse(pokemons[selectedIndex], enemy); enemy.setHp(enemy.getHp() - atk); break; //TODO: Hogy adjam át, hogy ne legyen rossz?
		case 'S': list(); cout << "Index of desired pokemon: " << endl; do { cin >> idx; } while (pokemons[idx - 1].getHp() > 5); cout << endl; switchtoIndex(idx); break;
		case 'R': cout << "You cannot retreat now" << endl; break;
		default: cout << "Your pokemon stood still, waiting to get killed" << endl;
		}
		cout << "It's your enemys turn!" << endl;
		if (enemy.getHp() > 0.0)
		{
			atk = enemy.attack();
			pokemons[selectedIndex].setHp(pokemons[selectedIndex].getHp() - atk);
		}
		else
		{
			cout << "Your enemy did not survive" << endl;
			endofbattle = true;
		}
		if (alivePokemons())
		{
			if (pokemons[selectedIndex].getHp() <= 0.0)
			{
				cout << "Your pokemon died! Choose a new one: " << endl;
				list(); cout << "Index of desired pokemon(choose an eligible one): " << endl; do { cin >> idx; } while (pokemons[idx - 1].getHp() > 5); cout << endl; switchtoIndex(idx);
			}
		}
		else
			endofbattle = true;
		cout << "Did not survive the encounter" << endl;

	} while (!endofbattle);
}

void Trainer::battle(Pokemon & enemy)
{
	bool endofbattle = false;
	cout << "Cool battle-music playing" << endl;
	cout << "The battle take place here and now." << endl;
	double atk;
	char c;
	Creature * ptr;
	int idx;
	do {
		cout << "Your pokemon: "; pokemons[selectedIndex].Print();
		cout << "Your enemy: "; enemy.Print();
		cout << "It's your turn!. H - Heal, M - Moves, S - Switch Pokemons, R - Retreat" << endl;
		cin >> c;
		switch (c)
		{
		case 'H': usePotion(); break;
		case 'M': pokemons[selectedIndex].listAbility(); cout << "Index of desired move: " << endl; cin >> idx; cout << endl; 	atk = pokemons[selectedIndex].getAbility(idx).pruse(pokemons[selectedIndex], enemy); enemy.setHp(enemy.getHp() - atk); break; //TODO: Hogy adjam át, hogy ne legyen rossz?
		case 'S': list(); cout << "Index of desired pokemon: " << endl; do { cin >> idx; } while (pokemons[idx - 1].getHp() > 5); cout << endl; switchtoIndex(idx); break;
		case 'R': cout << "You cannot retreat now" << endl; break;
		default: cout << "Your pokemon stood still, waiting to get killed" << endl;
		}
		cout << "It's your enemys turn!" << endl;
		if (enemy.getHp() > 0.0)
		{
			atk = enemy.attack(pokemons[selectedIndex]);
			pokemons[selectedIndex].setHp(pokemons[selectedIndex].getHp() - atk);
		}
		else
		{
			cout << "Your enemy did not survive" << endl;
			endofbattle = true;
		}
		if (alivePokemons())
		{
			if (pokemons[selectedIndex].getHp() <= 0.0)
			{
				cout << "Your pokemon died! Choose a new one: " << endl;
				list(); cout << "Index of desired pokemon(choose an eligible one): " << endl; do { cin >> idx; } while (pokemons[idx - 1].getHp() > 5); cout << endl; switchtoIndex(idx);
			}
		}
		else
			endofbattle = true;
		cout << "Did not survive the encounter" << endl;

	} while (!endofbattle);
}

bool Trainer::alivePokemons()
{
	for (int i = 0; i < pokemoncount; i++)
	{
		if (pokemons[i].getHp() > 0)
			return true;
	}
	return false;
}