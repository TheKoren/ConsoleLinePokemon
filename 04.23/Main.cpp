#include "Trainer.h"

struct Node {
	int id;
	int rightid;
	int leftid;
};
 /*TODO: ezeket szabad �gy csin�lni?*/
struct Story {
	int id;
	char * text;
};

Node* createmap() {
	//TODO: CPPben filekezeles?
}
Story* createstory() {

}

Creature* createcollection() {

}
Trainer* createArena() {

}

int main() {

	Node * root = createmap();
	Story * novel = createstory();
	Creature * collection = createcollection();
	/*Create User Trainer, linking pokemon Array*/
	Trainer * arenaop = createArena();
	char choice;
	int dice; //Todo: glob�lis v�ltoz�k tiltottak
	cin >> choice;
	do {
		switch (choice){
		case 'J': dice = rand() % 3; if (dice == 2)//Trainernek battlej�t megh�vjuk, egy m�sik randomsz�m� index collection�s creaturrel, felt�ve, ha a storyban m�g nem �rt�nk el egy bizonyos indexet}
		case 'B':	dice = rand() % 3; if (dice == 2) //Trainernek battlej�t megh�vjuk, egy m�sik randomsz�m� index collection�s creaturrel, felt�ve ha a storyban m�g nem �rt�nk el egy bizonyos indexet}
		case 'H': //ki list�zza a Trainer pokemonjait, lehet indexet v�lasztani, majd azt healelni.
		case 'S': //Valahogy lementi a cuccost.
		case 'X': cout << "Are you sure, you want to quit? Y-Yes | N-No" << endl; cin >> choice; if (choice == 'Y') { break; }
				  else if (choice == 'N') { choice = 'X'; break; }
		default: cout << "..." << endl;
						}
		} while (choice != 'X');


		return 0;
}

