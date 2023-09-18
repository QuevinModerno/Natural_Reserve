//
// Created by Quevin Moderno on 09/11/2022.
//
#include "../Headers/Animal.h"


Animal::Animal(string specie,int id): ID(id), health(20), weight(5),age(3), hunger(0), history(""){}
Animal::Animal(int id, int health, int weight, int steps, int vision):ID(id), health(health), weight(weight), vision(vision), age(1), hunger(0), steps(steps), dead(false), history(""){}
Animal::~Animal(){ }

string Animal::setHistory(string food, int nutricity, int toxicity)
{
    ostringstream oss;

    oss << food << ":" << endl;
    oss << "    Points:  Nutricity-> " << nutricity <<";  Toxicity-> " <<  toxicity << endl<< endl;

    return oss.str();
}
void Animal::setHistory(string specie, int id)
{
    ostringstream oss;

    oss << "Killed animal " << specie << " id " << id;

    history += oss.str();

}
void Animal::feed(string food, int nutricity, int toxicity)
{
    this->health += (nutricity - toxicity);
    this->history += setHistory(food, nutricity, toxicity);
}

ostream& operator<< (ostream& output, Animal* a)
{
    output << a->ID << ": Animal " << a->letter() << endl <<
    " Health-> " << a->health << "  Hunger: " << a->gethunger() << " Age " << a->getage() << endl
     << a->history << endl;
    return output;
}




//RABBIT

void Rabbit::dayPassed()
{
    setage();
    if(this->gethealth() == 0) DIE();

    sethunger(gethunger()+1);
    if(getage() == 30)
        DIE();

    if(gethunger() > 10)
    {
        if(gethunger() > 20){
            sethealth(gethealth() - 2);
            setstpes(3);
        }
        else{
            sethealth(gethealth() - 1);
            setstpes(4);
        }
    }
    else{
        setstpes(1);
    }

}
bool Rabbit::SpeciesDictatingMovem(vector<string> sp)
{
    for(int i = 0; i < sp.size(); i++)
        if(sp[i] == "L" || sp[i] == "G" || sp[i] == "r" || sp[i] == "t")
            return true;

    return false;
}

bool Rabbit::AvoidAN(Animal *an){
    if (an->getweight() > 10)
        return true;

    return false;
}
bool Rabbit::moveAN  ( Animal* an){
    return false;
}
bool Rabbit::moveFD  ( Food* fd) {
    if(fd->getLetter() == "r" || fd->getLetter() == "t")
        return true;

    return false;
}

void Rabbit::child(Animal* an) {}
bool Rabbit::child(int * distance){
    if(getage() == 8 || getage() == 16 || getage() == 24){

        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(1,2);
        int random = randn(defEngine);

        //50% chance of creating the child
        if(random == 1){
            *distance = 10;
            return true;
        }
    }

    return false;
}




//SHEEP

void Sheep::dayPassed() {
    setage();
    if(this->gethealth() == 0) DIE();

    sethunger(gethunger()+1);

    if(getage() == 35)
        DIE();


    if(gethunger() > 10)
    {
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(1,4);
        setstpes(randn(defEngine));

        if(gethunger() > 20){
            sethealth(gethealth() - 2);
        }
        else{
            sethealth(gethealth() - 1);
        }

    }else
        setstpes(1);


}

bool Sheep::SpeciesDictatingMovem(vector<string> sp)
{
    for(auto it : sp)
        if(it == "L" || it == "G" || it == "r" || it == "t")
            return true;

    return false;
}
/*virtual bool move  ( vector<Animal*> an, vector<Food*> food) {
    for (auto at: an) {
        if (at->getweight() > 15)
            return false;
    }

    return true;
}

virtual vector<Animal*> moveAN  ( vector<Animal*> an) {an.clear(); return an;}
virtual vector<Food*> moveFD  ( vector<Food*> food)
{
    for (int i = 0; i < food.size(); i++) {
        if (food[i]->getLetter() == "r" || food[i]->getLetter() == "t");
        else{
            delete food[i];
        }
    }

    return food;
}


virtual int chase(vector<Animal*> an, vector<Food*> food, map<int, int> distance)
{
    int Minordist = 0, distan = 0, id = 0;

    for(auto at : food){

        for(auto it = distance.begin(); it != distance.end(); it++)
            if(at->getID() == it->first) {
                distan = it->second;
                break;
            }

        if(distan < Minordist){
            Minordist = distan;
            id = at->getID();
        }
    }

    return id;
}
*/

