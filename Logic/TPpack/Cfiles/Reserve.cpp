//
// Created by Quevin Moderno on 03/11/2022.
//

#include "../Headers/Reserve.h"



Reserve::Reserve(int rows, int columns):ROWS(rows), COLUMNS(columns), show("")
{
    if(rows < this->visibleRows[1])
        this->visibleRows[1] = rows;
    if(columns < this->visibleColumns[1])
        this->visibleColumns[1] = columns;
}

Reserve::Reserve(const Reserve& ref): ROWS(ref.ROWS), COLUMNS(ref.COLUMNS), show("")
{
    if(ref.ROWS < this->visibleRows[1])
        this->visibleRows[1] = ref.ROWS;
    if(ref.COLUMNS < this->visibleColumns[1])
        this->visibleColumns[1] = ref.COLUMNS;

    for(auto it: ref.animals)
        delete it;
    for(auto it : ref.food)
        delete it;

    animals.clear();
    food.clear();
    positions.clear();

    this->positions.insert(ref.positions.begin(), ref.positions.end());


    for(auto it: ref.animals)
        this->animals.push_back(it);
    for(auto it : ref.food)
        this->food.push_back(it);
}


Reserve& Reserve::operator=(const Reserve& ref)
{
    if( this == &ref) return *this;

    for(auto it: ref.animals)
        delete it;
    for(auto it : ref.food)
        delete it;

    animals.clear();
    food.clear();
    positions.clear();


    for(auto it: ref.animals)
        this->animals.push_back(it->clone());
    for(auto it : ref.food)
        this->food.push_back(it);

    return *this;
}


Reserve::~Reserve(){
    for(auto it: animals)
        delete it;
    for(auto it : food)
        delete it;

    cout << "Reserve deleted.";
}


void Reserve::setPosition(int id, vector<int> pos)
{
    for (auto it = this->positions.begin(); it != this->positions.end(); it++)
        if (it->first == id){
           it->second = pos;
        }
}
vector<int> Reserve::getPosition(int id)
{
    for (auto it = this->positions.begin(); it != this->positions.end(); it++)
        if (it->first == id)
        {
            return it->second;
        }
    vector<int> x;
    return x;
}



//verify if there is any animal or food in a determined position
bool Reserve::PositionAvailable(string specie, const vector<int> &pos) {


    if( (pos[0] < 1) || (pos[0] > this->ROWS+1) || (pos[1] < 1) || (pos[1] > this->COLUMNS+1))
        return false;


    //In case you want add FOOD on the map
    // verify if there is already food in that position
    if(specie == "r" || specie == "t" || specie == "b" || specie == "a"){
        for (auto it = this->positions.begin(); it != this->positions.end(); it++)
            if (it->second == pos)
            {
                for(auto at : food)
                    if(it->first == at->getID())
                        return false;
            }
    }

    return true;
}


//Returns what is found in a position (empty, food or animal)
// Max two animals shown
//In case there is at least one animal in one position the food won´t be showed
string Reserve::findinPosition(const vector<int> &pos)
{
    int idd, nofanim = 0;
    string stReturn;
    ostringstream oss;
    bool add = false;

    if(this->positions.empty()){
        oss << "   ";
        return oss.str();
    }


    for(auto it = this->positions.begin(); it != this->positions.end(); it++){
         if(it->second == pos)
        {
             add = true;
            idd = it->first;
            for(int i = 0;  i< this->animals.size(); i++)
                if(this->animals[i]->getID() == idd){
                    if(nofanim < 2) { //showing max two animals in the same position
                        oss << this->animals[i]->letter();
                        nofanim++;
                    }
                }

            for(auto at : this->food)
                if(at->getID() == idd){
                    oss << at->getLetter();
                    nofanim++;
                    break;
                }
        }
    }

    if(nofanim == 1){
        oss << "  ";
    }
    else
        if(nofanim == 2)
            oss << " ";
    if(!add)
        oss << "   ";

    return oss.str();
}
vector<int> Reserve::getIDbyPosition(const vector<int> &pos)
{
    vector<int> ids;
    for(auto it = this->positions.begin(); it != this->positions.end(); it++)
        if(it->second == pos) ids.push_back(it->first);

    return ids;
}

