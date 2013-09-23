#ifndef SCORES_H
#define SCORES_H

#include <QWidget>
#include <QtGui>
#include <iostream>
#include <fstream>
#include <algorithm>

struct sc{
	char name[50];
	int value;
};

class Scores :	public QWidget {
Q_OBJECT

private:
	sc arrayofscores[11],initstruct;
	QString formlabel;
	QLabel *lbl;
	std::fstream filescores;

public:
	Scores(QWidget *pwgt = 0);
	~Scores(void);

	static bool cmp(sc a, sc b);
	void updatearrayofscore();
	void addscore(char* name, int value);

};


#endif //SCORES_H