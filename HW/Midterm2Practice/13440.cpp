#include <iostream>
#include <cstring>
using namespace std;

class Animal {
	public:
		Animal();
		Animal(string n, string s);
		~Animal();
		
		virtual string get_name();
		virtual string get_species();
		virtual int get_HP();
		virtual void update_HP(int x);
		virtual void turn_HP_into_zero();
		
		virtual void Talk();
		virtual void Breath(int x);
		virtual void Sleep(int x);
		virtual void Eat(Animal *animal);
		virtual void Eaten(Animal *animal);
		
	private:
		string name;
		string species;
		int HP;
};

class Cat : public virtual Animal {
	public:
		Cat(string n);
		void Talk();
		void Eat(Animal *animal);
};

class Fish : public virtual Animal {
	public:
		Fish(string n);
		void Talk();
		void Eaten(Animal *animal);
};

class Bird : public virtual Animal {
	public:
		Bird(string n);
		void Talk();
		void Eat(Animal *animal);
		void Eaten(Animal *animal);
};

class Human : public virtual Animal {
	public:
		Human(string n);
		void Talk();
		void Eat(Animal *animal);
};

using namespace std;

int n, q;

string species[1009];
Animal *animal[1009];

int main() {
    freopen("output.txt","w",stdout);
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++ i) {
		string name;
		cin >> species[i] >> name;
		
		if (species[i] == "cat")
			animal[i] = new Cat(name);
		else if (species[i] == "fish")
			animal[i] = new Fish(name);
		else if (species[i] == "bird")
			animal[i] = new Bird(name);
		else if (species[i] == "human")
			animal[i] = new Human(name);
	}
	
	while ( q -- ) {
		string op; int i;
		cin >> op >> i;
		
		if (op == "Name") {
			cout << animal[i]->get_name() << endl;
			
		} else if (op == "Species") {
			cout << animal[i]->get_species() << endl;
			
		} else if (op == "HP") {
			cout << animal[i]->get_HP() << endl;
			
		} else if (op == "Talk") {
			animal[i]->Talk();
				
		} else if (op == "Breath") {
			int x;
			cin >> x;
			animal[i]->Breath(x);
			
		} else if (op == "Sleep") {
			int x;
			cin >> x;
			animal[i]->Sleep(x);
			
		} else if (op == "Eat") {
			int j;
			cin >> j;
			animal[i]->Eat(animal[j]);
			animal[j]->Eaten(animal[i]);
			
		}
	}
}

Animal::Animal(){
    
}

Animal::Animal(string n, string s){
    name = n;
    species = s;
    HP=0;
}
Animal::~Animal(){

}
string Animal::get_name(){
    return name;
}
string Animal::get_species(){
    return species;
}
int Animal::get_HP(){
    return HP;
}
void Animal::update_HP(int x){
    HP += x;
}
void Animal::turn_HP_into_zero(){
    HP = 0;
}

void Animal::Talk(){

}
void Animal::Breath(int x){
    HP+=x;
}
void Animal::Sleep(int x){
    if(HP<=100) HP*=x;
}
void Animal::Eat(Animal *animal){
    
}
void Animal::Eaten(Animal *animal){
    
}

Cat::Cat(string n):Animal(n,"cat"){

}
void Cat::Talk(){
    cout<<"Meow"<<endl;
}
void Cat::Eat(Animal *animal){
    if(animal->get_species()=="fish") update_HP(animal->get_HP());
}
Fish::Fish(string n):Animal(n,"fish"){

}
void Fish::Talk(){
    cout<<"?"<<endl;
}
void Fish::Eaten(Animal *animal){
    if(animal->get_species()!="fish") turn_HP_into_zero();
}
Bird::Bird(string n): Animal(n,"bird"){

}
void Bird::Talk(){
    cout<<"Suba"<<endl;
}
void Bird::Eat(Animal *animal){
    if(animal->get_species()=="fish"){
        update_HP(animal->get_HP());
    }
}
void Bird::Eaten(Animal *animal){
    if(animal->get_species()=="human"){
        turn_HP_into_zero();
    }
}
Human::Human(string n):Animal(n,"human"){

}
void Human::Talk(){
    cout<<"Hello, world"<<endl;
}
void Human::Eat(Animal *animal){
    if(animal->get_species()=="bird"||animal->get_species()=="fish") update_HP(animal->get_HP()) ;
    else if(animal->get_species()=="cat") turn_HP_into_zero();
}