void Reserve::AddinMap( int rows, int columns)
{
    vector<int> pos {rows,columns};

    this->positions.insert( {ID, pos} );
}

bool Reserve::AddinReserve(string type, string specie,int rows, int columns){

    if(!PositionAvailable(specie, {rows, columns} ))
        return false;

    if (type == "animal"){
        if (specie == "C" || specie == "O" || specie == "L" || specie == "G" || specie == "M"){
            ID++;
            this->animals.push_back(chooseAnimal(specie, ID));
        }
        else return false;
    }
    else
        if(type == "food")
            if (specie == "r" || specie == "t" || specie == "b" || specie == "a" || specie == "p"){
                ID++;
                this->food.push_back(chooseFood(specie, ID));
            }
            else return false;

        else return false;

    AddinMap(rows, columns);
    return true;
}
bool Reserve::AddinReserve(string specie,int rows, int columns){

    if(!PositionAvailable(specie, {rows, columns} ))
        return false;


    if (specie == "C" || specie == "O" || specie == "L" || specie == "G" || specie == "M") {
        ID++;
        this->animals.push_back(chooseAnimal(specie, ID));
    }
    else
        if(specie == "r" || specie == "t" || specie == "b" || specie == "a"|| specie == "p"){
            ID++;
            this->food.push_back(chooseFood(specie, ID));
        }

        else return false;

    AddinMap(rows, columns);

    return true;
}

bool Reserve::AddinReserve(string type, string specie)
{

    if (type == "animal")
        if (specie == "C" || specie == "O" || specie == "L" || specie == "G" || specie == "M"){
            ID++;
            this->animals.push_back(chooseAnimal(specie, ID));
        }
        else return false;
    else
        if(type == "food")
            if(specie == "r" || specie == "t" || specie == "b" || specie == "a"|| specie == "p"){
                ID++;
                this->food.push_back(chooseFood(specie, ID));
            }
            else return false;
        else return false;

    int x,y;
    default_random_engine defEngine(time(nullptr));
    uniform_int_distribution<int> intRows(1,this->ROWS);
    uniform_int_distribution<int> intColumns(1,this->COLUMNS);


    do {
        x= intRows(defEngine);
        y= intColumns(defEngine);
    }while(  !(PositionAvailable(specie, {x, y}))  );


    AddinMap(x, y);

    return true;
}

bool Reserve::EraseinReserve(int id)
{
    bool erased = false;

    for(int i =0; i < this->animals.size(); i++)
        if(this->animals[i]->getID() == id) {
            this->animals.erase(this->animals.begin()+ i);
            erased = true;
            break;
        }



    if(!erased)
    {
        for(int i =0; i < this->food.size(); i++)
            if(this->food[i]->getID() == id) {
                this->food.erase(this->food.begin()+ i);
                erased = true;
                break;
            }
    }
    // Find the ID and erase it in the reserve!
    if(erased){
        for (auto it = this->positions.begin(); it != this->positions.end(); it++)
            if (it->first == id) {this->positions.erase(it); return true;}

    }

    return false;
}
bool Reserve::EraseinReserve(string com, int rows, int columns)
{

    vector<int> IdsinPos = getIDbyPosition({rows, columns});
    vector<int> idstoErase;
    bool eraseAll = false;

    if(IdsinPos.empty()){ return false; }

    if(com == "empty"){ eraseAll = true;}

    if(com == "kill" || eraseAll)//animal
    {
        for(int i =0; i < this->animals.size(); i++)
            for(int j = 0; j < IdsinPos.size(); j++)
                if(this->animals[i]->getID() == IdsinPos[j]) {
                    this->animals.erase(this->animals.begin()+ i);
                    idstoErase.push_back(IdsinPos[j]);
                }
    }

    if(com == "nofood"|| eraseAll)//food
    {
        for(int i =0; i < this->food.size(); i++)
            for(int j = 0; j < IdsinPos.size(); j++)
                if(this->food[i]->getID() == IdsinPos[j]) {
                    this->food.erase(this->food.begin()+ i);
                    idstoErase.push_back(IdsinPos[j]);
                }

    }

    bool breaking = false;
    // Find the ID and erase it in the reserve!
    if(!idstoErase.empty())
    {
        int reps = 0;

        do{
        for (auto it = this->positions.begin(); it != this->positions.end(); it++){

            for(int i = 0; i < idstoErase.size(); i++)
                if (it->first == idstoErase[i]) {
                    this->positions.erase(it);
                    breaking = true;
                    break;
                }
            if(breaking) break;
        }
            breaking = false;
            reps++;
        }while(reps != idstoErase.size());
        return true;
    }

    return false;
}