bool Sheep::AvoidAN(Animal *an){
    if (an->getweight() > 15)
        return true;

    return false;
}
bool Sheep::moveAN  ( Animal* an){
    return false;
}
bool Sheep::moveFD  ( Food* fd) {
    if(fd->getLetter() == "r" || fd->getLetter() == "t")
        return true;

    return false;
}

void Sheep::child(Animal* an){ an->sethealth(this->gethealth()); }
bool Sheep::child(int * distance){
    if(getage() == 15 || getage() == 30){
        *distance = 12;
        return true;
    }

    return false;
}




//WOLF

void Wolf::dayPassed(){
    setage();
    if(this->gethealth() == 0) DIE();

    sethunger(gethunger()+2);


    if(gethunger() > 15)
    {
        setstpes(2);
        if(gethunger() > 25)
            sethealth(gethealth() - 2);

        else
            sethealth(gethealth() - 1);

    }
    else{
        setstpes(1);
    }

    if(this->DaytoChild == getage())
        DIE();
}
bool Wolf::SpeciesDictatingMovem(vector<string> sp)
{
    for(auto it : sp)
        if(it == "p" || it == "b" || it == "C" || it == "O" || it == "L" || it == "G" || it == "M")
            return true;

    return false;
}
/*virtual bool move  ( vector<Animal*> an, vector<Food*> food){return true;}
virtual vector<Animal*> moveAN  ( vector<Animal*> an) {
    if(!an.empty())
    {
        if(this->getweight() < 15)
            setstpes(3);
        else setstpes(2);
    }
    return an;
}
virtual vector<Food*> moveFD  ( vector<Food*> food)
{
    for (int i = 0; i < food.size(); i++) {
        if (food[i]->getLetter() == "p" || food[i]->getLetter() == "b");
        else{
            delete food[i];
        }
    }

    return food;
}

virtual int chase(vector<Animal*> an, vector<Food*> food, map<int, int> distance)
{
    int Minordist = 0, distan = 0, id = 0;

    for(auto at : an){

        for(auto it = distance.begin(); it != distance.end(); it++)
            if(at->getID() == it->first) {
                distan = it->second;
                break;
            }
        //if it has an animal close enough kills it (or gets in a fight)
        if( distan < this->getsteps())
        {
            //fight!
            if(this->getweight() < at->getweight()){

                default_random_engine defEngine(time(nullptr));
                uniform_int_distribution<int> randn(1,2);
                int random = randn(defEngine);
                if(random == 1)
                    this->DIE();
                else
                    at->DIE();
            }
                //Kills the animal being chased
            else{ at->DIE(); }

            return at->getID();
        }


        if(distan < Minordist){
            Minordist = distan;
            id = at->getID();
        }
    }

    for(auto at : food){

        for(auto it = distance.begin(); it != distance.end(); it++)
            if(at->getID() == it->first) {
                distan = it->second;
                break;
            }

        if(distan < Minordist){
            Minordist = distan;
            id = at->getID();
        }
    }

    return id;
}
 */
bool Wolf::AvoidAN(Animal *an){ return false;}
bool Wolf::moveAN  ( Animal* an){

    //FIGHT
    if(this->getweight() < an->getweight()) {
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(0,1);


        if( randn(defEngine) == 0){
            DIE();
            return false;
        }
    }

    if(this->getweight() < 15){
        setstpes(3);
    }
    else{ setstpes(2);}

    return true;
}
bool Wolf::moveFD  ( Food* fd) {
    if (fd->getLetter() == "p" || fd->getLetter() == "b")
        return true;

    return false;
}

bool Wolf::child(int * distance){
    if(getage() == DaytoChild){
        *distance = 15;
        return true;
    }

    return false;
}



//KANGAROO

 void Kangaroo::dayPassed(){
    setage();

    if(getage() == 70)
        DIE();

    if(getage() == 20){
        setweight(20);
    }
    if( getage() == 11)
        this->son = nullptr;

}
 bool Kangaroo::SpeciesDictatingMovem(vector<string> sp) {
    if(getage() > 20 )
        return false;

    for(auto it : sp)
        if(it == "G")
            return true;

    return false;
}
 bool Kangaroo::AvoidAN(Animal *an){ if(getage() > 10) return false; else return true; }
bool Kangaroo::moveAN  ( Animal* an){

    if( getage() < 10 && an->getID() == son->getID() ){
        setstpes(2);
        return true;
    }

    return false;
}
bool Kangaroo::moveFD  ( Food* fd) {return false;}
bool Kangaroo::child(int * distance){
    if(getage() == 30 || getage() == 60){
        *distance = 3;
        return true;
    }

    return false;
}




