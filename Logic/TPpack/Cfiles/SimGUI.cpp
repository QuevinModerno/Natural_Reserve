//
// Created by Quevin Moderno on 24/11/2022.
//

#include "../Headers/SimGUI.h"


SimGUI::SimGUI(Simulator &sim): simulator(sim){}

SimGUI::~SimGUI(){}

/* Return values of start function. Meaning:

 * 0. Problem with writen comand
 * 1. Comand was interpreted. Show simulator
 * 2. Save simulator
 * 3. Restore simulator

*/
void SimGUI::start() {

    bool ComdMade = true;
    int returnValue;
    string txt;
    cout << simulator.readConstants();
    do{
        if(ComdMade){
            cout << &simulator;
            cout << this->simulator.Elementsdetails() << endl;
            cout << "------- INFO COMMANDS ----------" << endl;
            cout << simulator.getshow();


            cout << endl << endl << "***Insert commands:  ***" << endl;
        }
        else {cout << "\tError: Problems with writen commands!!" << endl <<"***Insert commands::  ***" << endl;}
        returnValue = this->simulator.getCommand();

        if(returnValue == 0)ComdMade = false;
        else if(returnValue == 1) ComdMade = true;
        else if(returnValue == 2) save();
        else if(returnValue == 3) restore();


    }while(!this->simulator.ResrvState());

    cout << "Reserved closed!" << endl;
}

void SimGUI::save(){

    states.push_back( new SaveState (simulator));

cout << &simulator;

}
void SimGUI::restore(){

    for(int i =0; i <states.size(); i ++)
        if(states[i]->getName() == simulator.saveName) {
            this->simulator = states[i]->getSIM();
            day = states[i]->getDay();
        }

}
// 0 continuar
// 1. instante passado a frente (mostrar os detalhes)
// 2. passar n instantes a frente
// 3. passar n p instantes
// 4. save!
// 5. restore!