bool Reserve::feed(int id, int nutricity, int toxicity )
{
    for(int i = 0; i < this->animals.size(); i++){

        if(this->animals[i]->getID() == id){
            this->animals[i]->feed("user", nutricity, toxicity);
            return true;
        }
    }

    return false;
}
bool Reserve::feed(int id, int nutricity, int toxicity, string specie )
{
    for(int i = 0; i < this->animals.size(); i++){

        if(this->animals[i]->getID() == id){
            this->animals[i]->feed(specie, nutricity, toxicity);
            return true;
        }
    }

    return false;
}
bool Reserve::feed(int row, int column,int nutricity, int toxicity  )
{
    vector<int> IdsinPos = getIDbyPosition({row, column});
    int fed = false;

    for(int i = 0; i < this->animals.size(); i++){
        for(int j = 0; j < IdsinPos.size(); j++)

            if(this->animals[i]->getID() == IdsinPos[j]) {
                fed = true;
                this->animals[i]->feed("user", nutricity, toxicity);
             }
    }

    if(fed){ return true;}
    return false;
}

string Reserve::info(int nid)
{
    ostringstream output;
    for(int i = 0; i < this->animals.size(); i++)
            if(nid == animals[i]->getID())
                output << animals[i] ;

    for(int i = 0; i < this->food.size(); i++)
            if(nid == food[i]->getID()){
                output << food[i];
                break;
            }

    return output.str();
}
string Reserve::see(int row, int column)
{
    string returning;
    vector<int> ids = getIDbyPosition({row, column});

    for(int i = 0; i < ids.size(); i++)
        returning += info(ids[i]);

    return returning;
}
string Reserve::getIDs(){
    ostringstream oss;

    oss << ".Anim:" << endl;
    for(auto at: animals){
        oss <<"ID " << at->getID() << "-> " << at->letter() << ". Health: " << at->gethealth() << endl;
    }

    return oss.str();
}

string Reserve::getvisIDs() {
    ostringstream oss;
    vector<int> pos;

    oss << ".Visanim:" << endl;
    for(auto at: animals){

        pos = getPosition(at->getID());

        if(pos[0] >= this->visibleRows[0] && pos[0] <= this->visibleRows[1])
            if(pos[1] >= this->visibleColumns[0] && pos[1] <= this->visibleColumns[1])
                oss <<"ID " << at->getID() << "-> " << at->letter() << ". Health: " << at->gethealth() << endl;
    }

    return oss.str();
}

//ALTER THE VISIBLE ZONE (slide)
bool Reserve::VisibleZone(string direction, int quantity)
{

    // 4 ifs em relacao a direcao
    if(direction == "up")
    {
        //confirmacoes

        if( (this->visibleRows[0] - quantity) < 1)
            return false;

        this->visibleRows[1] -= quantity;
        this->visibleRows[0] -= quantity;

    }
    else
    if(direction == "down"){

        if( (this->visibleRows[1] + quantity) > this->ROWS)
            return false;

        this->visibleRows[0] += quantity;
        this->visibleRows[1] += quantity;
    }
    else
    if(direction == "right")
    {

        if( (this->visibleColumns[1] + quantity) > this->COLUMNS)
            return false;


        this->visibleColumns[0] += quantity;
        this->visibleColumns[1] += quantity;

    }
    else
    if(direction == "left")
    {
        if( (this->visibleColumns[0] - quantity) < 1)
            return false;

        this->visibleColumns[1] -= quantity;
        this->visibleColumns[0] -= quantity;
    }

    return true;
}

