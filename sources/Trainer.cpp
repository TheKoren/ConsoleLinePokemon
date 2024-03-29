#include "../includes/Trainer.h"



Trainer::Trainer()
{
}

Trainer::Trainer(string name, int balls, int potions, int pokemoncount, int selectedIndex) : name(name), balls(balls), selectedIndex(selectedIndex), potions(potions), pokemoncount(pokemoncount)
{
	pokemons = nullptr;
	pokemoncount = 0;
}


Trainer::~Trainer()
{
	delete[] pokemons;
}

void Trainer::Print()
{
	cout << "Name: " << name << "Number of balls: " << balls << "Number of potions " << potions << endl;
}

bool Trainer::catchPokemon(Pokemon & newpokemon)
{
	bool ongoingcatch = true;
	char c; //choice

	while (ongoingcatch && (balls > 0))
	{
		cout << "Balls left: " << balls << "Do you want to continue?" << endl;
		cout << "Type \"Y\", if you want to continue\"N\", if you don't want to continue." << endl;
		cin >> c;
		cin.ignore(10000, '\n');
		if (cin.fail())
		{
			throw ios_base::failure("Cin fail");
		}cout << endl;
		switch (c) {
		case 'Y':
		{
			balls -= 1;
			if (rand() % 5 > 2)
			{
				cout << "Success!" << endl;
				Pokemon * poke = new Pokemon(newpokemon);
				poke->setHp(6.0);
				linktoArray(*poke);
				ongoingcatch = false;
				return true;
				
			}
			else
			{
				cout << "Failure!" << endl;
				break;
			}

		}
		case 'N': cout << "Pokemon flees away!" << endl; ongoingcatch = false; return false;
		default: cout << "Unknown input!" << endl; break;
		}
	}return false;
}

void Trainer::switchtoIndex(int index)
{
	selectedIndex = index - 1; // Mert azt akarom, hogy a listn�l ne legyen 0
}

void Trainer::usePotion()
{
	if (pokemons[selectedIndex].getHp() <= 0)
	{
		cout << "Pokemon is dead. Can't heal";
		return;
	}
	if (potions > 0)
	{
		if (pokemons[selectedIndex].getHp()+10 > pokemons[selectedIndex].getMaxHp())
		{
			cout << "Can't heal the selected pokemon" << endl; return;
		}
		else

		{
			pokemons[selectedIndex].setHp(pokemons[selectedIndex].getHp() + 10);
			potions -= 1;
			cout << pokemons[selectedIndex].getName() << " healed. Current hp: " << pokemons[selectedIndex].getHp() << ". Amount of potions left: " << potions << endl;
		}
	}
	else
	{
		cout << "You have no potions left. " << endl;
	}

}

void Trainer::usePotion(int a)
{
	a = a - 1;
	if ((a < 0)||a>(pokemoncount-1))
	{
		throw ios_base::failure("Wrong idx given");
	}
	if (pokemons[a].getHp() <= 0)
	{
		cout << "Pokemon is dead. Can't heal";
		return;
	}
	if (potions > 0)
	{
		if (pokemons[a].getHp() + 10 > pokemons[a].getMaxHp())
		{
			cout << "Can't heal the selected pokemon" << endl; return;
		}
		else

		{
			pokemons[a].setHp(pokemons[a].getHp() + 10);
			potions -= 1;
			cout << pokemons[a].getName() << " healed. Current hp: " << pokemons[a].getHp() << ". Amount of potions left: " << potions << endl;
		}
	}
	else
	{
		cout << "You have no potions left. " << endl;
	}
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
		cout << "[" << i + 1 << "] - " << pokemons[i].getName() << "\t" << pokemons[i].getHp() << "\t";
		if (pokemons[i].getHp() > 5)
		{
			cout << "Usable" << endl;
		}
		else
			cout << "Not usable" << endl;
	}
}

