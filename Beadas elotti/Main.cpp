#include "Story.h"
#include <ios>
#include <fstream>
#include <exception>

Story* controller(int *d) {
	ifstream fp;
	fp.open("controll.txt");
	if (!fp.is_open())
	{
		throw exception("File not found");
	}

	int n, index, left, right;
	char c;
	char text[4000];
	fp >>c>> n;
	if (fp.fail())
	{
		fp.close();
		throw exception("Couldn't scan the number of coming elements");
	}
	*d = n;
	Story * array = new Story[n];
	if (array == nullptr)
	{
		throw exception("new not working");
	}
	for (int i = 0; i < n; i++)
	{
		fp >> index >> left >> right;
		if (fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan the data");
		}
		fp.getline(text, 3999);
		if(fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan the text");
		}
		array[index] = Story(index, left, right, text);
	}
	fp.close();
	return array;
}

Creature* createcreatures(int * d) {
	ifstream fp;
	fp.open("creature.txt");
	if(!fp.is_open())
	{
		throw exception("File not found");
	}
	int n;
	char c;
	fp >> c >> n;
	if(fp.fail())
	{
		fp.close();
		throw exception("Couldn't scan the number of elements coming");
	}
	*d = n;
	double hp, basedmg;
	char name[30];
	Creature * array1 = new Creature[n];
	if (array1 == nullptr)
	{
		throw exception("new not working");
	}
	for (int i = 0; i < n; i++)
	{
		fp >> hp >> name >> basedmg;
		if(fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan data");
		}
		array1[i] = Creature(hp, name, basedmg, hp);
	}
	fp.close();
	return array1;
}

Pokemon* createpokemons(int *d)
{
	ifstream fp;
	fp.open("pokemons.txt");
	if(!fp.is_open())
	{
		throw exception("File not found");
	}
	int n;
	char c;
	fp >> c >> n;
	if(fp.fail())
	{
		fp.close();
		throw exception("Couldn't scan the number of elements coming.");
	}
	*d = n;
	double hp, basedmg, succfak, failfak;
	int own, weakness, lvl, growth, abcount;
	Type own1, weakness1;
	char name[20];
	Move v;
	Pokemon * array2 = new Pokemon[n];
	if (array2 == nullptr)
	{
		throw exception("new not working");
	}
	for (int i = 0; i < n; i++)
	{
		fp >> hp >> name >> basedmg >> own >> weakness >> lvl >> growth;
		if (fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan data");
		}
		switch (own) {
		case 1: own1 = Water; break;
		case 2: own1 = Fire; break;
		case 3: own1 = Grass; break;
		default: break; //exception? 
		}
		switch (weakness) {
		case 1: weakness1 = Water; break;
		case 2: weakness1 = Fire; break;
		case 3: weakness1 = Grass; break;
		default: break; //exception?

		}
		array2[i] = Pokemon(hp, name, basedmg, hp, own1, weakness1, lvl, growth);
		fp >> c >> abcount;
		if (fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan the number of elements coming");
		}
		for (int k = 0; k < abcount; k++) {
			fp >> own >> name >> succfak >> failfak;
			if (fp.fail())
			{
				fp.close();
				throw exception("Couldn't scan data");
			}
			switch (own) {
			case 1: own1 = Water; break;
			case 2: own1 = Fire; break;
			case 3: own1 = Grass; break;
			default: own1 = Neutral; break;
			}
			Move v(own1, name, succfak, failfak);
			array2[i].linkAbility(v);
		}
	}
	fp.close();
	return array2;
}

Trainer* createArena(Pokemon * array, int d) {
	ifstream fp;
	fp.open("arena.txt");
	if (!fp.is_open())
	{
		throw exception("File not found");
	}
	int n;
	char c;
	fp >> c >> n;
	if (fp.fail())
	{
		fp.close();
		throw exception("Couldn't scan the number of elements coming");
	}
	Trainer * op = new Trainer[n];
	if (op == nullptr)
	{
		throw exception("new not working");
	}
	char name[20];
	int g, balls, potions, elementNum, selectedIndex;
	int a = d - 3; // Ne legyen olyan pokemonja a többi trainernek mint nekünk
	for (int i = 0; i < n; i++)
	{
		fp >> name >> balls >> potions >> elementNum >> selectedIndex;
		if (fp.fail())
		{
			fp.close();
			throw exception("Couldn't scan data");
		}
		op[i] = Trainer(name, balls, potions, elementNum, selectedIndex);
		g = rand() % a + 3;
		op[i].linktoArray(array[g]);
	}
	fp.close();
	return op;
}