ostream& operator<<(ostream& output, Reserve* resv){

    output << endl << endl << "   ";

    for(int c =resv->visibleColumns[0]; c <= resv->visibleColumns[1]; c++){
        if(c < 10)
            output << c << "    ";
        else
            output << c << "   ";
    }


    output << endl;
    for(int r = resv->visibleRows [0]; r <= resv->visibleRows[1] ; r++){

        output << r <<" ";

        for(int c =resv->visibleColumns[0]; c <= resv->visibleColumns[1]; c++)
            output << "+___*" ;

        output << endl << "  ";
        for(int c =resv->visibleColumns[0]; c <= resv->visibleColumns[1]; c++)
            output << "|" << resv->findinPosition({r,c} ) << "|";
        output << endl;

    }
    output << endl << endl << endl;


    return output;
}
string Reserve::getshow()
{
    ostringstream oss;

    oss << "Animals: " << animals.size() << "\t Food: " << food.size() << endl;
    oss << show; show = "";
    return oss.str();
}

//MOVEMENT OF ANIMALS
/*
void Reserve::keepSurroundingAnimals(vector<int> ids, vector<Animal*> anim, vector<Food*> fd)
{
    for(auto it : animals)
        for(auto iD : ids)
            if(it->getID() == iD)
                anim.push_back(it);


    for(auto it : food)
        for(auto iD : ids)
            if(it->getID() == iD)
                fd.push_back(it);
}
*/
//finds all species IDs surrounding a certain animal(an)
/*vector<int> Reserve::findNeighboursIDs(Animal * an)//, vector<Animal*> anim, vector<Food*> fd, vector<string> spec) {
{
    vector<int> anPosition;
    vector<int> neighboursIDs;

    //Find the position of the animal
    for (auto it: positions)
        if (an->getID() == it.first){
            anPosition = it.second;
            break;
        }
    cout << " *** Animais no mapa: ****" << endl;
    for(auto a : animals)
        cout << a->getID() << " " << a->letter() << endl;

    cout << "***********" << endl;

    cout << "Animal " << an->getID() << "position:" << anPosition[0] << "," << anPosition[1] << endl;
    //Find the ID of the species in his neighbourhood
    for (auto at: positions) {

        if (anPosition[0] == at.second[0] && anPosition[0] == at.second[0]);
        else if (
                (anPosition[0] - an->getvision()) <= at.second[0] &&      //limite inferior

                at.second[0] <= (anPosition[0] + an->getvision()) &&      //limite superior

                (anPosition[1] - an->getvision()) <= at.second[1] &&      //limite lateral esquerdo

                at.second[1] <= (anPosition[1] + an->getvision())           //limite lateral direito

                ) {
            neighboursIDs.push_back(at.first);
        }
    }
    return neighboursIDs;
}

 */

int Reserve::IDirection (int id, Animal* an)
{
    vector<int> posNeigh = getPosition(id);
    vector<int> pos = getPosition(an->getID());
    int difRows;
    int difCols;


    difRows = posNeigh[0]- pos[0];
    difCols = posNeigh[1]- pos[1];

    if(difCols > 0) return 0; //RIGHT
    if(difCols < 0) return 1; //LEFT
    if(difRows < 0) return 2; //ABOVE
    if(difRows > 0) return 3; //DOWN

    return 5; //Same position

    /*if( posNeigh[0] >= (pos[0] - an->getvision() ) &&
        posNeigh[0] <= (pos[0] + an->getvision() )
     )
    {
        //MEANS NEIGHBOUR IS AT THE RIGHT (dirc = 0)
        if(posNeigh[1] >=  (pos[1] + 1)     &&      posNeigh[1] <= (pos[1] + an->getvision()))
            return 0;

        else //LEFT (dirc = 1)
            if(posNeigh[1] >= pos[1] - an->getvision()     &&      posNeigh[1] >= pos[1] - 1)
                return 1;
    }


    if( posNeigh[1] >= (pos[1] - an->getvision() ) &&
        posNeigh[1] <= (pos[1] + an->getvision() )
            )
    {
        //MEANS NEIGHBOUR IS UP (dirc = 2)
        if(posNeigh[0] >= (pos[0] - an->getvision())     &&      posNeigh[0] <= (pos[0] - 1))
            return 2;

        else //DOWN (dirc = 3)
            if(posNeigh[0] >= pos[0] + 1     &&      posNeigh[0] >= pos[0] + an->getvision())
                return 3;
    }
    */


}
vector<Animal*> Reserve::IDtoAnimal(vector<int> ids)
{
    vector<Animal*> anim;

    for (auto it: animals)
        for (auto iD: ids)
            if (it->getID() == iD)
                anim.push_back(it);

    return anim;
}
vector<Food*> Reserve::IDtoFood(vector<int> ids)
{
    vector<Food*> anim;

    for (auto it: food)
        for (auto iD: ids)
            if (it->getID() == iD)
                anim.push_back(it);

    return anim;
}



