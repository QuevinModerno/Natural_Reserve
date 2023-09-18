//
// Created by Quevin Moderno on 03/11/2022.
//

#ifndef TP_SIMULATOR_H
#define TP_SIMULATOR_H
#include "Reserve.h"

#include <fstream>
#include <chrono>
#include <thread>
#define MAX_SIZE_RESERVE 500;

static string loading;
static int loaded = 0;
static int day = 0;

using namespace std;

class Simulator {

    Reserve reserve;

    int comand(string txt);
    bool load(string file);

    void NextInstant();
    void NextInstant(int n);
    void NextInstant(int n, int p);

    bool endReserve = false;
    string showGUI;
public:
    Simulator(int rows, int columns);

    ~Simulator();
    string getshow(){string a = showGUI; showGUI = ""; return a;}
    string readConstants();
    int getCommand();
    bool ResrvState();
    string Elementsdetails ();
    string saveName;
    int getday();


    friend ostream& operator<<(ostream& output, Simulator* sim);
};


#endif //TP_SIMULATOR_H
