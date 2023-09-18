//
// Created by Quevin Moderno on 09/11/2022.
//

#include "../Headers/Food.h"


Food::Food(string specie,int id):let(specie), ID(id){}
Food::Food(int id, int nutri, int tox): ID(id), nutricity(nutri), toxicity(tox), dead(false){}
Food::~Food(){}

ostream& operator<< (ostream& output, Food* a)
{
    output << a->ID << ": Food " << a->getLetter() << " Nutricity:" << a->nutricity << " Toxicity:" << a->toxicity <<endl;
    return output;
}


void Carrot::dayPassed() {
    int a = this->getage();

    if(a == 10 || a == 20 || a == 30)
        setoxicity(this->getoxicity() +1);
}
void Body::dayPassed()  {
    setnutricity(getnutricity() - 1);

    if( (this->In_nutricity * 2) < getage() )
        setoxicity(getoxicity() + 1);
}
void Meet::dayPassed() {
    if(this->getage() == 30) DIE();

    if(this->getnutricity() != 0)
        setoxicity(this->getnutricity()-1);
}
