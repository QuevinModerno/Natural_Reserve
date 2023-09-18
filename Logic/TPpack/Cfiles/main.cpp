#include <iostream>
#include "../Headers/Simulator.h"
#include "../Headers/SimGUI.h"


using namespace std;
int main() {

    int rows, columns;
    cout << "       *********** NATURAL RESERVE ***********        " << endl << endl;
    cout << "Number of rows:"; cin >> rows;
    cout << "Number of columns:"; cin >> columns;

    Simulator *simulator = new Simulator(rows, columns);
    SimGUI gui(*simulator);
    gui.start();
    delete simulator;

    return 0;
}
