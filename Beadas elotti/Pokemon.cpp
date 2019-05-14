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

Type Pokemon::getWeakness()const
{
	return this->weakness;
}

Type Pokemon::getOwn()const
{
	return this->own;
}


int Pokemon::getcount() const
{
	return abilitycount;
}

Move Pokemon::getAbility(int idx)const
{
	return ability[idx];
}

int Pokemon::getlvl() const
{
	return lvl;
}

void Pokemon::Print()
{
	cout << "Name:" << getName() << "\tHealthpoints:" << getHp() << "\tCurrent level: " << lvl << "\tType:" << own+1 << endl;
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

Pokemon& Pokemon::operator=(const Pokemon & other)
{
	this->lvl = other.lvl;
	this->growth = other.growth;
	this->weakness = other.weakness;
	this->own = other.own;
	this->abilitycount = other.abilitycount;
	Creature::setHp(other.getHp());
	Creature::setName(other.getName());
	Creature::setBaseDmg(other.getBaseDmg());
	Creature::setMaxHp(other.getMaxHp());
	Move * tmp = new Move[abilitycount];
	for (int i = 0; i < abilitycount; i++)
	{
		tmp[i] = other.ability[i];
	}
	ability = tmp;
	return *this;
}




Move::Move(Type own, string name, double succfaktor, double failfaktor) : own(own), name(name), succfaktor(succfaktor), failfaktor(failfaktor)
{

}

Move::Move()
{
	own = Neutral;

	name = "Unknown";
	succfaktor = 1;
	failfaktor = 1;
}

Move::~Move()
{
}

string Move::getName()
{
	return this->name;
}


double Move::use(Pokemon & owner, Creature & enemy)
{
	cout << owner.getName() << " is using " << this->name << "." << endl;
	if (this->own == Neutral)
	{
		if (rand() % 1)
		{
			cout << owner.getName() << "causes " << owner.getBaseDmg()*1.1 + owner.getlvl() << "damage on " << enemy.getName() << endl;
			return owner.getBaseDmg()*1.1+owner.getlvl();
		}
		else
		{
			cout << owner.getName() << "causes " << owner.getBaseDmg()*0.9 + owner.getlvl() << "damage on " << enemy.getName() << endl;
			return owner.getBaseDmg()*0.9 + owner.getlvl();
		}
	}
	if (enemy.getBaseDmg() > owner.getBaseDmg())
	{
		cout << owner.getName() << "causes " << this->failfaktor*owner.getBaseDmg() + owner.getlvl() << "damage on " << enemy.getName() << endl;
		cout << "It's not very effective." << endl;
		return this->failfaktor*owner.getBaseDmg() + owner.getlvl();
	}
	else
	{
		cout << owner.getName() << "causes " << this->succfaktor*owner.getBaseDmg() + owner.getlvl() << "damage on " << enemy.getName() << endl;
		cout << "It's effective" << endl;
		return this->succfaktor*owner.getBaseDmg() + owner.getlvl();
	}

}

void Move::Print()
{
	cout << "Name: " << name << endl;
}

double Move::use(Pokemon & owner, Pokemon & enemy)
{
	cout << "-";
	cout << owner.getName() << " is using " << this->name << "." << endl;
	if (this->own == Neutral)
	{
		if (rand() % 1)
		{
			cout << owner.getName() << "causes " << owner.getBaseDmg()*1.1 + owner.getlvl() << "damage on " << enemy.getName() << endl;
			return owner.getBaseDmg()*1.1 + owner.getlvl();
		}
		else
		{
			cout << owner.getName() << "causes " << owner.getBaseDmg()*0.9 + owner.getlvl() << "damage on " << enemy.getName() << endl;
			return owner.getBaseDmg()*0.9 + owner.getlvl();
		}

	}
	else if (enemy.getOwn() == owner.getWeakness())
	{
		cout << owner.getName() << "causes " << this->failfaktor * owner.getBaseDmg() + owner.getlvl() << "damage on " << enemy.getName() << endl;
		cout << "Its not very effective." << endl;
		return this->failfaktor * owner.getBaseDmg() + owner.getlvl();
	}
	else if (enemy.getWeakness() == owner.getOwn())
	{
		cout << owner.getName() << "causes " << this->succfaktor * owner.getBaseDmg() + owner.getlvl() << "damage on " << enemy.getName() << endl;
		cout << "It's effective." << endl;
		return this->succfaktor * owner.getBaseDmg() + owner.getlvl();
	}
	else
	{
		cout << owner.getName() << "causes " << owner.getBaseDmg() + owner.getlvl() << "damage on " << enemy.getName() << endl;
		return owner.getBaseDmg() + owner.getlvl();
	}

}