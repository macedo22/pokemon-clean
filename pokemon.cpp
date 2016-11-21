/*Alex Macedo
Project 7
Pokemon-clean
email:macedo22@ucla.edu

This includes the implementation for member functions of
the Pokemon, Fire, Water, Grass, Squirtle, Wartortle, and
Blastoise classes. Contains constructors for each pokemon
type that modifies their stats according to type. Also
includes the implementation of friend functions make_pokemon
and and an ostream overloaded function. The former creates
a pokemon of a certain type while the latter is used to
print the specifics about a pokemon object.

The virtual attack1 function is implemented in Water and
Blastoise classes, while virtual attack2 function is
implemented in the Squirtle, Wartortle, and Blastoise
classes. Each attack functions calls the take_damage function
to deplete an enemy's hp and print who attacked who and how
much damage was incurred.*/

#include "pokemon.h"
#include <iostream>
#include <fstream>

using namespace std;

//Overloads << operator to print information about a pokemon
ostream& operator <<(ostream& os, Pokemon pokemon){
	os << "Pokemon: " << endl
		<< "\tID: " << pokemon.id << endl
		<< "\tNick name: " << pokemon.nickName << endl
		<< "\tAttack: " << pokemon.attack << endl
		<< "\tDefense: " << pokemon.defense << endl
		<< "\tEntry: " << endl
		<< "\t\tNumber: " << (*(pokemon.pokeEntry)).number << endl
		<< "\t\tName: " << (*(pokemon.pokeEntry)).name << endl << endl;

	return os;
}

/*Uses the overloaded << operator to print a pokemon's information
to a file named usin their unique id number*/
void Pokemon::write(){
	ofstream outFile;
	string filename = id + ".dat";
	outFile.open(filename);

	outFile << (*this) << endl;

	outFile.close();
}


/*Passes the damage given by a specific attack and it's elemental
damage type. The weaknesses of the pokemon incurring damage
will be iterated through. If a weakness equals one of the elemental
attacks inflicted by the attacker, the attacked pokemon becomes
weaker. The level of weakness increases the total damage incurred,
which is subtracted from the attacked's current hp and is returned.*/
int Pokemon::take_damage(int damageAmount, list<element> damageTypes){
	int weaknessCount = 0;
	for (auto wIt = weaknesses.begin(); wIt != weaknesses.end(); wIt++)
		for (auto dIt = damageTypes.begin(); dIt != damageTypes.end(); dIt++)
			if (*dIt == *wIt) weaknessCount++;

	damageAmount = static_cast<int>(damageAmount * (log(5 * weaknessCount + 5) / log(5)));
	currentHP -= damageAmount;
	return damageAmount;
}

//stat modifications for Fire pokemon
Fire::Fire(int index) : Pokemon(index){
	maxHP += 1; speed += 2;
	attack += 2; defense -= 2;
	specialAttack += 4; specialDefense += 1;
	weaknesses.push_back(element::water);
}

//stat modifications for Water pokemon
Water::Water(int index) : Pokemon(index){
	maxHP += 2; speed -= 1;
	attack -= 2; defense += 2;
	specialAttack -= 4; specialDefense -= 1;
	weaknesses.push_back(element::grass);
}

//Bubble attack
int Water::attack1(Pokemon* pokemon){
	list<element> damageTypes;
	damageTypes.push_back(element::fire);

	int damage= (*pokemon).take_damage(2, damageTypes);

	cout << (*this).get_nickName() << " used Bubble. "
		<< (*pokemon).get_species() << " took "
		<< damage << " damage!" << endl;
	return damage;
}

//stat modifications for Grass pokemon
Grass::Grass(int index) : Pokemon(index){
	maxHP -= 3; speed -= 2;
	attack -= 2; defense += 0;
	specialAttack -= 3; specialDefense += 0;
	weaknesses.push_back(element::fire);
}

//Nick name defaults to Squirtle
Squirtle::Squirtle(string n):Water(7){
	set_nickName(n);
	set_species("Squirtle");
}

//Tackle attack
int Squirtle::attack2(Pokemon* pokemon){
	list<element> damageTypes;
	damageTypes.push_back(element::normal);

	int damage = (*pokemon).take_damage(2, damageTypes);

	cout << (*this).get_nickName() << " used Tackle. "
		<< (*pokemon).get_species() << " took "
		<< damage << " damage!" << endl;
	return damage;
}

//Nick name defaults to Wartortle
Wartortle::Wartortle(string n):Water(8){
	set_nickName(n);
	set_species("Wartortle");
}

//Surf attack
int Wartortle::attack2(Pokemon* pokemon){
	list<element> damageTypes;
	damageTypes.push_back(element::water);

	int damage = (*pokemon).take_damage(4, damageTypes);

	cout << (*this).get_nickName() << " used Surf. "
		<< (*pokemon).get_species() << " took "
		<< damage << " damage!" << endl;
	return damage;
}

//Nick name defaults to Blastoise
Blastoise::Blastoise(string n): Water(9){
	set_nickName(n);
	set_species("Blastoise");
}

//Water Pledge attack
int Blastoise::attack1(Pokemon* pokemon){
	list<element> damageTypes;
	damageTypes.push_back(element::water);
	damageTypes.push_back(element::dragon);

	int damage = (*pokemon).take_damage(8, damageTypes);

	cout << (*this).get_nickName() << " used Water Pledge. "
		<< (*pokemon).get_species() << " took "
		<< damage << " damage!" << endl;
	return damage;
}

//Hydro Cannon attack
int Blastoise::attack2(Pokemon* pokemon){
	list<element> damageTypes;
	damageTypes.push_back(element::water);

	int damage = (*pokemon).take_damage(6, damageTypes);

	cout << (*this).get_nickName() << " used Hydro Cannon. "
		<< (*pokemon).get_species() << " took "
		<< damage << " damage!" << endl;
	return damage;
}

/*Creates and returns a pointer to a Squirtle, Wartortle, or
Blastoise object by passing an index and nick name.*/

Pokemon *make_pokemon(int index, string n) {

	Pokemon *newPokemon;
	if (index == 7) {
		newPokemon = new Squirtle(n);
		newPokemon->get_nickName() = n;
		cout << "You created a new Squirtle named " << n << endl;
	}
	else if (index == 8) {
		newPokemon = new Wartortle(n);
		newPokemon->get_nickName() = n;
		cout << "You created a new Wartortle named " << n << endl;
	}
	else if (index == 9) {
		newPokemon = new Blastoise(n);
		newPokemon->get_nickName() = n;
		cout << "You created a new Blastoise named " << n << endl;
	}
	else{
		cout << "Not a valid index. Choose 7, 8, or 9." << endl;
		return NULL;
	}
	return newPokemon;

}

//simple main function to demonstrate functionality of attack functions
int main(){

	Squirtle squirtle = Squirtle("Splashy");
	Pokemon* blastoise = make_pokemon(9, "Old Faithful");//test for make_pokemon function

	squirtle.attack2(blastoise);//squirtle attacks blastoise
	(*blastoise).attack1(&squirtle);//blastoise attacks squirtle

	Pokemon* charmander = new Fire(1);
	(*charmander).set_species("Charmander");
	(*blastoise).attack1(charmander);//blastoise attacks charmander, who takes more damage than squirtle due to elemental weakness

	return 0;
}
