#include "pokemon.h"

using namespace std;

Fire::Fire(int index) : Pokemon(index){
	maxHP+=1; speed+=2;
	attack+=2; defense-=2;
	specialAttack+=4; specialDefense+=1;
}

Water::Water(int index) : Pokemon(index){
	maxHP+=2; speed-=1;
	attack-=2; defense+=2;
	specialAttack-=4; specialDefense-=1;
}

Grass::Grass(int index) : Pokemon(index){
	maxHP-=3; speed-=2;
	attack-=2; defense+=0;
	specialAttack-=3; specialDefense+=0;
}

&ostream Pokemon::operator<<(ostream& os, const Pokemon& pokemon){
    os<< "Pokemon: "<<endl
        <<"\tID: " <<pokemon.id<<endl
        <<"\tNick name: " <<pokemon.nickName<<endl
        <<"\tAttack: " <<pokemon.attack<<endl
        <<"\tDefense: " <<pokemon.defense<<endl
        <<"\tEntry: "<<endl
        <<"\t\tNumber: " <<pokemon.number<<endl
        << "\t\tName: " <<pokemon.name<<endl<<endl;
}

Pokemon::write(){
    std::ofstream outFile;
    string filename = pokemon.id + ".dat";
    outFile.open(filename);

    outfile<<pokemon<<endl;

    outFile.close();
}

Pokemon *make_pokemon(element e, std::string n) {

	Pokemon *newPokemon;
	if(e == element::fire) {
		newPokemon = new Fire(1);
		newPokemon->name = n;
	} else if(e == element::grass) {
		newPokemon = new Grass(1);
		newPokemon->name = n;
	} else if(e == element::water) {
		newPokemon = new Water(1);
		newPokemon->name = n;
	}
	return newPokemon;

}
