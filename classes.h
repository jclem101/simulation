#include <iostream>
using namespace std;
class Environ{ //each environ is width by height units, each unit can either be a food unit, media unit or both, only one cell to a unit. 

public:

	struct subenv{
	int celltype; //cell id number in current idx position, 
	int mediaAMT; //1 if traversible, 0 if not traversible
	int foodAMT; //1 if food, 0 for no food
	int cellID; //0 for no cell, 1 for earth cell, 2 for alien cell.
	};

	int pctfood, pctmedium;
	const static int width = 250, height = 250; //62500 idx
	unsigned long long int ticks;
	subenv fieldarray[width][height];
	//specifies contructor method
	Environ(int);
	
	//accessors
	int getticks(){return ticks;}
	int getwidth(){return width;}
	int getheight(){return height;}
	int getpctfood(){return pctfood;}
	int getpctmedium(){return pctmedium;}
	//subenv getidx(int x, int y){return fieldarray[x][y];}
	
	
	//modifiers/actions
	void move(int x, int y, int dir){
	
	int ltype = fieldarray[x][y].cellID;
		if (dir >= 0){
		
			switch(dir){
			case 0:
				if(fieldarray[x-1][y-1].cellID != 1 && fieldarray[x-1][y-1].cellID != 2 && fieldarray[x-1][y-1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x-1][y-1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 1:
				if(fieldarray[x][y-1].cellID != 1 && fieldarray[x][y-1].cellID != 2 && fieldarray[x][y-1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x][y-1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 2:
				if(fieldarray[x+1][y-1].cellID != 1 && fieldarray[x+1][y-1].cellID != 2 && fieldarray[x+1][y-1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y-1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 3:
				if(fieldarray[x+1][y].cellID != 1 && fieldarray[x+1][y].cellID != 2 && fieldarray[x+1][y].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 4:
				if(fieldarray[x+1][y+1].cellID != 1 && fieldarray[x+1][y+1].cellID != 2 && fieldarray[x+1][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y+1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 5:
				if(fieldarray[x][y+1].cellID != 1 && fieldarray[x][y+1].cellID != 2 && fieldarray[x][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x][y+1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 6:
				if(fieldarray[x-1][y+1].cellID != 1 && fieldarray[x-1][y+1].cellID != 2 && fieldarray[x-1][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x-1][y+1].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			case 7: 
				if(fieldarray[x-1][y].cellID != 1 && fieldarray[x-1][y].cellID != 2 && fieldarray[x-1][y].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x-1][y].cellID = ltype;
					fieldarray[x][y].cellID = 0;
				}
			break;
			
			
			
			}
			
		}
	
	
	}
	
	
	void consume(int x, int y, int dir){
	
	int ltype = fieldarray[x][y].cellID;
		if (dir >= 0){
		
			switch(dir){
			case 0:
				if(fieldarray[x-1][y-1].cellID !=0 || fieldarray[x-1][y-1].foodAMT ==1 && fieldarray[x-1][y-1].mediaAMT == 1){
				//if direction is occupied or there is food and there is media in location
					fieldarray[x-1][y-1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 1:
				if(fieldarray[x][y-1].cellID != 0 || fieldarray[x][y-1].foodAMT ==1 && fieldarray[x][y-1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x][y-1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 2:
				if(fieldarray[x+1][y-1].cellID != 0 ||fieldarray[x+1][y-1].foodAMT ==1 && fieldarray[x+1][y-1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y-1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 3:
				if(fieldarray[x+1][y].cellID != 0 ||fieldarray[x+1][y].foodAMT ==1 && fieldarray[x+1][y].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 4:
				if(fieldarray[x+1][y+1].cellID != 0|| fieldarray[x+1][y+1].foodAMT ==1 && fieldarray[x+1][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x+1][y+1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 5:
				if(fieldarray[x][y+1].cellID != 0|| fieldarray[x][y+1].foodAMT ==1&& fieldarray[x][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x][y+1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 6:
				if(fieldarray[x-1][y+1].cellID != 0 ||fieldarray[x-1][y+1].foodAMT ==1 && fieldarray[x-1][y+1].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x-1][y+1].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			case 7: 
				if(fieldarray[x-1][y].cellID != 0 ||fieldarray[x-1][y].foodAMT ==1 && fieldarray[x-1][y].mediaAMT == 1){
				//if direction is unoccupied and there is media in location
					fieldarray[x-1][y].cellID = ltype;
					//fieldarray[x][y].cellID = 0;
				}
			break;
			
			
			
			}
			
		}
	
	
	}
	void divide(){
	
	}
	void mutate(){
	
	}
	
	
};

Environ :: Environ(int dummy){//constructor gets input
//enter game variables


cout << "enter number of ticks(1-1,000): " ;
cin >> ticks;



cout << "enter percent of food tiles of game field (0-100): " ;
cin >> pctfood;


cout << "enter percent of traversible medium in field (0-100): " ;
cin >> pctmedium;


}

/*
class cell{

public: //public members
	//stats
	int currentEnergy, mitosisStage, telomereLength;
	int coorX, coorY;
	int mutationProb;
	int cellid;

	//public virtual methods
	virtual void move() = 0; //0 by convention

	virtual void consume() = 0;

	virtual void divide() = 0;
	
	virtual void mutate() = 0;
};

class earthcell : public cell{//inherits from base class cell
//earth cells begin with more energy but less mutationprob

};

class aliencell : public cell{ 
//alien cells have less energy but have more mutationprob


};

*/