void Trainer::battle(Creature & enemy)
{
	system("cls");
	double atk;
	char c;
	int idx;
	bool endofbattle = false;
	cout << "Cool battle-music playing" << endl;
	cout << "The battle take place here and now." << endl;
	if (!currentisUsable())
	{
		cout << "Your current Pokemon is not usable.";
		list();
		do {
			cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
		} while (!((idx <= pokemoncount) && (idx > 0) && (pokemons[idx - 1].getHp() > 5.0)));
		switchtoIndex(idx);
	}
	do {
		cout << "Your pokemon: "; pokemons[selectedIndex].Print();
		cout << "Your enemy: "; enemy.Print();
		cout << "------------------It's your turn!. H - Heal, M - Moves, S - Switch Pokemons, R - Retreat-----------" << endl;
		cin >> c;
		switch (c)
		{
		case 'h':;
		case 'H': usePotion(); cout << endl; cout << endl; break;
		case 'm':;
		case 'M': pokemons[selectedIndex].listAbility(); do { cout << "Index of desired move: " << endl; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
		} while (!((idx <= pokemons[selectedIndex].getcount()) && (idx > 0))); 	atk = pokemons[selectedIndex].getAbility(idx-1).use(pokemons[selectedIndex], enemy); enemy.setHp(enemy.getHp() - atk); cout << endl; break;
		case 's':;
		case 'S': list(); 
			do { cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
			} while (!((idx <= pokemoncount) && (idx > 0)&&pokemons[idx-1].isAlive()));
			switchtoIndex(idx); cout << endl; break;
		case 'r':;
		case 'R': cout << "You cannot retreat now" << endl; cout << endl; break;
		default: cout << "Your pokemon stood still, waiting to get killed" << endl; cout << endl; break;
		}
		cout << "------------------------------------It's your enemys turn!------------------------------------" << endl;
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
				list(); do { cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
				} while (!((idx <= pokemoncount) && (idx > 0) && pokemons[idx - 1].isAlive())); switchtoIndex(idx);
			}
		}
		else
		{
			endofbattle = true;
			cout << "You did not survive the encounter" << endl;
		}

	} while (!endofbattle);

	enemy.setHp(enemy.getMaxHp());

	pokemons[selectedIndex].lvlup((rand() % 25) + 1);
	cout << "Type a char to continue: ";
	cin >> c;
	cin.ignore(10000, '\n');
	system("cls");
}

void Trainer::battle(Pokemon & enemy)
{
	system("cls");
	double atk;
	char c;
	int idx;
	bool endofbattle = false;
	bool signal = false;
	cout << "Cool battle-music playing" << endl;
	cout << "The battle take place here and now." << endl;
	if (!currentisUsable())
	{
		cout << "Your current Pokemon is not usable.";
		list();
		do {
			cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
		} while (!((idx <= pokemoncount) && (idx > 0)&& (pokemons[idx-1].getHp()>5.0)));
		switchtoIndex(idx);
	} 
	
	do {
		cout << "Your pokemon: "; pokemons[selectedIndex].Print();
		cout << "Your enemy: "; enemy.Print();
		cout << "--------------------It's your turn!. H - Heal, M - Moves, S - Switch Pokemons, R - Retreat, C - Catch---------------------" << endl;
		cin >> c;
		switch (c)
		{
		case 'h':;
		case 'H': usePotion(); cout << endl; break;
		case 'm':;
		case 'M': pokemons[selectedIndex].listAbility(); do { cout << "Index of desired move: " << endl; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number"); } while (!((idx <= pokemons[selectedIndex].getcount()) && (idx > 0))); 	atk = pokemons[selectedIndex].getAbility(idx - 1).use(pokemons[selectedIndex], enemy); enemy.setHp(enemy.getHp() - atk); break; //TODO: Hogy adjam �t, hogy ne legyen rossz?
		case 's':;
		case 'S': list(); do { cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
		} while (!((idx <= pokemoncount) && (idx > 0) && pokemons[idx - 1].isAlive())); switchtoIndex(idx); cout << endl; cout << endl; break;
		case 'r':;
		case 'R': cout << "You cannot retreat now" << endl; cout << endl; break;
		case 'c':;
		case 'C': if (enemy.getHp() > 7) { cout << "Enemy is too strong to catch it" << endl; cout << endl; cout << endl; break; }
				  else { signal = catchPokemon(enemy); cout << endl; break; }
		default: cout << "Your pokemon stood still, waiting to get killed" << endl;
		}
		if (!signal)
		{
			cout << "------------------------------------It's your enemys turn!------------------------------------" << endl;
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
					list(); do { cout << "Index of desired pokemon(choose an eligible one: "; cin >> idx; if (cin.fail()) throw ios_base::failure("String!=Number");
					} while (!((idx <= pokemoncount) && (idx > 0) && pokemons[idx - 1].isAlive())); switchtoIndex(idx);
				}
			}
			else
			{
				endofbattle = true;
				cout << "You did not survive the encounter" << endl;
			}
		}
		else
			endofbattle = true;

	} while (!endofbattle);

	enemy.setHp(enemy.getMaxHp());

	cout << "Type a char to continue: ";
	cin >> c;
	cin.ignore(10000, '\n');
	system("cls");
}

bool Trainer::alivePokemons()
{
	for (int i = 0; i < pokemoncount; i++)
	{
		if (pokemons[i].getHp() > 5.0)
			return true;
	}
	return false;
}

bool Trainer::currentisUsable()
{
	if (pokemons[selectedIndex].getHp() > 5.0)
	{
		return true;
	}
	else
		return false;

}

Pokemon * Trainer::getpokemons()
{
	return pokemons;
}

Trainer & Trainer::operator=(const Trainer & other)
{
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