//
// Created by Quevin Moderno on 03/11/2022.
//

#include "../Headers/Simulator.h"

Simulator::Simulator(int rows, int columns) : reserve(rows, columns) {

    if(rows > 500)
        rows = MAX_SIZE_RESERVE;

    if(columns > 500)
        columns = MAX_SIZE_RESERVE;

}

Simulator::~Simulator(){ cout << "Simulator deleted.";} //delete this->reserve;}

void Simulator::NextInstant()
{
    day++;
    this->reserve.dayPassed();

}
void Simulator::NextInstant(int n)
{
    for(int i = 0; i < n; i++) {
        day++;
        cout << endl << endl;
        this->reserve.dayPassed();
        if (i != n - 1){
           cout << &reserve;
           cout << this->Elementsdetails();
        }
    }

}
void Simulator::NextInstant(int n, int p)
{
    for(int i = 0; i < n; i++) {
        day++;
        this->reserve.dayPassed();
        std::this_thread::sleep_for(std::chrono::milliseconds (p*1000));
        if (i != n - 1) {
            cout << &reserve;
            cout << this->Elementsdetails();
        }
    }

}
int Simulator::getday() {return day;}
string Simulator::Elementsdetails (){
    ostringstream oss;
    oss << "------- ELEMENT DETAILS ----------" << endl;
    oss << this->reserve.getshow() << endl;
    oss << "DAY: " << day << endl;
    return oss.str();
}

bool Simulator::ResrvState(){return this->endReserve;}
string Simulator::readConstants(){
    string com;
    ifstream myfile;
    ostringstream oss;

    myfile.open ("C:\\Users\\Quevin Moderno\\Desktop\\POO_V2\\TP\\constantes.txt");
    if(!myfile.is_open()) { return oss.str(); };

    oss << endl  << endl << "Reading constantes.txt.." << endl;
    while(getline(myfile, com))
    {
        oss << com << ";";
    }

    myfile.close();

    return oss.str();
}
bool Simulator::load(string file)
{
    loading = file;
    string txt = "C:\\Users\\Quevin Moderno\\Desktop\\POO_V2\\TP\\";
    txt += file;
    txt += ".txt";

    int nline = 0;
    string com;
    ifstream myfile;

    myfile.open (txt);
    if(!myfile.is_open()){  loading = "";return false;}


    while(getline(myfile, com))
    {
        if(nline == loaded) {
            loaded++;
            cout << "COmando: " << nline << com;
        }
        nline++;
    }


    loaded = 0;
    loading = "";
    myfile.close();
    return false;
}

int Simulator::getCommand()
{
    string txt;
    int x = false;


    if(!loading.empty()){
        x = load(loading);
        return true;
    }
    else{
        getline( cin, txt);

        if(txt.empty())
            getline(cin, txt);
         x = this->comand(txt);
    }

    if(txt == "exit") endReserve = true;

    return x;
}

int Simulator::comand(string txt)
{
    bool made = false;
    istringstream iss(txt);
    string arg;
    vector<string> sprComands;

    while (iss >> arg){
        sprComands.push_back(arg);
    }


    if(sprComands[0] == "animal" || sprComands[0] == "food")
    {
        if( sprComands.size() == 4)
            made = reserve.AddinReserve(sprComands[0], sprComands[1], stoi(sprComands[2]),stoi(sprComands[3] ));
        else
            if(sprComands.size() == 2)
                made = reserve.AddinReserve(sprComands[0], sprComands[1]);
            else return false;
    }
    else if(sprComands[0] == "kill"){ if( sprComands.size() == 3)   made = reserve.EraseinReserve( sprComands[0], stoi(sprComands[2]), stoi(sprComands[3]) ); else return false; }

    else if(sprComands[0] == "killid"){ if( sprComands.size() == 2) made = reserve.EraseinReserve( stoi(sprComands[1]) ); else return false;}

    else if(sprComands[0] == "feed"){ if( sprComands.size() == 5)   made = reserve.feed( stoi(sprComands[1]), stoi(sprComands[2]), stoi(sprComands[3]), stoi(sprComands[4]) ); else return false; }

    else if(sprComands[0] == "feedid"){ if( sprComands.size() == 4) made = reserve.feed( stoi(sprComands[1]), stoi(sprComands[2]), stoi(sprComands[3]) ); else return false; }

    else if(sprComands[0] == "nofood")
    {
        if( sprComands.size() == 3)
            made =reserve.EraseinReserve(sprComands[0], stoi(sprComands[1]), stoi(sprComands[2]));
        else
            if(sprComands.size() == 2)
                made = reserve.EraseinReserve( stoi(sprComands[1]));
    }

    else if(sprComands[0] == "empty"){ if( sprComands.size() == 3) made = reserve.EraseinReserve( sprComands[0],stoi(sprComands[1]),stoi(sprComands[2]) ); else return false; }

    else if(sprComands[0] == "slide"){ if( sprComands.size() == 3) made = reserve.VisibleZone( sprComands[1],stoi(sprComands[2]) ); else return false;}
    else if(sprComands[0] == "load"){ return load(sprComands[1]);}
    else if(sprComands[0] == "see"){ if( sprComands.size() == 3) showGUI = reserve.see( stoi(sprComands[1]),stoi(sprComands[2]) ); else return false;made = true; }
    else if(sprComands[0] == "info"){ if( sprComands.size() == 2) showGUI = reserve.info( stoi(sprComands[1]) ); else return false; made = true;}
    else if(sprComands[0] == "anim"){ showGUI = reserve.getIDs(); return true;}
    else if(sprComands[0] == "visanim"){ showGUI = reserve.getvisIDs(); return true;}
    else if(sprComands[0] == "n")
    {
        if( sprComands.size() == 3)
            NextInstant(stoi(sprComands[1]), stoi(sprComands[2]));
        else
            if( sprComands.size() == 2)
                NextInstant(stoi(sprComands[1]));

            else NextInstant();
        made = true;
    }
    else if(sprComands[0] == "store"){if( sprComands.size() == 2){  saveName = (string)sprComands[1]; return 2;}}
    else if(sprComands[0] == "restore"){if( sprComands.size() == 2){ saveName = (string)sprComands[1]; return 3;}}
    else if(sprComands[0] == "exit"){this->endReserve = true; return 0;}
    else return false;

    return made;
}


ostream& operator<<(ostream& output, Simulator* sim){

    output << &sim->reserve;
    return output;
}