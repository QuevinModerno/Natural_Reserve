//
// Created by Quevin Moderno on 09/11/2022.
//

#ifndef TP_ANIMAL_H
#define TP_ANIMAL_H


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <random>
#include "Food.h"

using namespace std;

class Animal {

    int ID;
    int health;
    int hunger;
    double weight;
    int vision;
    int age;
    int steps;
    bool dead;
    string history;

    string setHistory(string specie, int nutricity, int toxicity);
protected:
    void sethunger(int h){this->hunger = h;}
    void setweight(int w){this->weight = w;}
    void setstpes(int s){this->steps = s;}
    void setage(){this->age++;}
public:
    Animal(string specie, int id);
    Animal(int id, int health, int weight, int steps, int vision);

    virtual ~Animal();

    int getID() const {return this->ID;}
    int gethealth() const {return this->health;}
    int gethunger() const {return this->hunger;}
    int getweight() const {return this->weight;}
    int getage() const {return this->age;}
    int getsteps() const {return this->steps;}
    int getvision() const {return this->vision;}
    bool getdead() const {return this->dead;}
    void DIE(){this->dead = true;}

    void sethealth(int h){this->health = h;}
    void setHistory(string specie, int id);
    void feed(string specie, int nutricity, int toxicity);


    virtual void dayPassed() = 0;
    virtual string letter() = 0;
    virtual bool SpeciesDictatingMovem(vector<string> sp) = 0;
   /* virtual bool move  ( vector<Animal*> an, vector<Food*> food) = 0;
    virtual vector<Animal*> moveAN  ( vector<Animal*> an) = 0;
    virtual vector<Food*> moveFD  ( vector<Food*> fd) = 0;
    */

    virtual bool AvoidAN(Animal *an) = 0;   //checks if it should avoid the other specie around him
    virtual bool moveAN  ( Animal* an) = 0; // check if it is an animal he wants to chase
    virtual bool moveFD  ( Food* fd) = 0;   // check if it is a food he wants to chase


    virtual bool child(int * distance) = 0;  //check if it is time to create a child
    virtual void child(Animal* an) = 0;      //Alters the necessary attributes of the child
    virtual vector<int> getDeadBody() = 0;   //Returns the attributes of the meat created by the dead body


    virtual Animal* clone() = 0;
    friend ostream& operator<< (ostream& output, Animal* a); //friend para poder aceder a memoria privada da classe
};


class Rabbit: public Animal{

public:
    Rabbit(int id) : Animal(id, 20,1,1,4){
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(1,4);
        setweight( randn(defEngine));
    }
    ~Rabbit(){cout << "C morreu";}
    virtual void dayPassed();
    virtual string letter(){return "C";}
    virtual bool SpeciesDictatingMovem(vector<string> sp);

    /*virtual bool move(vector<Animal*> an, vector<Food*> food)
    {
        for (auto at: an) {
            if (at->getweight() > 10){
                return false;
            }
        }
        return true;
    }
    virtual int chase(vector<Animal*> an, vector<Food*> food, map<int, int> distance){
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
    virtual bool AvoidAN(Animal *an);
    virtual bool moveAN  ( Animal* an);
    virtual bool moveFD  ( Food* fd);

    virtual void child(Animal* an);
    virtual bool child(int * distance);
    virtual vector<int> getDeadBody() { vector<int> a; return a; };

    virtual Animal* clone() {return new Rabbit(*this);}
};

class Sheep: public Animal{

public:
    Sheep(int id) : Animal(id, 30,5,1, 3){
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(4,8);
        setweight( randn(defEngine));
    }
    ~Sheep(){}

     virtual void dayPassed();
    virtual string letter(){return "O";}
    virtual bool SpeciesDictatingMovem(vector<string> sp);


    virtual bool AvoidAN(Animal *an);
    virtual bool moveAN  ( Animal* an);
    virtual bool moveFD  ( Food* fd);

    virtual void child(Animal* an);
    virtual bool child(int * distance);
    virtual vector<int> getDeadBody() { vector<int> a = {this->getweight(), 0}; return a;}

    virtual Animal* clone() {return new Sheep(*this);}
};

class Wolf: public Animal{
    int DaytoChild;
public:
    Wolf(int id) : Animal(id, 30,15,1,5){
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(5,40);
        this->DaytoChild = randn(defEngine);
    }
    ~Wolf() {}

    virtual void dayPassed();
    virtual string letter(){return "L";}
    virtual bool SpeciesDictatingMovem(vector<string> sp);
    virtual bool AvoidAN(Animal *an);
    virtual bool moveAN  ( Animal* an);
    virtual bool moveFD  ( Food* fd);

    virtual bool child(int * distance);
    virtual void child(Animal* an) {}
    virtual vector<int> getDeadBody() { vector<int> a = {10, 0}; return a;}

    virtual Animal* clone() {return new Wolf(*this);}
};

class Kangaroo: public Animal{
    Kangaroo* son;
public:
    Kangaroo(int id) : Animal(id, 20,20,1,7){ this->son = nullptr;}
    Kangaroo(int id, Kangaroo* a) : Animal(id, 20,10,1,7){this->son = a;}
    ~Kangaroo(){}


    virtual void dayPassed();
    virtual string letter(){return "G";}
    virtual bool SpeciesDictatingMovem(vector<string> sp);
    virtual bool AvoidAN(Animal *an);
    virtual bool moveAN  ( Animal* an);
    virtual bool moveFD  ( Food* fd);


    virtual bool child(int * distance);
    virtual void child(Animal* an) { this->son =(Kangaroo*) an;}
    virtual vector<int> getDeadBody() { return {15, 5};}

    virtual Animal* clone() {return new Kangaroo(*this);}
};


class Giraffe: public Animal{

public:
    Giraffe(int id) : Animal(id, 30,10,1,10){}
    ~Giraffe(){}

    virtual string letter(){return "M";}
    virtual bool SpeciesDictatingMovem(vector<string> sp) {return false;}
    virtual void dayPassed(){
        setage();
        if(this->gethealth() == 0) DIE();
        sethunger(gethunger()+4);
    }

    virtual bool AvoidAN(Animal *an){ return false;}
    virtual bool moveAN  ( Animal* an){ return false;}
    virtual bool moveFD  ( Food* fd) {if(fd->getLetter() == "a") return true; else return false;}


    virtual bool child(int * distance){
        if(getage() == 10){
            *distance = 1;
            return true;
        }

        return false;
    }
    virtual void child(Animal* an){}
    virtual vector<int> getDeadBody() { return {this->gethealth(), 10}; }

    virtual Animal* clone() {return new Giraffe(*this);}
};




#endif //TP_ANIMAL_H