bool Reserve::checKill(Animal *an, vector<int> chaseIDs)
{
    int distan = 10;
    int chaseID;
    for(auto it : chaseIDs){
        int d = Distance(an->getID(), it);
        if( d < distan){
            chaseID = it;
            distan = d;
        }
    }


    if (distan <= an->getsteps()){

        setPosition(an->getID(),  getPosition(chaseID)); //goes to his position
        vector<int> pos = getPosition(an->getID());

        vector<Food*> fd = IDtoFood({chaseID} );
        vector<Animal*> ChaseAn = IDtoAnimal({chaseID} );

        //IN THE CASE THE ANIMAL EATS:

        //FOOD: feeds him!
        if(!fd.empty()){
            feed(an->getID(), fd[0]->getnutricity(),fd[0]->getoxicity(), fd[0]->getLetter());
        }
        else
            //Animal: Creates a dead body in the right position
        if(!ChaseAn.empty()){

            for(auto it:animals)
                if(an->getID() == it->getID())
                    it->setHistory(ChaseAn[0]->letter(), ChaseAn[0]->getID());

            if(ChaseAn[0]->letter() != "C") {//Case it is a rabbit nothing gets done
                ID++;
                AddinMap(pos[0], pos[1] + 1);
                vector<int> add = an->getDeadBody();
                this->food.push_back(new Body(ID, add[0], add[1]));

            }
        }

        ostringstream oss;
        oss << "ID " << an->getID() << " killed ID " << chaseID << endl;
        setshow(oss.str());
        EraseinReserve(chaseID);
        return true;
    }
    return false;
}
//Calculates the distance between two species
int Reserve::Distance(int IDactual, int IDsecond)
{
    vector<int> posAct, posSec;
    int distance;

    for(auto it: positions)
    {
        if(it.first == IDactual)
            posAct = it.second;
        if(it.first == IDsecond)
            posSec = it.second;
    }

    distance = posAct[0] - posSec[0];
    distance += (posAct[1] - posSec[1]);

    if(distance < 0)
        distance = distance * (-1);


    return distance;

}
//returns the direction more favourable for the animal(an). Case it has a specie close enough goes to his position and returns ""
int Reserve::chooseDirection(Animal * an, vector<int> neighboursIDs){
    int dirc, n, direc;
    vector<Animal*> anim = IDtoAnimal(neighboursIDs);
    vector<Food*> fd = IDtoFood(neighboursIDs);
    map<int, int> IDnDIR;
    vector<int> avoid;
    vector<int> chase;
    vector<int> killIDs;

    /*for(auto at:neighboursIDs)
        IDnDIR.insert({at,IDirection(at, an)} );
    */
    //para cada animal
    for(auto at : anim) {
             //ver a sua direcao em relacao ao animal principal
       direc = IDirection(at->getID(), an);

        if (an->AvoidAN(at))
            avoid.push_back(direc);

        else if (an->moveAN(at)) {
            chase.push_back(direc);

            killIDs.push_back(at->getID());
        }

    }

    for(auto it : fd) {
        direc = IDirection(it->getID(), an);
        cout << direc << "direc" << endl;
        /*for (auto it = IDnDIR.begin(); it != IDnDIR.end(); it++)
            if (it->first == at->getID()) {
                direc = it->second;
                break;
            }
            */
        if (an->moveFD(it)){
            chase.push_back(direc);

            killIDs.push_back(it->getID());
        }
    }
    //cout << "Posicoes que estao no chase:" << endl;


    // case there is some direction to avoid, the opposite side is placed on the chase vector
    for(int i =0;i < avoid.size(); i++) {
        dirc = avoid[i];

        if (dirc == 0) dirc = 1; else if (dirc == 1) dirc = 0; else if (dirc == 2) dirc = 3; else if (dirc == 3) dirc = 2;

        chase.push_back(dirc);
    }

    //case there is some direction being avoided and chased at the same time, gets avoided
    for(int i = 0; i < chase.size(); i++)
        for(auto at:avoid)
            if( chase[i] == at)
                chase.erase(chase.begin() + i);

//debug

    if(chase.empty())
        return 4;
   /* cout << "chase ";
    for(auto it : chase)
        cout << it<< "  ";

    //cout << "Posicoes que estao no avoid:" << endl;
    cout << endl << "Avoid ";
    for(auto it : avoid)
        cout << it<< "  ";
        */

    if(chase.size() > 1){
        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(0,avoid.size());
        n= randn(defEngine);
    }
    else n = 0;

    //if there is some animal in the same position give priority

    checKill(an, killIDs);
    /*for(auto it : killIDs)
        if(it == 4)
            if( checKill(an, it, Distance(an->getID(), it)) )
                return -1;

    //check wether any animal can be eaten
    for(auto it : killIDs)
        if( checKill(an, it, Distance(an->getID(), it)) )
            return -1;

     */
    return chase[n];
}
/*
    if (!an->move(anim, fd)) {

    }




    if (dirc == 0) dirc = 1; if (dirc == 1) dirc = 0; if (dirc == 2) dirc = 3; if (dirc == 3) dirc = 2;
    return dirc;





    // Lines[0] inicio das linhas; Lines[1] Fim das linhas. Same para columns
    vector<int> pos = getPosition(an->getID());
    int Lines = pos[0], column = pos[1], iniLine, endLine, iniColm, endColm;
    vector<int> idsNeighbours;
    vector<Animal*> chaseAN;
    vector<Food*> chaseFD;
    vector<string> AvailableDir;
    map<int, string> specieDir;
    map<int, int> distan;


    //gets species from a certain direction
    for(int dirc = 0; dirc < 4; dirc++) {
        //DIREITA
        if (dirc == 0) {
            iniLine = (Lines - an->getvision() );
            endLine = (Lines + an->getvision() );
            iniColm = (column + 1);
            endColm = (column + an->getvision());
        }
        // LEFT
        else if (dirc == 1) {
            iniColm = column - an->getvision();
            endColm = column - 1;
        }
            //UP
        else if (dirc == 2) {
            iniLine = Lines - an->getvision();
            endLine = Lines - 1;
            iniColm = column - an->getvision();
            endColm = column + an->getvision();
        }
            //DOWN
        else if (dirc == 3) {
            iniLine = Lines + 1;
            endLine = Lines + an->getvision();
        }

        if(iniLine < 0 ) iniLine = 0; if(endLine < 0) endLine = 0;
        if(iniLine > ROWS) iniLine = ROWS; if (endLine > ROWS) endLine = ROWS;
        if(iniColm < 0 ) iniColm = 0; if(endColm < 0) endColm = 0;
        if(iniColm > COLUMNS) iniColm = COLUMNS; if (endColm > COLUMNS) endColm = COLUMNS;


        forget
         *  esquerda : col = 1
         *  direita : col = COLUMNS
         *  cima : lines = 1;
         *  baixo : lines = ROWS
        ;

        //Ignore a direction in case its on a border and has nothing in it!
    if( dirc == 0 && endColm == COLUMNS ||
        dirc == 1 && iniColm == 0 ||
        dirc == 2 && iniLine == 0 ||
        dirc == 3 && iniLine == ROWS
        ) ;
    else{



        //gets species from a certain direction
        for (int i = iniLine; i < endLine; i++)
            for (int j = iniColm; j < endColm; j++) {
                vector<int> x = getIDbyPosition({i, j});
                //vector because it might be more than one animal in one position
                if (!x.empty()) {

                    for (auto at: x){
                        idsNeighbours.push_back(at);
                        cout << "vim aqui" <<  dirc << endl;
                    }
                }
            }

        cout << endl << endl;
        for( auto it : idsNeighbours){
            cout << it << ": Animal perseguido" << endl;
        }

        if (!idsNeighbours.empty()) {
            //transfer ids to vector of animals and food
            //keepSurroundingAnimals(idsNeighbours, anim, fd);

            for (auto it: animals)
                for (auto iD: neighboursIDs)
                    if (it->getID() == iD)
                        anim.push_back(it);


            for (auto it: food)
                for (auto iD: neighboursIDs)
                    if (it->getID() == iD)
                        fd.push_back(it);

            //DEBUG
            cout << endl << "Animais a sua volta: ";
            for(auto at: anim) {
                cout << at->letter() << " || " ;
            }
            cout << endl;

            MOVE:
                FALSE: Avoids direction with a dangerous specie
                TRUE: there is not any animal to run from in this direction

            bool add = true;
            //if(an->moveAN(anim) && an->moveFD(fd))
            if (an->move(anim, fd)) {
                anim = an->moveAN(anim);
                fd = an->moveFD(fd);

                cout << endl << "Depois do move animal, animais: ";
                for(auto at: anim) {
                    cout << at->letter() << " || " ;
                }
                cout << endl;
                //Keeps information from the species that can be chased and distance
                for (auto it: anim) {

                    for (auto at: chaseAN)
                        if (at->getID() == it->getID())
                            add = false;

                    if (add) {
                        cout << "adicionei um lado " << dirc;
                        if (dirc == 0) specieDir.insert({it->getID(), "rt"});
                        if (dirc == 1) specieDir.insert({it->getID(), "lt"});
                        if (dirc == 2) specieDir.insert({it->getID(), "up"});
                        if (dirc == 3) specieDir.insert({it->getID(), "dn"});

                        distan.insert({it->getID(), Distance(an->getID(), it->getID())});
                        chaseAN.push_back(it);
                    }

                    add = true;
                }
                for (auto it: fd) {

                    for (auto at: chaseFD)
                        if (at->getID() == it->getID())
                            add = false;

                    if (add) {
                        if (dirc == 0) specieDir.insert({it->getID(), "rt"});
                        if (dirc == 1) specieDir.insert({it->getID(), "lt"});
                        if (dirc == 2) specieDir.insert({it->getID(), "up"});
                        if (dirc == 3) specieDir.insert({it->getID(), "dn"});

                        distan.insert({it->getID(), Distance(an->getID(), it->getID())});
                        chaseFD.push_back(it);

                    }

                    add = true;

                }
            }
        }
    }


    //DEBUG

    int chaseID = an->chase(chaseAN, chaseFD, distan);
    cout << "Animal elegido" << chaseID << endl;

    if (!checKill(an, chaseID, distan)) {

        for (auto at = specieDir.begin(); at != specieDir.end(); at++)
            if (at->first == chaseID) return at->second;
    }


    return "";
}
*/

