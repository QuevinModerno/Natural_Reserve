//
// Created by Quevin Moderno on 24/11/2022.
//

#ifndef TP_SIMGUI_H
#define TP_SIMGUI_H

#include "SaveState.h"

class SimGUI {
    Simulator simulator;
    vector<SaveState*> states;

public:
    SimGUI(Simulator &sim);
    ~SimGUI();

    void start();
    void save();
    void restore();
};


#endif //TP_SIMGUI_H
