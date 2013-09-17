#include "PaintObject.h"

PaintObject::~PaintObject(){

}

void Desk::paint(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0,0,0);

	for(int i=0; i<9; ++i){
		glBegin(GL_LINES);
			glVertex2f(50*i+50,0);
			glVertex2f(50*i+50,500);
		glEnd();
	}

	for(int i=0; i<9; ++i){
		glBegin(GL_LINES);
			glVertex2f(0,50*i+50);
			glVertex2f(500,50*i+50);
		glEnd();
	}

}


int GamePoint::countofpoint = 0;

GamePoint::GamePoint(int x, int y) : PaintObject(){
	countofpoint++;
	del = 0;
	id = countofpoint;
	color = rand()%7;
	active = 0;
	this->x = x;
	this->y = y;
}

GamePoint::GamePoint(int x, int y, int color) : PaintObject(){
	countofpoint++;
	del = 0;
	id = countofpoint;
	this->color = color;
	active = 0;
	this->x = x;
	this->y = y;
}


GamePoint::~GamePoint(){
	countofpoint--;
}

void GamePoint::paint(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x,y,0);

	if(active){
		glPointSize(32);
		glColor3f(0,0,0);
		glBegin(GL_POINTS);
			glVertex2f(0,0);
		glEnd();
	}
	
	glPointSize(26);
	switch(color){
		case 0: {glColor3f(0,0,1); break;}
		case 1: {glColor3f(0,1,0); break;}
		case 2: {glColor3f(0,1,1); break;}
		case 3: {glColor3f(1,0,0); break;}
		case 4: {glColor3f(1,0,1); break;}
		case 5: {glColor3f(1,1,0); break;}
		case 6: {glColor3f(1,1,1); break;}
		default: glColor3f(0,0,0);
	}

	glLoadName(id);
	glBegin(GL_POINTS);
		glVertex2f(0,0);
	glEnd();
}

void GamePoint::moveup(){
	y+=5;
	Sleep(20);
}

void GamePoint::movedown(){
	y-=5;
	Sleep(20);
}

void GamePoint::moveleft(){
	x-=5;
	Sleep(20);
}

void GamePoint::moveright(){
	x+=5;
	Sleep(20);
}