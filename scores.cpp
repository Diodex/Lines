#include "scores.h"


Scores::Scores(QWidget *pwgt) : QWidget(pwgt){
	setGeometry(50,50,500,500);
	
	strcpy(initstruct.name,"Name");
	initstruct.value = 0;
	for(int i=0; i<11; ++i) arrayofscores[i] = initstruct;

	filescores.open("scores.bin", std::ios::binary | std::ios::in | std::ios::out);
	if(filescores.is_open()){
		filescores.read(reinterpret_cast<char*>(&arrayofscores), sizeof(sc)*11);
	} else filescores.write(reinterpret_cast<char*>(&arrayofscores), sizeof(sc)*11);

	filescores.close();

	lbl = new QLabel(this);
	lbl->setGeometry(0,0,500,500);
	updatearrayofscore();
}


Scores::~Scores(void){

}

void Scores::updatearrayofscore(){

	std::sort(arrayofscores, arrayofscores+11, cmp);

	lbl->hide();
	formlabel = "";
	for(int i=0; i<10; ++i)
		formlabel += ("<H1><CENTER>" + QString::number(i+1) + " " + arrayofscores[i].name + " " + QString::number(arrayofscores[i].value) + "</CENTER></H1>");
	lbl->setText(formlabel);
	lbl->show();

	filescores.open("scores.bin", std::ios::binary | std::ios::in | std::ios::out);
	filescores.write(reinterpret_cast<char*>(&arrayofscores), sizeof(sc)*11);
	filescores.close();
}


void Scores::addscore(char* name, int value){
	strcpy(arrayofscores[10].name, name);
	arrayofscores[10].value = value;
}

bool Scores::cmp(sc a, sc b){
	if(a.value > b.value) return true; else return false;
}