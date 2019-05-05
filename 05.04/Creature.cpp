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

Creature::Creature(const Creature & other) : maxhp(other.maxhp)
{
	this->hp = other.hp;
	this->name = other.name;
	this->basedmg = other.basedmg;
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

void Creature::Print()
{
	cout << "Name: " << name << "Healthpoints: " << hp << endl;
}

bool Creature::isAlive()
{
	return hp > 0.0;
}

void Creature::setHp(double newhp)
{
	if ((hp + newhp) > maxhp)
	{
		hp = maxhp;
	}
	else
		hp = hp + maxhp;

}

double Creature::attack()
{
	int dice = rand() % 100 + 1;
	if (dice == 100)
	{
		cout << "Attack is super effective!\t" << name << " heals itself for 5 healthpoints!" << endl;
		setHp(hp + 5);
		cout << "Damage given: " << basedmg * 1.5 << endl;
		return basedmg * 1.5;
	}
	else if (dice > 90)
	{
		cout << "Attack is effective!\t" << name << " heals itself for 1 healthpoint!" << endl;
		setHp(hp + 5);
		cout << "Damage given: " << basedmg * 1.25 << endl;
		return basedmg * 1.25;
	}
	else if (dice >= 30)
	{
		cout << "Attack is nem gyaszos, de nem igazan patent effective!\t" << endl;
		cout << "Damage given " << basedmg << endl;
		return basedmg;
	}
	else
	{
		cout << "Attack is not that effective!\t" << endl;
		cout << "Damage given " << basedmg * 0.75 << endl;
		return basedmg * 0, 75;
	}

}