int main() {
	
	srand(time(NULL));			// A randomizált számok mások legyenek, minden lefutáskor.

	int crethossz;				// Szükséges tömbök deklarálása, feltöltése, lekezelése.
	int storyhossz;
	int pokhossz;
	Story * control;
	Creature * creatures;
	Pokemon * pokemons;
	Trainer * arenaop;
	try {
		control = controller(&storyhossz);
		creatures = createcreatures(&crethossz);
		pokemons = createpokemons(&pokhossz);
		arenaop = createArena(pokemons, pokhossz);
	}
	catch (exception&ex) { cout << ex.what(); exit(1); } // Ha hiba van, lépjen ki.

	char choice;										//Choice- választásunk, hogy hogyan menjünk tovább. Dice-random fgv eredménye + switchIdx-et is használom ezzel.
	int dice, currentnode = 0, opponents = 0;			//Currentnode- Jelenleg hol vagyunk a storyban Opponents-
	string name;


	cout << "Welcome! Type your name: "; getline(cin, name); Trainer Player(name, 10, 2, 0, 0); // Karakterünk megalkotása

	cout << "Pokemon name\tHP\tStatus" << endl; // Pokemonjaink kilistázása, és hozzáadása a Userhez
	Player.linktoArray(pokemons[0]);
	Player.linktoArray(pokemons[1]);
	Player.linktoArray(pokemons[2]);
	Player.list();

	control[currentnode].Print();				// A kezdet

	try {
		do {
			cout << "Choices: (R)IGHT, (L)EFT, (H)EAL, (P)okemonlist E(X)IT" << endl;
			cin >> choice;
			cin.ignore(10000, '\n');
			switch (choice) {
			case 'r':;
			case 'R': {currentnode = control[currentnode].getright(); 
				if (control[currentnode].getright() == control[currentnode].getleft() && control[currentnode].getright() == storyhossz - 1) {
					choice = 'X';
					control[currentnode].Print(); break;
				}
				else if (control[currentnode].getid() >= control[currentnode].getarena()) {
					control[currentnode].Print();
					Player.battle(arenaop[opponents].getpokemons()[0]); opponents++;   break;
				}

				else if (control[currentnode].getid() > control[currentnode].getwild() && control[currentnode].getid() < control[currentnode].getarena())
				{
					dice = rand() % 3;
					if (dice == 2)
					{
						Player.battle(creatures[rand() % crethossz]);
					}  control[currentnode].Print(); break;

				}

			} control[currentnode].Print(); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break;
			case 'l':;
			case 'L': {currentnode = control[currentnode].getleft();
				if (control[currentnode].getright() == control[currentnode].getleft()) {
					choice = 'X';  control[currentnode].Print();
					break;
				}
				else if (control[currentnode].getid() > control[currentnode].getarena()) {
					control[currentnode].Print();
					Player.battle(arenaop[opponents].getpokemons()[0]);  opponents++;
						break;
				}


				else if ((control[currentnode].getid() >= control[currentnode].getwild()) && (control[currentnode].getid() <= control[currentnode].getarena()))
				{
					dice = rand() % 3;
					if (dice == 2)
					{
						Player.battle(creatures[rand() % crethossz]);
					}  control[currentnode].Print(); break;

				}

			}  control[currentnode].Print(); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break;
			case 'h':;
			case 'H': Player.list(); cin >> dice; if (cin.fail()) {  throw ios_base::failure("Char!=num");}Player.usePotion(dice); Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break;
			case 'x':;
			case 'X': cout << "Are you sure, you want to quit? X-Let me gooo | N-Nope" << endl; cin >> choice; if (choice == 'X') { choice = 'X'; Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break; }
					  else if (choice == 'N') { choice = 'Y'; cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl;  break;
												}
			case 'p':;
			case 'P': Player.list(); cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break;
			default:  cout << "Wrong Input" << endl; cout << "."; Sleep(500); cout << "."; Sleep(500); cout << "." << endl; break;
			}
		} while (choice != 'X' || !(Player.alivePokemons()));
	}
	catch (ios_base::failure&ex) { cin.clear(); cout << ex.what(); exit(1); }
	cout << "And the END is here. Don't forget to come back!:)" << endl;
	cout << "Type something, to exit: ";
	cin >> choice;

	delete[] control;			// Felszabadítás
	delete[] creatures;
	delete[] pokemons;
	delete[] arenaop;

	getchar();
	return 0;
}