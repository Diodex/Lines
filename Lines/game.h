#ifndef GAME_H
#define GAME_H

#include <QGLWidget>
#include <QTimer>
#include <stdlib.h>
#include <time.h>
#include "PaintObject.h"


class Game : public QGLWidget{
Q_OBJECT

public:
	Game(QWidget *pwgt = 0);
	~Game(void);
	int gamescore;
	QTimer *updatetimer;
	void NewGame();

protected:
	virtual void initializeGL();         
	virtual void resizeGL(int nWidth, int nHeight);  
	virtual void paintGL();     
	virtual void mousePressEvent(QMouseEvent *pe);

private:
	int movepoint(int xs, int ys, int xk, int yk);
	void EndGame();
	void addpoint();
	int delobjects();
	int checkarray();
	GamePoint *arrayofpoints[10][10], *activepoint;
	PaintObject* desk;

signals:
	void YOU_DIED();
	void scoreChanged();

private slots:
	void updateogl();



};


#endif //GAME_H
