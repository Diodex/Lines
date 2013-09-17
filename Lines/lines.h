#ifndef LINES_H
#define LINES_H

#include <QtGui/QMainWindow>
#include <QtGui>
#include "game.h"
#include "scores.h"

class Lines : public QMainWindow
{
	Q_OBJECT

public:
	Lines(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Lines();
	char playername[50];

private:
	//Widgets
	Game *g;
	Scores *s;

	//Buttons
	QPushButton *newgamebutton, *scorebutton;

	QLabel *scorelbl;
	QLineEdit *playernameedit;

public slots:
	void EndGame();
	void NewGame();
	void ShowScores();
	void SetScore();
	void SetName();
};

#endif // LINES_H
