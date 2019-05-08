#define _CRT_SECURE_NO_WARNINGS

#include "Trainer.h"


class Story {
private:
	int id;
	char text[4000];
	int nextright;
	int nextleft;
	static int wildstart;
	static int arenastart;
	static int elementnum;
public:
	Story() {};
	Story(int id, int nextright, int nextleft, char * szoveg) :id(id), nextright(nextright), nextleft(nextleft) { strcpy(text, szoveg); }
	~Story() {};
	void Print() { cout << text << endl; }
	int getright() { return nextright; }
	int getleft() { return nextleft; }
	int getarena() { return arenastart; }
	int getwild() { return wildstart; }
	int getid() { return id; }
};
int Story::arenastart = 7;
int Story::wildstart = 3;

Story* controller(int *d) {
	FILE *fp = fopen("controll.txt", "r");
	if (fp == NULL)
	{
		cout << "geci";
	}
	//exception vagy miafasz?
	int n, index, left, right;
	char text[4000];
	fscanf(fp, "#%d", &n);
	*d = n;
	Story * array = new Story[n];
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%d\t%d\t%d\t", &index, &left, &right);
		fgets(text, 3999, fp);
		array[index] = Story(index, left, right, text);
	}
	fclose(fp);
	return array;
}

Creature* createcreatures(int * d) {
	FILE * fp = fopen("creature.txt", "r");
	//s
	int n;
	fscanf(fp, "#%d", &n);
	*d = n;
	double hp, basedmg;
	char name[30];
	Creature * array1 = new Creature[n];
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%lf\t%s\t%lf", &hp, name, &basedmg);
		array1[i] = Creature(hp, name, basedmg, hp);
	}
	fclose(fp);
	return array1;
}
Pokemon* createpokemons(int *d)
{
	FILE *fp = fopen("pokemons.txt", "r");
	//exp
	int a;
	fscanf(fp, "#%d", &a);
	*d = a;
	double hp, basedmg, succfak, failfak;
	int own, weakness, lvl, growth, abcount;
	Type own1, weakness1;
	char name[20];
	Move v;
	Pokemon * array2 = new Pokemon[a];
	for (int i = 0; i < a; i++)
	{
		fscanf(fp, "%lf\t%s\t%lf\t%d\t%d\t%d\t%d\n", &hp, name, &basedmg, &own, &weakness, &lvl, &growth);
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
		fscanf(fp, "#%d", &abcount);
		for (int k = 0; k < abcount; k++) {
			fscanf(fp, "%d\t%s\t%lf\t%lf", &own, name, &succfak, &failfak);
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
	fclose(fp);
	return array2;
}

Trainer* createArena(Pokemon * array, int d) {
	FILE * fp = fopen("arena.txt", "r");
	//exp
	int n;
	fscanf(fp, "#%d", &n);
	Trainer * op = new Trainer[n];
	char name[20];
	int g, balls, potions, elementNum, selectedIndex;
	int a = d - 3; // ennyi 
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%s\t%d\t%d\t%d\t%d", name, &balls, &potions, &elementNum, &selectedIndex);
		op[i] = Trainer(name, balls, potions, elementNum, selectedIndex);
		g = rand() % a + 3;
		op[i].linktoArray(array[g]);
	}
	fclose(fp);
	return op;
}

int main() {
	int crethossz;
	int storyhossz;
	int pokhossz;
	Story * controll = controller(&storyhossz);
	Creature * creatures = createcreatures(&crethossz);
	Pokemon * pokemons = createpokemons(&pokhossz);
	Trainer * arenaop = createArena(pokemons, pokhossz);
	char choice;
	int dice;
	string name;
	int currentnode=0;
	int opponents = 0;

	cout << "Welcome! Type your name: "; cin >> name; Trainer Player(name, 3, 2, 0, 0);
	Player.linktoArray(pokemons[0]);
	Player.linktoArray(pokemons[1]);
	Player.linktoArray(pokemons[2]);
	Player.list();

	controll[currentnode].Print();

	do {
		cout << "Choices: (R)IGHT, (L)EFT, (H)EAL, E(X)IT" << endl;
		cin >> choice;
		switch (choice) {
		case 'R': {currentnode = controll[currentnode].getright(); controll[currentnode].Print(); 
			if (controll[currentnode].getright() == controll[currentnode].getleft() && controll[currentnode].getright()== storyhossz-1){
				choice = 'X';
				break;
			}
			else if (controll[currentnode].getid()>= controll[currentnode].getarena()) {

				Player.battle(arenaop[opponents].getpokemons()[0]); break;
			}

			else if(controll[currentnode].getid()> controll[currentnode].getwild() && controll[currentnode].getid()< controll[currentnode].getarena())
			{
				dice = rand() % 3; if (dice == 2)
					Player.battle(creatures[rand() % (crethossz)-1]); break;
				
			}

		} WAIT break;
		case 'L': {currentnode = controll[currentnode].getleft(); controll[currentnode].Print();
			if (controll[currentnode].getright() == controll[currentnode].getleft()) {
				choice = 'X';
					break;
			}
			else if (controll[currentnode].getid() > controll[currentnode].getarena()) {

				Player.battle(arenaop[opponents].getpokemons()[0]); break;
			}

				
			else if ((controll[currentnode].getid() > controll[currentnode].getwild()) && (controll[currentnode].getid() < controll[currentnode].getarena()))
			{
				dice = rand() % 3; if (dice == 2)
					Player.battle(creatures[rand() % (crethossz)-1]); break;

			}

		} WAIT break;
		case 'H': Player.list(); cin >> dice; Player.switchtoIndex(dice); Player.usePotion(); WAIT break;
		case 'X': cout << "Are you sure, you want to quit? Y-Yes | N-No" << endl; cin >> choice; if (choice == 'Y') { choice = 'X'; WAIT break; }
				  else if (choice == 'N') { choice = 'Y'; WAIT break; }
		default:  cout << "Wrong Input" << endl; WAIT break;
		}
	} while (choice != 'X' || !(Player.alivePokemons()));
	
	cout << "And the END is here. Don't forget to come back!:)" << endl;


	getchar();
	return 0;
}