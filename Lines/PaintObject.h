#ifndef PAINTOBJECT_H
#define PAINTOBJECT_H

#include <QtOpenGL>
#include <iostream>

class PaintObject abstract{
public:
	virtual void paint() abstract;
	virtual ~PaintObject();
};


class Desk : public PaintObject{
public:
	void paint();
};


class GamePoint : public PaintObject{
private:	
	int id;

public:
	static int countofpoint;
	GamePoint(int x, int y);
	GamePoint(int x, int y, int color);
	~GamePoint();
	int active,del,color,x,y;
	void paint();
	void moveup();
	void moveleft();
	void moveright();
	void movedown();
};

#endif //PAINTOBJECT_H