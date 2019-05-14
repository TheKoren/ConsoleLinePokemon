#include "Creature.h"



Creature::Creature(double hp, string name, double basedmg, int maxhp) : hp(hp), name(name), basedmg(basedmg), maxhp(maxhp)
{
}


Creature::~Creature()
{
}

Creature::Creature() :maxhp(0)
{
	hp = 0;
	name = "Unknown";
	basedmg = 0.0;
}

string Creature::getName()const
{
	return name;
}

double Creature::getHp()const
{
	return hp;
}

double Creature::getBaseDmg()const
{
	return basedmg;
}

int Creature::getMaxHp() const
{
	return maxhp;
}

void Creature::setBaseDmg(double a)
{
	basedmg = a;
}

void Creature::setMaxHp(int a)
{
	maxhp = a;
}

void Creature::setName(string a)
{
	name = a;
}

void Creature::Print()
{
	cout << "Name:" << name << "\tHealthpoints:" << hp << endl;
}

bool Creature::isAlive()
{
	return hp > 0.0;
}

void Creature::setHp(double newhp)
{
	if (hp + newhp > maxhp)
	{
		hp = maxhp;
	}
	if (newhp < 0)
	{
		hp = 0;
	}
	else
		hp = newhp;
}

double Creature::attack(Pokemon & enemy)
{
	int dice = rand() % 100 + 1;
	if (dice == 100)
	{
		cout << "ENEMY:Attack is super effective!\t" << name << " heals itself for 5 healthpoints!" << endl;
		setHp(hp + 5);
		cout << "Damage given: " << basedmg * 1.5 << endl;
		return basedmg * 1.5;
	}
	else if (dice > 90)
	{
		cout << "ENEMY:Attack is effective!\t" << name << " heals itself for 1 healthpoint!" << endl;
		setHp(hp + 5);
		cout << "Damage given: " << basedmg * 1.25 << endl;
		return basedmg * 1.25;
	}
	else if (dice >= 30)
	{
		cout << "ENEMY:Attack is regular!\t" << endl;
		cout << "Damage given " << basedmg << endl;
		return basedmg;
	}
	else
	{
		cout << "ENEMY:Attack is not that effective!\t" << endl;
		cout << "Damage given " << basedmg * 0.75 << endl;
		return basedmg * 0.75;
	}

}

Creature & Creature::operator=(const Creature & other)
{
	this->hp = other.hp;
	this->name = other.name;
	this->basedmg = other.basedmg;
	this->maxhp = other.maxhp;
	return *this;
}
