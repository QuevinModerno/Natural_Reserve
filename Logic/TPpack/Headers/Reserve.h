//
// Created by Quevin Moderno on 03/11/2022.
//

#ifndef TP_RESERVE_H
#define TP_RESERVE_H

#include "Animal.h"
#include "Food.h"
#define VISIBLEROWS 20
#define VISIBLELINES 20

static int ID = 0;

class Reserve {
    map< int, vector<int> > positions;
    vector<Animal*> animals;
    vector<Food*> food;


    int visibleRows[2] = {1, VISIBLEROWS};
    int visibleColumns[2] = {1, VISIBLELINES};
    int ROWS;
    int COLUMNS;

    void AddinMap(int rows, int columns);
    bool PositionAvailable(string specie, const vector<int> &pos);
    string findinPosition(const vector<int> &pos);
    vector<int> getIDbyPosition(const vector<int> &pos);
    int Distance(int IDactual, int IDsecond);
    vector<string> getSpecies(vector<int> neighboursIDs);
    int IDirection (int id, Animal* an);

    void setPosition(int id, vector<int> pos);
    vector<int> getPosition(int id);

    int chooseDirection(Animal * an, vector<int> neighboursIDs);//, vector<Animal*> anim, vector<Food*> fd);
   // void keepSurroundingAnimals(vector<int> ids, vector<Animal*> anim, vector<Food*> fd);
    bool checKill(Animal *an, vector<int> chaseIDs);
    void dead(Animal * an);
    void dead(Food * an);
    void addChild(Animal *an);
    void addChild(Food* fd);
    Animal* chooseAnimal(string spec, int id);
    Food* chooseFood(string spec, int id);

    bool AddinReserve(string specie, int rows, int columns);
    vector<Animal*> IDtoAnimal(vector<int> ids);
    vector<Food*> IDtoFood(vector<int> ids);

    string show;
public:

    Reserve(int rows, int columns);
    Reserve(const Reserve& ref);
    ~Reserve();
    friend ostream& operator<<(ostream& output, Reserve* x);
    Reserve& operator=(const Reserve& res);

    string getIDs();
    string getvisIDs();

    bool AddinReserve(string type, string specie, int rows, int columns);
    bool AddinReserve(string type, string specie);

    bool EraseinReserve(int id);
    bool EraseinReserve(string com, int row, int column);


    bool feed(int id, int nutricity, int toxicity );
    bool feed(int id, int nutricity, int toxicity, string specie );
    bool feed(int row, int column,int nutricity, int toxicity);
    string see(int row, int column);
    string info(int nid);

    bool VisibleZone(string direction, int quantity);


    void dayPassed();
    void move(Animal * an);
    vector<int> findNeighboursIDs(Animal * an);//, vector<Animal*> anim, vector<Food*> fd, vector<string> spec);
    string getshow();
    void setshow(string s){this->show += s;}
};


#endif //TP_RESERVE_H
