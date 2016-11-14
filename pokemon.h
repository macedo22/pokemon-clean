#ifndef POKEMON_H
#define POKEMON_H

#include <string>

enum class element {
    fire = 0, water = 1, grass = 2
};

struct PokeEntry {
    int number;
    char name[20];
    char type[10];
    char description[100];

    PokeEntry() {};
    PokeEntry(int n){};
};


class Pokemon {
private:
	std::string nickName;
	int level = 1;
	string id;
protected:
	int maxHP = 20;
	int currentHP = maxHP;
	int speed = 10;
	int attack = 10;
	int defense = 10;
	int specialAttack = 10;
	int specialDefense = 10;

public:
	Pokemon(int i) {}
	~Pokemon() {}
	std::string get_nickName() {
		return nickName;
	}
	int get_level() {
		return level;
	}
	int get_maxHP() {
		return maxHP;
	}
	int get_currentHP() {
		return currentHP;
	}
	friend Pokemon* make_pokemon(element type, std::string name);
	ostream& operator <<(&ostream os, const Pokemon& pokemon);
	void write();

};

class Fire: public Pokemon {
public:
	Fire(int index);
};

class Water: public Pokemon {
public:
	Water(int index);
};

class Grass: public Pokemon {
public:
	Grass(int index);
};

#endif // POKEMON_H

