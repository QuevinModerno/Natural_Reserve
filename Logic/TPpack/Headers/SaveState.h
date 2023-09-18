//
// Created by Quevin Moderno on 24/12/2022.
//

#ifndef TP_SAVESTATE_H
#define TP_SAVESTATE_H
#include "Simulator.h"

class SaveState {
    string name;
    Simulator simulator;
    int day;

public:
    SaveState(Simulator& sim): simulator(sim){
        name = simulator.saveName;
        day = simulator.getday();
    }

    string getName(){return this->name;}
    int getDay(){return this->day;}
    Simulator getSIM(){return this->simulator;}
};


#endif //TP_SAVESTATE_H
