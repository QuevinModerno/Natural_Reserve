//
// Created by Quevin Moderno on 09/11/2022.
//

#ifndef TP_FOOD_H
#define TP_FOOD_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

class Food {
    int ID;
    string let;

    int age;
    int nutricity;
    int toxicity;
    bool dead;

public:
    Food(string specie,int id);
    Food(int id, int nutri, int tox);
    virtual ~Food();

    int getID() const {return this->ID;}
    int getnutricity() const {return this->nutricity;}
    int getoxicity() const {return this->toxicity;}
    int getage() const {return this->age;}
    bool getdead(){return this->dead;}

    void setoxicity(int n){this->toxicity = n;}
    void setnutricity(int n){this->nutricity = n;}
    virtual string getLetter() = 0;
    virtual void dayPassed(){this->age++;}


    void DIE(){ this->dead = true;}
    friend ostream& operator<< (ostream& output, Food* a);
};

class Grass : public Food{

public:
    Grass(int id):Food(id, 3, 0){}
    ~Grass(){}

    virtual string getLetter() {return "r";}
    virtual void dayPassed(){ if(this->getage() == 20) DIE();}
};
class Carrot : public Food{

public:
    Carrot(int id):Food(id, 4, 0){}
    ~Carrot(){}

    virtual string getLetter() {return "t";}
    virtual void dayPassed();
};
class Body : public Food{
    int In_nutricity;
public:
    Body(int id, int n, int t):Food(id, n, t){ this->In_nutricity = n;}
    ~Body(){}

    virtual string getLetter() {return "p";}
    virtual void dayPassed();
};
class Meet : public Food{

public:
    Meet(int id):Food(id, 10, 2){}
    ~Meet(){}

    virtual string getLetter() {return "b";}
    virtual void dayPassed();
};
class Mistery : public Food{

public:
    Mistery(int id):Food(id, 4, 0){}
    ~Mistery(){}

    virtual string getLetter() {return "a";}
    virtual void dayPassed(){ if(this->getage() == 20) DIE();}
};




#endif //TP_FOOD_H