//Moves to the position of the chased specie case it is close enough. If the chased specie is food kills it


vector<int> Reserve::findNeighboursIDs(Animal * an)
{
    vector<int> neighboursIDs;

    for(auto it : animals){

        if(an->getID() != it->getID()){

            if(Distance(an->getID(), it->getID()) < an->getvision())
                neighboursIDs.push_back(it->getID());
        }
    }

    for(auto it : food){

        if(an->getID() != it->getID()){

            if(Distance(an->getID(), it->getID()) < an->getvision())
                neighboursIDs.push_back(it->getID());
        }
    }

    return neighboursIDs;
}
vector<string> Reserve::getSpecies(vector<int> neighboursIDs)
{
    vector<string > spec;

    for(auto it: animals)
        for(auto at : neighboursIDs)
            if(it->getID() == at)
                spec.push_back(it->letter());

    for(auto it: food)
        for(auto at : neighboursIDs)
            if(it->getID() == at)
                spec.push_back(it->getLetter());


    return spec;
}


//moves an animal to a certain direction
void Reserve::move(Animal * an)
{
    vector<int> neighboursIDs;
    vector<string> spec;
    bool random = false;
    string direction;
    vector<int> newPos = getPosition(an->getID());
    int randing;

    neighboursIDs = findNeighboursIDs(an);//, anim, fd, spec);
    if(neighboursIDs.empty()){
        random = true;
    }
    else{
        spec = getSpecies(neighboursIDs);


        if (!an->SpeciesDictatingMovem(spec))
            random = true;
        else{
            randing = chooseDirection(an, neighboursIDs);
        }
    }



    if(random || randing == 4){
        //cout << "Foi feito de forma random" << endl;

        default_random_engine defEngine(time(nullptr));
        uniform_int_distribution<int> randn(0,3);
        randing = randn(defEngine);
    }


    if(direction == "rt" || randing == 0){
        newPos[1] += an->getsteps() ;
        if(newPos[1] > COLUMNS ) newPos[1] = 1;
    }
    else
        if(direction == "lt" || randing == 1) {
            newPos[1] -= an->getsteps();
            if(newPos[1] < 1 ) newPos[1] = COLUMNS;
        }
        else
            if(direction == "up" || randing == 2) {
                newPos[0] -= an->getsteps();
                if(newPos[0] < 1 ) newPos[0] = ROWS;
            }
            else if(direction == "dn" || randing == 3){
                newPos[0] += an->getsteps();
                if(newPos[0] > ROWS ) newPos[0] = 1;
            }
            else if(randing == -1)
                return;
    //cout << an->getID() << an->letter() << "-> " << newPos[0] << newPos[1] << endl;


    setPosition(an->getID(), newPos);
}

