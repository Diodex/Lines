#include "game.h"


Game::Game(QWidget *pwgt) : QGLWidget(pwgt){
	setGeometry(50,50,500,500);
	srand(time(NULL));
	activepoint = NULL;
	gamescore = 0;

	for(int i=0; i<10; ++i)
		for (int j=0; j<10; ++j) arrayofpoints[i][j] = NULL;

	desk = new Desk;

	updatetimer = new QTimer(this);
	connect(updatetimer, SIGNAL(timeout()), this, SLOT(updateogl()));
	updatetimer->start(20);

	addpoint(); addpoint(); addpoint();
}


Game::~Game(void){

}


void Game::initializeGL(){
	qglClearColor(Qt::gray);
	glEnable(GL_POINT_SMOOTH);
	glInitNames();
	glPushName(0);
}

void Game::resizeGL(int nWidth, int nHeight){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,500,500);
	glOrtho(0,500,0,500,-1,1);

}

void Game::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	desk->paint();

	for(int i=0; i<10; ++i)
		for (int j=0; j<10; ++j) 
			if(arrayofpoints[i][j] != NULL) arrayofpoints[i][j]->paint();
}

void Game::addpoint(){
	if(GamePoint::countofpoint < 100){

		int pos = rand()%(100-GamePoint::countofpoint);
		for(int i=0; i<10; ++i)
			for (int j=0; j<10; ++j) 
				if(arrayofpoints[i][j] == NULL){
					if(!pos) arrayofpoints[i][j] = new GamePoint(25+50*i, 25 + 50*j);
					pos--;
				}

	}
}

int Game::delobjects(){
	int numberofdelobjects = 0;
	for(int i=0; i<10; ++i)
		for (int j=0; j<10; ++j) 
			if(arrayofpoints[i][j] != NULL)
				if(arrayofpoints[i][j]->del){
					delete arrayofpoints[i][j];
					arrayofpoints[i][j] = NULL;
					numberofdelobjects++;
				}
	gamescore += numberofdelobjects;
	return numberofdelobjects;
}

int Game::checkarray(){
	for(int i=0;i<10;++i)
		for(int j=0;j<6;++j){
			
			if((arrayofpoints[i][j])&&(arrayofpoints[i][j+1])&&(arrayofpoints[i][j+2])&&(arrayofpoints[i][j+3])&&(arrayofpoints[i][j+4])){
				int clearcolor = arrayofpoints[i][j]->color;
				if((arrayofpoints[i][j+1]->color == clearcolor)&&(arrayofpoints[i][j+2]->color == clearcolor)&&(arrayofpoints[i][j+3]->color == clearcolor)&&(arrayofpoints[i][j+4]->color == clearcolor))
					arrayofpoints[i][j]->del = arrayofpoints[i][j+1]->del = arrayofpoints[i][j+2]->del = arrayofpoints[i][j+3]->del = arrayofpoints[i][j+4]->del = 1;
			}

			if((arrayofpoints[j][i])&&(arrayofpoints[j+1][i])&&(arrayofpoints[j+2][i])&&(arrayofpoints[j+3][i])&&(arrayofpoints[j+4][i])){
				int clearcolor = arrayofpoints[j][i]->color;
				if((arrayofpoints[j+1][i]->color == clearcolor)&&(arrayofpoints[j+2][i]->color == clearcolor)&&(arrayofpoints[j+3][i]->color == clearcolor)&&(arrayofpoints[j+4][i]->color == clearcolor))
					arrayofpoints[j][i]->del = arrayofpoints[j+1][i]->del = arrayofpoints[j+2][i]->del = arrayofpoints[j+3][i]->del = arrayofpoints[j+4][i]->del = 1;
			}
		}

	
	if(GamePoint::countofpoint == 100) EndGame();
	return delobjects();
}

void Game::mousePressEvent(QMouseEvent *pe){
	if(pe->buttons() == 1){
		int x = pe->x()/50;
		int y = (500-pe->y())/50;
		if(arrayofpoints[x][y] != NULL){
			if(activepoint != NULL) activepoint->active = 0;
			activepoint=arrayofpoints[x][y];
			activepoint->active = 1;
		} else {
			if(activepoint != NULL){
			/////////////////////////////////////////	
				if(movepoint(activepoint->x/50,activepoint->y/50,x,y)){
					if(!checkarray()){
						emit scoreChanged();
						addpoint(); addpoint(); addpoint();
					}
					checkarray();
					emit scoreChanged();
				}
			/////////////////////////////////////////
			}
		}

	}

	if(pe->buttons() == 2){
		if(activepoint){
			activepoint->active = 0;
			activepoint = NULL;
		}
	}
}


int Game::movepoint(int xs, int ys, int xk, int yk){
	int arr[10][10];
	
	for(int i=0; i<10; ++i)
		for(int j=0; j<10; ++j)
			if(arrayofpoints[i][j]!=NULL) arr[i][j]=-1; else arr[i][j]=0; 
	arr[xk][yk]=1;
	arr[xs][ys]=0;

	for(int k=1; k<=100; ++k)
		for(int i=0; i<10; ++i)
			for(int j=0; j<10; ++j)
				if(arr[i][j]==k){
					if(i>0) if(!arr[i-1][j]) arr[i-1][j]=k+1;
					if(i<9) if(!arr[i+1][j]) arr[i+1][j]=k+1;
					if(j>0) if(!arr[i][j-1]) arr[i][j-1]=k+1;
					if(j<9) if(!arr[i][j+1]) arr[i][j+1]=k+1;
				}
	

	if(arr[xs][ys]){
		int k = arr[xs][ys], xt=xs, yt=ys;

		while(k>1){
			if(xs>0) if(arr[xs-1][ys]==(k-1)){
				for(int i=0; i<10; ++i){
					activepoint->moveleft();
					updateGL();
				}
				k--; xs--;
			}

			if(xs<9) if(arr[xs+1][ys]==(k-1)){
				for(int i=0; i<10; ++i){
					activepoint->moveright();
					updateGL();
				}
				k--; xs++;
			}

			if(ys>0) if(arr[xs][ys-1]==(k-1)){
				for(int i=0; i<10; ++i){
					activepoint->movedown();
					updateGL();
				}
				k--; ys--;
			}

			if(ys<9) if(arr[xs][ys+1]==(k-1)){
				for(int i=0; i<10; ++i){
					activepoint->moveup();
					updateGL();
				}
				k--; ys++;
			}
		
		}

		arrayofpoints[xk][yk] = arrayofpoints[xt][yt];
		arrayofpoints[xt][yt] = NULL;
		activepoint->active = 0;
		activepoint = NULL;
		return 1;
	}
	
	activepoint->active = 0;
	activepoint = NULL;
	return 0;
}

void Game::EndGame(){
	updatetimer->stop();
	emit YOU_DIED();
}

void Game::NewGame(){
	activepoint = NULL;
	for(int i=0; i<10; ++i)
		for(int j=0; j<10; ++j)
			if(arrayofpoints[i][j] != NULL)arrayofpoints[i][j]->del = 1;
	delobjects();
	addpoint();addpoint();addpoint();
	gamescore = 0;
	updatetimer->start(20);
	this->show();	
}

void Game::updateogl(){
	updateGL();
}