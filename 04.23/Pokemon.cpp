#include "Pokemon.h"



Pokemon::Pokemon(double hp, string name, double basedmg, int maxhp, Type own, Type weakness, int lvl, int growth) :Creature(hp, name, basedmg, maxhp), own(own), weakness(weakness), lvl(lvl), growth(growth)
{
	ability = nullptr;
	abilitycount = 0;
}


Pokemon::Pokemon()
{
	own = Water;
	weakness = Water;
	lvl = 0;
	growth = 0;
	ability = nullptr;
	abilitycount = 0;
	Creature(0, "Unknown", 0, 0);
}

Pokemon::~Pokemon()
{
	delete[] ability;
}

Pokemon::Pokemon(const Pokemon & other)
{
	own = other.own;
	weakness = other.weakness;
	lvl = other.lvl;
	growth = other.growth;

	Move * tmp = new Move[other.abilitycount];
	for (int i = 0; i < other.abilitycount; i++)
	{
		ability[i] = other.ability[i];
	}
	abilitycount = other.abilitycount;
	ability = tmp;
}

string Pokemon::getName()const
{
	return Creature::getName();
}

double Pokemon::getBaseDmg()const
{
	return Creature::getBaseDmg();
}

Type Pokemon::getWeakness()const
{
	return this->weakness;
}

Type Pokemon::getOwn()const
{
	return this->own;
}

double Pokemon::getHp()const
{
	return Creature::getHp();
}

Move Pokemon::getAbility(int idx)const
{
	return ability[idx];
}

void Pokemon::Print()
{
	cout << "Name: " << getName() << "Healthpoints: " << getHp() << "Current level: " << lvl << "Type: " << own << endl;
}

bool Pokemon::lvlup(int newgrowth)
{
	growth = growth + newgrowth;
	if (growth >= 100)
	{
		lvl += 1;
		cout << getName() << " levelled up!" << "New level: " << lvl << endl;
		growth = growth - 100;
		return true;
	}
	else
		cout << "Not enough experience points to level up..." << endl;
	return false;
}

bool Pokemon::isAlive()
{
	return this->getHp()>0;
}

void Pokemon::setHp(double newhp)
{
	setHp(newhp);
}

void Pokemon::listAbility()
{
	for (int i = 0; i < abilitycount; i++)
	{
		cout << "[" << i + 1 << "] - " << ability[i].getName() << endl;
	}
}

double Pokemon::attack(Pokemon & enemy)
{
	int dice = rand() % abilitycount;
	return ability[dice].use(*this, enemy);
}

void Pokemon::linkAbilitys(Move * abilitys, int count)
{
	ability = abilitys;
	abilitycount = count;
}

void Pokemon::linkAbility(Move & Ability)
{
	Move * tmp = new Move[abilitycount + 1];
	for (int i = 0; i < abilitycount; i++)
	{
		tmp[i] = ability[i];
	}
	tmp[abilitycount] = Ability;
	abilitycount += 1;
	delete[] ability;
	ability = tmp;
}

Pokemon& Pokemon::operator=(Pokemon & other)
{
	this->lvl = other.lvl;
	this->growth = other.growth;
	this->weakness = other.weakness;
	this->own = other.own;
	this->abilitycount = other.abilitycount;
	Move * tmp = new Move[abilitycount];
	for (int i = 0; i < abilitycount; i++)
	{
		tmp[i] = other.ability[i];
	}
	ability = tmp;
	return *this;
}




Move::Move(Type own, Type weakness, string name, double succfaktor, double failfaktor) : own(own), weakness(weakness), name(name), succfaktor(succfaktor), failfaktor(failfaktor)
{

}

Move::Move()
{
	own = Neutral;
	weakness = Neutral;
	name = "Unknown";
	succfaktor = 1;
	failfaktor = 1;
}

Move::~Move()
{
}

Move::Move(const Move & other)
{
	this->own = other.own;
	this->weakness = other.weakness;
	this->name = other.name;
	this->succfaktor = other.succfaktor;
	this->failfaktor = other.failfaktor;
}

string Move::getName()
{
	return this->name;
}

double Move::use(Pokemon & owner, Creature & enemy)
{
	Creature * a = dynamic_cast<Creature*>(&enemy);
	if (a == nullptr)
	{
		return cruse..
	}
		cout << owner.getName() << " is using " << this->name << "." << endl;
		if (this->own == Neutral)
		{
			if (rand() % 1)
				//cout
				return owner.getBaseDmg()*1.1;
			else
				//cout
				return owner.getBaseDmg()*0.9;
		}
		else if (enemy.getOwn() == owner.getWeakness())
		{
			//cout
			return this->failfaktor * owner.getBaseDmg();
		}
		else if (enemy.getWeakness() == owner.getOwn())
		{
			//cout
			return this->succfaktor * owner.getBaseDmg();
		}

	
}
