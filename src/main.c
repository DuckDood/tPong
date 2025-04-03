#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "border.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#ifndef D_SPEED
#define D_SPEED 0.5
#endif

#ifndef M_SPEED
#define M_SPEED 2
#endif

#ifndef A_SPEED
#define A_SPEED 0.3
#endif

#ifndef A_LENIENCY
#define A_LENIENCY 3
#endif

#ifndef TICK_LEN
#define TICK_LEN 20
#endif

int main() {
	srand(time(NULL));
	initscr();
	curs_set(false);
	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	int x, y;
	int batY1 = 0;
	int batY2 = 0;
	int ballX = 0;
	float fBallY = 0;
	float fBatY2 = 0;
	int ballY = 0;
	int input;
	int dir = -1; 
	float dirY = D_SPEED;
	int score1 = 0;
	int score2 = 0;
	int tDown1 = 0;
	int tDown2 = 0;
	getmaxyx(stdscr, y, x);
	while(1) {
	clear();
	// ball
	for(int i = 0; i < 6; i++) {	
	mvprintw(y/2-1+i+ballY, x/2+ballX, "%c%c%c%c%c", ball[0+i*5], ball[1+i*5], ball[2+i*5], ball[3+i*5], ball[4+i*5]);
	}
	// bat 1
	for(int i = 0; i < 14; i++) {	
	mvprintw(y/2-6+i + batY1, x/2+1 - 80, "%c%c%c", bat[0+i*3], bat[1+i*3], bat[2+i*3]);
	}
	// bat 2
	for(int i = 0; i < 14; i++) {	
	mvprintw(y/2-6+i + batY2, x/2+1 + 80, "%c%c%c", bat[0+i*3], bat[1+i*3], bat[2+i*3]);
	}
	// debug stuff
//	mvprintw(0, 0, "%c", mvinch(y/2 + ballY, x/2+1 - 80));
//	mvprintw(1, 0, "%c", mvinch(y/2 + ballY+3, x/2+1 - 80));
	mvprintw(0, 0, "%d", score1);
	mvprintw(0, x-1, "%d", score2);
	refresh();
	move(1,1);
	input = getch();
	ballX += dir;
	fBallY += dirY;
	ballY = fBallY;
	#ifdef SMART_AI
	if(batY2 > ballY-A_LENIENCY) {
			fBatY2-=A_SPEED;
	}	
	if(batY2 < ballY+A_LENIENCY) {
			fBatY2+=A_SPEED;
	}
	batY2 = fBatY2;
	#endif
	#ifndef SMART_AI
	batY2 = ballY* 0.5;
	#endif

	if(y/2+ballY < batY2) {
		batY2++;
	}

	if (ballX < -76 && ( mvinch(y/2 + ballY, x/2+1 - 80) ==(int)'|' ||  mvinch(y/2 + ballY+3, x/2+1 - 80) == (int)'|')) {
		dir = 1;
		if(input == (int)'s') {
		dirY = 0.1;
		}
		dirY += (float)rand()/2147483648 -1;
	} else if(ballX < -80) {
		ballX = 0;
		score2++;
		dirY = D_SPEED;
		dir = -1;
		clear();
	}
	if (ballX > 76 && ( mvinch(y/2 + ballY, x/2+1 + 80) ==(int)'|' ||  mvinch(y/2 + ballY+3, x/2+1 + 80) == (int)'|')) {
		dir = -1;
	
	} else if (ballX > 80) {
		ballX = 0;
		score1++;
		dir = -1;
		dirY = D_SPEED;
		clear();
	}
	if (input == (int)'s') {
		batY1 += M_SPEED;
	}
	if (input == (int)'w') {
		batY1 -= M_SPEED;
	}
	if (y/2 + ballY > y-3) {
		dirY *= -1;
	}
	if (y/2 + ballY < 0) {
		dirY *= -1;
	}
	//ballX = MAX(ballX, -x/2);
	usleep(TICK_LEN*1000);
	}
	endwin();
}
