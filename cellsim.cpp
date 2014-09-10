
//g++ -o cellsim cellsim.cpp -lX11

//std libs
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

//gui libs
#include <X11/Xlib.h> 
#include <assert.h>   
#include <unistd.h>   
#include <X11/Xutil.h>

//programmer defined, assumes pwd
#include "classes.h"


using namespace std;

void populatefield(Environ* field);
int getrandidx();
int getrandact();
int getranddirection(int x, int y);
int isedge(int x, int y);
void drawfield(Display *dpy, Window w, GC gc, Environ* field);
void wait();
void clearfield(Environ* field);
void step(Environ* field);
void doaction(int x, int y, int ID, Environ* field);

	
	
//global colors
int blackColor, whiteColor, greyColor;
//Environ field (0);


int main(int argc, char *argv[]){
	
	//init srand
	srand((unsigned)time(0)); 
	
	
	//X11 init
	Environ *field = new Environ(0); //create field with constructor, constructor gets variable input
	Display *dpy;
	Window w;
	GC gc;
	//colors
	blackColor = 0;//BlackPixel(dpy, DefaultScreen(dpy));
	whiteColor = 16777215;
	greyColor = (16777215/3);
	
	
	//clear the field from previous memory. 
	clearfield(field);
	//populate the field array in environment
	populatefield(field);
	
	
	int ticks = field->getticks();
	
	//create window with initial field

	dpy = XOpenDisplay(NULL);
	assert(dpy);

	w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
				     500, 500, 0, blackColor, greyColor );
	XSelectInput(dpy, w, StructureNotifyMask);
	XMapWindow(dpy, w);
	gc = XCreateGC(dpy, w, 0, NULL);
	XSetForeground(dpy, gc, whiteColor);
	for(;;){
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
        }
        
	
	
	//loop and update window until number of ticks is reached
	while(ticks > 0){
	//change values and send update event to X
	step(field);
	drawfield(dpy, w, gc, field);
	XFlush(dpy);//update display
	ticks--;
	}

wait();
//deallocate field
delete field;
return 0; //exit main
}









void populatefield(Environ* field){
//place media and food randomly until percentage of tiles is equal to given percentage
//four inital cells are placed on field in random indices, two of either type.
int x, y; 
printf("seed values:\n");
	for(int i = 0; i < 4; i++){
	
	x = getrandidx();
	y = getrandidx();
	printf("%i, %i\n", x, y);
		if(i == 0 || i == 1){
		//create earth cell
		//printf("cell@ %i, %i \n", x, y);
		field->fieldarray[x][y].cellID = 1;
		
		}else if(i == 2 || i== 3){
		//create alien cell
		//printf("cell@ %i, %i \n", x, y);
		field->fieldarray[x][y].cellID = 2;
		}

	}
	
//place media and food	

int goalpctfood = field->pctfood;
int goalpctmedium = field->pctmedium;

int currpctfood, currpctmedium, totalfood, totalmedium;

int foodinc = ((250*250)*goalpctfood)/100;
int mediuminc = ((250*250)*goalpctmedium)/100;

	
	for(int i = 0; i < foodinc; i++){
	x = getrandidx();
	y = getrandidx();
	
	field->fieldarray[x][y].foodAMT = 1;
	
	}
	
	for(int i = 0; i < mediuminc; i++){
	x = getrandidx();
	y = getrandidx();
	
	field->fieldarray[x][y].mediaAMT = 1;
	
	}


}






int getrandidx(){
	int lrand = (rand()%(250));//rand()%n we generate a number from 0 to n-1. so from 0 to 249
return lrand;
}




int getrandact(){
	int lrand = (rand()%(4)); //rand range from 0 to 3; 
return lrand;
}




int getranddirection(int x, int y){
int lrand = 0;	
	if(isedge(x, y) == 0){
	lrand = (rand()%(8)); //rand range from 0 to 7; 
	}else{
	lrand = -1;
	}
return lrand;
}





int isedge(int x, int y){
int lret = 0;

	if(x == 1 || x == 249|| y == 1 || y == 249){
	lret = 1;
	}

return lret;
}







void drawfield(Display* dpy, Window w, GC gc, Environ* field){
//parses fieldarray, if finds cell, invokes XFillRectangle and XSetForeground of appropriate color.
for(int y = 0; y<250;y++){
//parse y
	for(int x = 0; x<250; x++){
	//parse x
		if(field->fieldarray[x][y].cellID == 1){
		//draw earth cell
		//printf("bob: x:%i y:%i\n",x, y);
		XSetForeground(dpy, gc, blackColor);
		XFillRectangle(dpy, w, gc, (x*2), (y*2), 2, 2);
		//XFlush(dpy);
	
		}else if(field->fieldarray[x][y].cellID == 2){
		//draw alien cell
		XSetForeground(dpy, gc, whiteColor);
		XFillRectangle(dpy, w, gc,(x*2), (y*2),  2, 2);
		//XFlush(dpy);
		}else{//paint the index grey
		XSetForeground(dpy, gc, greyColor);
		XFillRectangle(dpy, w, gc,(x*2), (y*2),  2, 2);
		//XFlush(dpy);
		
		}
		
	
	
	
	}

}

//sleep(1);
//wait();
}

	

void wait(){
	char dummy;
	cout<<"press a key to quit"<<endl<<endl;
	cin >> dummy;
	//cin.ignore('q');
	
}

void clearfield(Environ* field){
	for(int y = 0; y < 250; y++){
		for(int x = 0; x<250; x++){
			field->fieldarray[x][y].cellID = 0;
		}
	}

}


void step(Environ* field){

	for(int y = 0; y < 250; y++){


		for(int x = 0; x < 250; x++){
			if(field->fieldarray[x][y].cellID == 1 ){
			doaction(x,y, 1, field);
			
			}else if(field->fieldarray[x][y].cellID == 2){
			
			doaction(x,y,2, field);
			}
	
	
		}


	}







}

void doaction(int x, int y, int ID, Environ* field){

int action = getrandact();

switch(action){
case 0: field->move(x, y, getranddirection(x, y));
break;
case 1: field->consume(x, y, getranddirection(x, y));
break;
case 2:field->move(x, y, getranddirection(x, y));
break;
case 3: field->consume(x, y, getranddirection(x, y));
break;

}


}










