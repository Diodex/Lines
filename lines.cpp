#include "lines.h"

Lines::Lines(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags){

	setGeometry(100,100,800,600);

	g = new Game(this);
	connect(g, SIGNAL(YOU_DIED()), this, SLOT(EndGame()));
	connect(g, SIGNAL(scoreChanged()), this, SLOT(SetScore()));
	g->show();	

	s = new Scores(this);
	s->hide();

	newgamebutton = new QPushButton(this);
	connect(newgamebutton, SIGNAL(clicked()), this, SLOT(NewGame()));
	newgamebutton->setGeometry(600,50,150,50);
	newgamebutton->setText("New Game");
	newgamebutton->show();

	scorebutton = new QPushButton(this);
	connect(scorebutton, SIGNAL(clicked()), this, SLOT(ShowScores()));
	scorebutton->setCheckable(true);
	scorebutton->setGeometry(600,125,150,50);
	scorebutton->setText("Score");

	scorelbl = new QLabel(this);
	scorelbl->setGeometry(600,200,150,50);
	scorelbl->setText("<H1><CENTER>0</CENTER></H1>");

	strcpy(playername,"Name");

	playernameedit = new QLineEdit(this);
	playernameedit->setGeometry(600,250,150,50);
	playernameedit->setAlignment(Qt::AlignHCenter);
	playernameedit->setFont(QFont("Times", 15, QFont::Bold));
	playernameedit->setText("Name");
	connect(playernameedit, SIGNAL(returnPressed()), this, SLOT(SetName()));
	
}

Lines::~Lines(){


}


void Lines::EndGame(){
	g->hide();
	s->addscore(playername, g->gamescore);
	s->updatearrayofscore();
	scorebutton->setChecked(true);
	s->show();
}

void Lines::NewGame(){
	s->hide();
	scorebutton->setChecked(false);
	g->NewGame();
	g->show();

	scorelbl->setText("<H1><CENTER>0</CENTER></H1>");
}

void Lines::ShowScores(){
	if(scorebutton->isChecked()){
		g->hide();
		s->updatearrayofscore();
		s->show();
	} else {
		s->hide();
		g->show();
	}
}

void Lines::SetScore(){
	QString scorestring;
	scorestring = "";
	scorestring += ("<H1><CENTER>" + QString::number(g->gamescore) + "</CENTER></H1>");
	scorelbl->setText(scorestring);
}

void Lines::SetName(){
	strcpy(playername, playernameedit->text().toAscii().data());	
}