void Reserve::dead(Animal * an)
{
    if(an->getdead()){
        vector<int> pos = getPosition(an->getID());
        if(an->letter() != "C") {//Case it is a rabbit nothing gets done
            ID++;
            AddinMap(pos[0], pos[1] + 1);

            vector<int> add = an->getDeadBody();
            this->food.push_back(new Body(ID, add[0], add[1]));
        }

        EraseinReserve(an->getID());
    }
}
void Reserve::dead(Food * an)
{
    if(an->getdead()){
        EraseinReserve(an->getID());
    }
}
Animal* Reserve::chooseAnimal(string spec, int id)
{
    if(spec == "C")
        return new Rabbit(id);
    if(spec == "O")
        return new Sheep(id);
    if(spec == "L")
        return new Wolf(id);
    if(spec == "G")
        return new Kangaroo(id);
    if(spec == "M")
        return new Giraffe(id);

    return nullptr;
}
Food* Reserve::chooseFood(string spec, int id){
    if(spec == "r")
        return new Grass(id);
    if(spec == "t")
        return new Carrot(id);
    if(spec == "p")
        return new Body(id,0,0);
    if(spec == "b")
        return new Meet(id);
    if(spec == "a")
        return new Mistery(id);

    return nullptr;
}

void Reserve::addChild(Animal *an)
{
    int distance = 0;
    vector<int> pos = getPosition(an->getID());


    if(an->child(&distance)){
        distance = distance / 2;

        if(!AddinReserve(an->letter(), pos[0] + distance, pos[1] + distance))
            if(!AddinReserve(an->letter(), pos[0] - distance, pos[1] - distance))
                if(!AddinReserve(an->letter(), pos[0] + distance, pos[1] - distance))
                    if(!AddinReserve(an->letter(), pos[0] - distance, pos[1] + distance)){}

        an->child(animals.back());
    }
}
void Reserve::addChild(Food* fd)
{
    if(fd->getLetter() == "r"){
        if(fd->getage() == 15){
            vector<int> pos = getPosition(fd->getID());

            default_random_engine defEngine(time(nullptr));
            uniform_int_distribution<int> randn(4,8);
            int n = randn(defEngine);
            n = n / 2;

            if(!AddinReserve(fd->getLetter(), pos[0] + n, pos[1] + n))
                if(!AddinReserve(fd->getLetter(), pos[0] - n, pos[1] - n))
                    if(!AddinReserve(fd->getLetter(), pos[0] + n, pos[1] - n))
                        if(!AddinReserve(fd->getLetter(), pos[0] - n, pos[1] + n)){}
        }

    }
}
void Reserve::dayPassed()
{
    for(int i = 0; i < animals.size(); i++){
        animals[i]->dayPassed();
        move(animals[i]);
    }

    for(int i = 0; i < animals.size(); i++) { dead(animals[i]); addChild(animals[i]); }
    for(int i = 0; i < food.size(); i++){food[i]->dayPassed(); dead(food[i]); addChild(food[i]);}

}