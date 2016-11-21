/*Declaration of base class Pokemon, its derived
classes (Fire, Water, and Grass) and the three species
classes that derive from Water (Squirtle, Wartortle, and
Blastoise. The pokemon class sets base stats that are
modified in pokemon.cpp depending on elemental type.
Derived classes have no unique functions other than their
constructors, and define Pokemon's two virtual attack
functions. Also declared are the make_pokemon function and
overloaded << operator that are friends to the Pokemon
class. The PokeEntry struct is used to store information
unique to each pokemon from the pokedex.*/

#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <fstream>
#include <list>
#include <cmath>

using namespace std;

enum class element {
	fire = 0, water = 1, grass = 2, normal = 3, dragon = 4
};

struct PokeEntry {
	int number;
	string name;//i.e. Jolteon
	char type[10];
	char description[100];

	PokeEntry() {};
	PokeEntry(int n) {
		std::ifstream entryFile(std::to_string(n) + ".txt");
		entryFile >> number;
		entryFile >> name;
		entryFile >> type;
		entryFile.seekg(1, std::ios::cur);
		entryFile.getline(description, 199);
		entryFile.close();
	};
};


class Pokemon {
private:
	std::string nickName;//i.e. "Sparky" for Jolteon
	int level = 1;
	string id;//unique hash identification number
protected:
	int maxHP = 20;
	int currentHP = maxHP;
	int speed = 10;
	int attack = 10;
	int defense = 10;
	int specialAttack = 10;
	int specialDefense = 10;
	list<element> weaknesses;
public:
	PokeEntry* pokeEntry;

public:
	Pokemon(int i) {
		pokeEntry = new PokeEntry(i);
	}
	~Pokemon() {}

	//getters
	string get_nickName() {
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
	string get_species(){
		return (*pokeEntry).name;
	}

	//stters
	void set_nickName(string n){
		nickName = n;
	}
	void set_species(string name){
		(*pokeEntry).name = name;
	}

	void write();//uses overloaded << operator to print pokemon info to a file
	int take_damage(int damageAmount, list<element> damageTypes);//inflicts damage on an opponent and prints details of the event

	virtual int attack1(Pokemon* pokemon){ return 0; };//implemented by Water and Blastoise
	virtual int attack2(Pokemon* pokemon){ return 0; };//implemented by Squirtle, Wartortle, and Blastoise

	friend Pokemon* make_pokemon(int index, string n);//creates new pokemon based on pokedex index and nick name
	friend ostream& operator <<(ostream& os, Pokemon pokemon);//used to print information about a pokemon
};

class Fire : public Pokemon {
public:
	Fire(int index);
};

class Water : public Pokemon {
public:
	Water(int index);
	int attack1(Pokemon* pokemon);
};

class Grass : public Pokemon {
public:
	Grass(int index);
};

class Squirtle : public Water{
public:
	Squirtle(string n="Squirtle");
	int attack2(Pokemon* pokemon);
};

class Wartortle : public Water {
public:
	Wartortle(string n="Wartortle");
	int attack2(Pokemon* pokemon);
};

class Blastoise : public Water {
public:
	Blastoise(string n = "Blastoise");
	int attack1(Pokemon* pokemon);
	int attack2(Pokemon* pokemon);
};

#endif // POKEMON_H
