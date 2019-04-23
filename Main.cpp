#include "Trainer.h"

struct Node {
	int id;
	int rightid;
	int leftid;
};

struct Story {
	int id;
	char * text;
};

Node* createmap() {

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

	
	return 0;
}