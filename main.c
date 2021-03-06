/************************************************************
*C programming Team project(Treasure hunt Game) by Team 7
*https://github.com/trollonion03/Cpre_Tp1
*First build: May. 3rd, 2022
*Latest build:JUN. 14th, 2022
*
*Target: Windows(x86-64)
*Language : C(MSVC, v142)
************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

//Constants
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define MAP_WIDTH 50
#define MAP_HEIGHT 18
#define PY_MIN 3
#define PY_MAX 21
#define PX_MIN 1
#define PX_MAX 50
#define POS_S1 22
#define POS_S2 37
#define POS_S3 52
#define POS_S4 67
#define BLK 0
#define WTE 7
#define YLW 14
#define SC2 2
#define GRE 10
#define RED 12

//Global variables
int32_t map_g[MAP_WIDTH-2][MAP_HEIGHT-2];
uint16_t d_t = 0;
uint32_t g_cnt, g_cnt2;

//functions
void gotoxy(int32_t, int32_t);
void init();
void CngTxtClr(uint16_t);
void CreateTitleScreen();
void Game_Core(int32_t);
void Create_Ground(int16_t, int16_t);
void movekey(int32_t*, int32_t*);
void movemonster(int32_t*, int32_t*);
void sel_lv(int32_t*);
void PrintTextS(uint16_t, uint8_t*);
void Story();
void LoadScreen(uint16_t, int32_t);
void CreateObstacle(int32_t lv);
void StatusPrint(int32_t, int32_t, int32_t, int32_t, float);
void GameOver(int32_t, int32_t*);
void GameClear(int32_t);

int32_t main() {
	/***********************************************
	*Modularize it as much as possible
	*Use this function to import other functions
	***********************************************/
	int32_t gch,g, lv;
	
	init();
	CreateTitleScreen();
	gch = _getch();
	if (gch != 'Q' && gch != 'q') {
		Story();
		g = _getch();
		if (g == 'Q' || g == 'q')
			return 0;
	}
	else
		return 0;
	
	while (1) {
		sel_lv(&lv);
		LoadScreen(SC2, lv);
		Game_Core(lv);
	}
}

void gotoxy(int32_t x, int32_t y) {
	COORD Cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void init() {
	//system("mode con cols=79 lines=23 | title game"); //Display option and windows name - for release
	srand((uint32_t)time(NULL));
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; 
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CngTxtClr(uint16_t clr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void CreateTitleScreen() {
	//TODO: New design required!
	//x : 56, y : 20
		system("cls");
	gotoxy(11, 6);  printf("|?? game.konkuk.ac.kr:23   |");
	gotoxy(59, 6);  printf("??|?? |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|           <???? ???????? ???????? ????????>           |");
	gotoxy(11, 9);  printf("|                      -0439  7??-                      |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                       Loading..                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(68, 22); printf("| Q: exit |");

	gotoxy(22, 12);
	CngTxtClr(YLW);
	PrintTextS(25, "????????????????????????????????????");
	Sleep(200);
	CngTxtClr(WTE);

	gotoxy(28, 14);
	Sleep(100);

	//Print one character per 0.1 second
	//TODO: change "press y key" to "press any key"
	PrintTextS(100, "Press any key to start!");	
}

void LoadScreen(uint16_t sc, int32_t lv) {	
	system("cls");
	switch (sc) {
	case 1:
		gotoxy(26, 7); printf("LOADING...");
		gotoxy(12, 8); printf("-------------------------------------");
		gotoxy(12, 9); printf("|                                   |");
		gotoxy(12, 10); printf("-------------------------------------");
		gotoxy(13, 9);
		PrintTextS(50, "###################################");
		break;
	case 2:
		gotoxy(11, 6);  printf("|?? game.konkuk.ac.kr:23/loading/tips   |");
		gotoxy(59, 6);  printf("??|?? |X|");
		gotoxy(11, 7);  printf("---------------------------------------------------------");
		gotoxy(11, 8);  printf("|                                                       |");
		gotoxy(11, 9);  printf("|                                                       |");
		gotoxy(11, 10); printf("|                                                       |");
		gotoxy(11, 11); printf("|                       Loading..                       |");
		gotoxy(11, 12); printf("|                                                       |");
		gotoxy(11, 13); printf("---------------------------------------------------------");
		
		gotoxy(27, 9); printf("%d?????? ?????? ????????!!", lv);

		gotoxy(22, 12);
		CngTxtClr(YLW);
		PrintTextS(50, "????????????????????????????????????");
		CngTxtClr(WTE);  break; 

	default:
		break;
	}
	Sleep(200);
}


void Story() {

	system("cls");
	gotoxy(64, 6); printf("??|?? |X|");
	gotoxy(6, 6);  printf("|?? game.konkuk.ac.kr:23/Story1   |");
	gotoxy(6, 7);  printf("-------------------------------------------------------------------");
	gotoxy(6, 8);  printf("|                                                                 |");
	gotoxy(6, 9);  printf("|                                                                 |");
	gotoxy(6, 10); printf("|                                                                 |");
	gotoxy(6, 11); printf("|                                                                 |");
	gotoxy(6, 12); printf("|                                                                 |");
	gotoxy(6, 13); printf("|                                                                 |");
	gotoxy(6, 14); printf("|                                                                 |");
	gotoxy(6, 15); printf("|                                                                 |");
	gotoxy(6, 16); printf("|                                                                 |");
	gotoxy(6, 17); printf("|                                                                 |");
	gotoxy(6, 18); printf("-------------------------------------------------------------------");
	
	gotoxy(8, 8);
	PrintTextS(25, "?????? ???????????? ???????? ???????? ?????? ????????");

	gotoxy(8, 10);
	PrintTextS(25, "???? ?????? ?????? ????!");

	gotoxy(8, 12);
	PrintTextS(25, "?????? ???????? ???? ????, ????, ???? ??????");

	gotoxy(8, 14);
	PrintTextS(25, "????, ???????? ???????? ????????..!!");

	gotoxy(8, 16);
	PrintTextS(25, "???? ???????? ???????? ?????????? ???? ??????????!");
	
	gotoxy(8, 17);
	CngTxtClr(RED);
	PrintTextS(25, "???????? ???????? ??????????!!");
	CngTxtClr(WTE);
	
	gotoxy(28, 19); printf("Press any key to start");
}

void sel_lv(int32_t *lv) {
	//TODO: New design needed
	int32_t gch1, y = 22, count = 1;

	system("cls");
	gotoxy(34, 1); printf("==========");
	gotoxy(33, 2); printf("||????????||");
	gotoxy(34, 3); printf("==========");
	gotoxy(64, 6); printf("??|?? |X|");
	gotoxy(6, 6);  printf("|?? game.konkuk.ac.kr:23/sel_lv   |");
	gotoxy(6, 7);  printf("-------------------------------------------------------------------");
	gotoxy(6, 8);  printf("|                                                                 |");
	gotoxy(6, 9);  printf("|                                                                 |");
	gotoxy(6, 10); printf("|     |Stage 1 |     |Stage 2 |     |Stage 3 |     |Stage 4 |     |");
	gotoxy(6, 11); printf("|     |1????   |     |2????   |     |3????   |     |4????   |     |");
	gotoxy(6, 12); printf("|                                                                 |");
	gotoxy(6, 13); printf("|     ?? ????                                                     |");
	gotoxy(6, 14); printf("|     | 1. ?????? ???? : ?????? 100 ??????                        |");
	gotoxy(6, 15); printf("|     | 2. ???? ????   : ???? 100 ???? ????                       |");
	gotoxy(6, 16); printf("|     | 3. ??????(#)?? ?????? @?? ??????????!!                    |");
	gotoxy(6, 17); printf("|     | 4. ?????????? ?????? O ??????!!                           |");
	gotoxy(6, 18); printf("|     | 5. ??????(??????, ??????) $ ?? ?????? ????????!           |");
	gotoxy(6, 19); printf("|                                                                 |");
	gotoxy(6, 20); printf("-------------------------------------------------------------------");
	gotoxy(68, 22); printf("| Q: exit |");

	while (1) {
		CngTxtClr(YLW);
		gotoxy(y, 10);
		printf("??");
		CngTxtClr(WTE);
		gch1 = _getch();
		printf("\b\b  ");
		switch (gch1) {
		case RIGHT:
			count++;
			break;
		case LEFT:
			count--;
			break;
		case 'q':
			exit(0);
			break;
		case 'Q':
			exit(0);
			break;
		default:
			break;
		}

		if (count == 5) {
			count = 1;
		}
		else if (count < 1) {
			count = 4;
		}
		
		switch (count){
		case 1:
			y = POS_S1;
			break;
		case 2:
			y = POS_S2;
			break;
		case 3:
			y = POS_S3;
			break;
		case 4:
			y = POS_S4;
			break;
		default:
			break;
		}

		if (gch1 == '\r') {
			*lv = count;
			break;
		}
	}
}

void Game_Core(int32_t lvs) {
	//TODO: Implementation of core functionality
	//int ground[25][15];
	int32_t px = 0, py = 0, count = 0, count2 = 0, st = 0, mx = 0, my = 0, mx1 = 0, my1 = 0, ms = 0;
	int32_t score, hp, row, col, j, k;

	//timer
	clock_t start = clock();
	float max_time = 0;

	system("cls");
	printf("\n");
	gotoxy(70, 1); printf("??|?? |X|");
	gotoxy(0, 1);
	if (lvs == 5) printf("|?? game.konkuk.ac.kr:23/Hidden_stage   | ??????\n");
	else printf("|?? game.konkuk.ac.kr:23/Stage%d   | %d????\n", lvs, lvs);
	printf("-------------------------------------------------------------------------------\n");
	Create_Ground(MAP_WIDTH, MAP_HEIGHT);
	CreateObstacle(lvs);
	gotoxy(0, 21); printf("| ?????? ????                                                                 |");
	gotoxy(0, 22); printf("|                                                                             |");
	gotoxy(0, 23); printf("-------------------------------------------------------------------------------");
	gotoxy(65, 22); printf("|");
	gotoxy(52, 15); printf("??????");
	gotoxy(52, 16); printf("?? ?? ?? ??");
	gotoxy(52, 18); printf("????");
	gotoxy(52, 19); printf("???????? 100?? ????????");

	px = 1; py = 4;
	mx = 20; my = 12;
	score = 0;

	switch (lvs) {
	case 2:
		hp = 110;
		break;
	case 3:
		hp = 120;
		break;
	case 4:
		hp = 130;
		break;
	default:
		hp = 100;
		break;
	}
	
	//TODO: Add game over & game clear conditions
	while (1) {
		if (count2 == 0)
			px = 1; py = 4; mx = 20, my = 12, count2++;
		clock_t end = clock();
		float time = (float)(end - start) / CLOCKS_PER_SEC;
		max_time = 120 - time;

		StatusPrint(score, hp, st, lvs, max_time);
		movekey(&px, &py);	
		movemonster(&mx, &my);
		map_g[mx-1][my-4] = 10;
		switch (map_g[px - 1][py - 4]) {
		case 1:
			score += 30;
			map_g[px - 1][py - 4] = 0;
			st = 1;
			break;
		case 3:
			score += 10;
			hp -= 10;
			map_g[px - 1][py - 4] = 0;
			st = 3;
			break;
		case 4:
			score += 20;
			hp += 10;
			map_g[px - 1][py - 4] = 0; 
			st = 4;
			break;
		case 5:
			score += 10;
			map_g[px - 1][py - 4] = 0;
			st = 5;
			break;
		case 6:
			hp -= 30;
			map_g[px - 1][py - 4] = 0;
			st = 6;
			break;
		case 7:
			hp -= 20;
			map_g[px - 1][py - 4] = 0;
			st = 7;
			break;
		case 8:
			hp -= 15;
			map_g[px - 1][py - 4] = 0;
			st = 8;
			break;
		case 9:
			hp -= 10;
			map_g[px - 1][py - 4] = 0;
			st = 9;
			break;
		case 10:
			hp -= 100;
			ms = 1;
			break;
		}

		if (score >= 100 && hp > 0) {
			g_cnt = 0;
			g_cnt2 = 0;
			count2 = 0;
			GameClear(lvs);
			Sleep(500);
			break;
		}
		else if (hp < 1 || max_time < 0) {
			g_cnt = 0;
			g_cnt2 = 0;
			count2 = 0;
			d_t++;
			GameOver(d_t, &ms);
			Sleep(500);
			break;
		}

		

		col = sizeof(map_g[0]) / sizeof(int32_t);
		row = sizeof(map_g) / sizeof(map_g[0]);

		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {
				// ?????? ????
				if (map_g[j][k] != 0 && map_g[j][k] != 2 && map_g[j][k] != 27 && map_g[j][k] != 10) {
					if (lvs != 5) {
						gotoxy(j + 1, k + 4);
						printf("@");
					}
				}
				else if (map_g[j][k] == 2) {
					gotoxy(j + 1, k + 4);
					CngTxtClr(YLW);
					printf("#");
					CngTxtClr(WTE);
				}
				else if (map_g[j][k] == 10) {
					gotoxy(j + 1, k + 4);
					CngTxtClr(RED);
					printf("$");
					CngTxtClr(WTE);
				}
				else if (map_g[j][k] == 0) {
					gotoxy(j + 1, k + 4);
					printf(" ");
				}
			}
		}
		map_g[mx-1][my-4] = 0;
	}	
}

void movekey(int32_t *x, int32_t *y) {
	//TODO: Add Input-delay
	static int32_t px, py;
	int32_t ch;

	gotoxy(px, py);
	CngTxtClr(GRE);
	printf("O");
	CngTxtClr(WTE);

	if (g_cnt == 0) {
		px = 1; py = 4;
		g_cnt++;
	}
	else {
		ch = _getch();
		switch (ch) {
		case DOWN:
			if (py > PY_MIN && py < PY_MAX && py + 1 != PY_MAX-1 && map_g[px-1][py-3] != 2)
				py++;
			break;

		case UP:
			if (py > PY_MIN && py < PY_MAX && py - 1 != PY_MIN && map_g[px-1][py-5] != 2)
				py--;
			break;

		case LEFT:
			if (px >= PX_MIN && px < PX_MAX && px - 1 != PX_MIN-1 && map_g[px-2][py-4] != 2)
				px--;		
			break;

		case RIGHT:
			if (px >= PX_MIN && px < PX_MAX && px + 1 != PX_MAX-1 && map_g[px][py-4] != 2)
				px++;
			break;

		default:
			break;
		}
		printf("\b ");
		gotoxy(px, py);
		//?????? ??????
		CngTxtClr(GRE);
		printf("O");
		CngTxtClr(WTE);
		*x = px;
		*y = py;
	}

}

void movemonster(int32_t* x, int32_t* y) {
	//TODO: Add Input-delay
	static int32_t count, mx, my;
	int32_t rd;
	gotoxy(mx, my);

	if (g_cnt2 == 0) {
		mx = 20; my = 12;
		g_cnt2++;
	}
	else {
		rd = rand() % 4;
		switch (rd) {
		case 0:
			if (my > PY_MIN && my < PY_MAX && my + 1 != PY_MAX - 1 && map_g[mx - 1][my - 3] != 2)
				my++;
			break;

		case 1:
			if (my > PY_MIN && my < PY_MAX && my - 1 != PY_MIN && map_g[mx - 1][my - 5] != 2)
				my--;
			break;

		case 2:
			if (mx >= PX_MIN && mx < PX_MAX && mx - 1 != PX_MIN - 1 && map_g[mx - 2][my - 4] != 2)
				mx--;
			break;

		case 3:
			if (mx >= PX_MIN && mx < PX_MAX && mx + 1 != PX_MAX - 1 && map_g[mx][my - 4] != 2)
				mx++;
			break;

		default:
			break;
		}
		*x = mx;
		*y = my;
	}

}

void Create_Ground(int16_t x, int16_t y) {
	/******************************************************************
	*if you use a emoji like '??', the emojis consume 2 spaces.
	*If you want to move one coordinate, you have to move two spaces.
	*TODO: Find the right ground size
	******************************************************************/
	int32_t i, j;

	CngTxtClr(YLW);
	for (i = 1; i <= x; i++) {
		printf("|");
	}
	printf("\n");
	for (i = 1; i <= y - 2; i++) {
		printf("|");
		for (j = 1; j <= x - 2; j++) {
			printf(" ");
		}
		printf("|\n");
	}
	for (i = 1; i <= x; i++) {
		printf("|");
	}
	
	CngTxtClr(WTE);
	gotoxy(0, 3);
	for (i = 0; i < 25; i++) printf("??");
	for (i = 0; i < 29; i++) printf("-");
	
	gotoxy(0, 20);
	for (i = 0; i < 25; i++) printf("??");
	for (i = 0; i < 29; i++) printf("-");

	for (i = 0; i < 17; i++) {
		gotoxy(78, i + 3); printf("|");
	}
	
	printf("\n");
}

void CreateObstacle(int32_t lv) {
	/***************************************************************************
	*Emoji test list
	*??!@#$%^&*()_+|
	* -------------------------
	* MT: 1, wall: 2, drinking party: 3, class absence: 4
	* dining : 5, Team project: 6, homework: 7,  class: 8, online class: 9
	*TODO: Add the verification method to check obstacles are created correctly
	*TODO: Add spawn area protection
	***************************************************************************/
	int32_t item[MAP_WIDTH - 2][MAP_HEIGHT - 2] = { 0, };
	int32_t i, j, k, x, y, col, row;
	uint16_t count = 0;
	int32_t mt=0, dp=0, ca=0, di=0, tp=0, hw=0, cl=0, oc=0; //without wall

	switch (lv) {
	case 1:
		mt = 1; dp = 2; ca = 3; di = 4; tp = 1; hw = 2; cl = 3; oc = 4;
		break;
	case 2:
		mt = 1; dp = 2; ca = 2; di = 4; tp = 1; hw = 2; cl = 4; oc = 3;
		break;
	case 3:
		mt = 1; dp = 2; ca = 2; di = 3; tp = 1; hw = 2; cl = 3; oc = 3;
		break;
	case 4:
		mt = 0; dp = 3; ca = 3; di = 2; tp = 1; hw = 3; cl = 3; oc = 3;
		break;
	case 5:
		mt = 0; dp = 2; ca = 3; di = 2; tp = 4; hw = 4; cl = 4; oc = 4;
	
	default:
		break;
	}

	col = sizeof(item[0]) / sizeof(int32_t);
	row = sizeof(item) / sizeof(item[0]);
	
	//init
	memset(map_g, 0, sizeof(map_g));

	//spawn area protection
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			item[i][j] = 27;
		}
	}

	//Create random item
	for (i = 0; i <= mt; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 1;
		else i--;
	}
		
	for (i = 0; i <= dp; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 3;
		else i--;
	}

	for (i = 0; i <= ca; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 4;
		else i--;
	}

	for (i = 0; i <= di; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 5;
		else i--;
	}

	for (i = 0; i <= tp; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 6;
		else i--;
	}

	for (i = 0; i <= hw; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 7;
		else i--;
	}

	for (i = 0; i <= cl; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 8;
		else i--;
	}

	for (i = 0; i <= oc; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 9;
		else i--;
	}

	//Create random wall
	for (i = 0; i <= 70; i++) {
		x = rand() % MAP_WIDTH - 2;
		y = rand() % MAP_HEIGHT - 2;

		if (item[x][y] == 0) item[x][y] = 2;
		else i--;
	}

	//print
	for (j = 0; j < row; j++) {
		for (k = 0; k < col; k++) {
			if (item[j][k] != 0 && item[j][k] != 2 && item[j][k] != 27) {
				if (lv != 5) {
					gotoxy(j + 1, k + 4);
					printf("@");
				}
			}
			else if (item[j][k] == 2) {
				gotoxy(j+1, k+4);
				CngTxtClr(YLW);
				printf("#");
				CngTxtClr(WTE);
			}
		}
	}

	//copy
	memmove(map_g, item, sizeof(item));
	memset(item, 0, sizeof(item));
}

void StatusPrint(int32_t score, int32_t hp, int32_t st, int32_t lv, float time) {
	//explain about item information (2, 22). 5, 7
	gotoxy(52, 5); printf("??????:       "); gotoxy(60, 5); printf("%d", score);
	gotoxy(52, 7); printf("????:          "); gotoxy(60, 7); printf("%d", hp);
	gotoxy(52, 9); printf("????:          "); gotoxy(60, 9); printf("%.f", time);
	gotoxy(2, 22); printf("                                                              ");
	gotoxy(2, 22);
	switch (st) {
	case 1:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("?????????? ?????? mt?? ?? ????, ???????? 30 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+30  "); CngTxtClr(WTE);
		break;
	case 3:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("???????? ?? ????, ???????? 10?????????? ?????? 10 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+10  "); CngTxtClr(RED); printf("-10"); CngTxtClr(WTE);
		break;
	case 4:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("?????? ???? ????, ?????? 20 ?????? 10 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+20  "); printf("+10"); CngTxtClr(WTE);
		break;
	case 5:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("???????? ?? ????, ???????? 10 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); CngTxtClr(GRE); printf("+10  "); CngTxtClr(WTE);
		break;
	case 6:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("?????? ???? ?????? ?????? 30 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-30"); CngTxtClr(WTE);
		break;
	case 7:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("?????? ???? ?????? ?????? 20 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-20"); CngTxtClr(WTE);
		break;
	case 8:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("???? ?????? ?? ?????? ?????? 15 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-15"); CngTxtClr(WTE);
		break;
	case 9:
		if (lv == 5) printf("?????? ???????????? ???????? ??????!");
		else printf("?????? ?????? ???? ?????? ?????? 10 ??????????.");
		gotoxy(67, 22); printf("         ");
		gotoxy(67, 22); printf("     "); CngTxtClr(RED); printf("-10"); CngTxtClr(WTE);
		break;
	default:
		break;
	}
}

void GameOver(int32_t count, int32_t* monster) {
	int32_t g, c = 0;
	system("cls");
	gotoxy(11, 6);  printf("|?? game.konkuk.ac.kr:23/GameOver   |");
	gotoxy(59, 6);  printf("??|?? |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|                      Game Over!                       |");
	gotoxy(11, 9);  printf("|                                                       |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                                                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(32, 14); printf("Press Any Key!!");
	gotoxy(68, 22); printf("| Q: exit |");

	switch (count) {
	case 1:
		if (*monster == 1) {
			gotoxy(23, 11); printf("???????? ???????? ??????????.");
			gotoxy(27, 12); printf("?????????? ??????????");
		}
		else {
			gotoxy(28, 11); printf("???? ?????? ????????");
			gotoxy(26, 12); printf("?????? ?????? ??????????.");
		}
		break;
	case 2:
		if (*monster == 1) {
			gotoxy(23, 11); printf("?????? ?????????? ??????????");
			gotoxy(27, 12); printf("?????????? ??????????");
		}
		else {
			gotoxy(23, 11); printf("???? ???? ?????? ???? ??????????.");
			gotoxy(20, 12); printf("???? ?????? ?????? ?? ???? ??????????");
		}
		break;
	case 3:
		if (*monster == 1) {
			gotoxy(23, 11); printf("???????? ???????? ??????????.");
			gotoxy(27, 12); printf("?????????? ??????????");
		}
		else {
			gotoxy(18, 11); printf("?????? ?? ???? ?????? ?????? ?? ??????????.");
			gotoxy(26, 12); printf("???? ?? ?????? ??????????");
		}
		break;
	case 4:
		if (*monster == 1) {
			gotoxy(23, 11); printf("???????? ???????? ??????????.");
			gotoxy(27, 12); printf("?????????? ??????????");
		}
		else {
			gotoxy(25, 11); printf("?????? ???? ???? ?????? ????");
			gotoxy(24, 12); printf("???? ???????? ???? ???? ??????.");
		}
		break;
	default:
		gotoxy(25, 10); printf("???????? ?????? ??????????");
		gotoxy(25, 11); printf("\"???????? ?????? ?? ????,,");
		gotoxy(22, 12); printf("????,, ???????? ?? ?????? ??????\"");
		d_t = 0;
		c = 1;
		break;
	}
	
	g = _getch();
	if (g != 'q' && g != 'Q') {
		if (c == 1) {
			c = 0;
			Game_Core(5);
		}
	}
	else {
		exit(0);
	}
}

void GameClear(int32_t lv) {
	int32_t g;
	system("cls");
	gotoxy(11, 6);  printf("|?? game.konkuk.ac.kr:23/GameClear   |");
	gotoxy(59, 6);  printf("??|?? |X|");
	gotoxy(11, 7);  printf("---------------------------------------------------------");
	gotoxy(11, 8);  printf("|                     Game Clear!                       |");
	gotoxy(11, 9);  printf("|                                                       |");
	gotoxy(11, 10); printf("|                                                       |");
	gotoxy(11, 11); printf("|                                                       |");
	gotoxy(11, 12); printf("|                                                       |");
	gotoxy(11, 13); printf("---------------------------------------------------------");
	gotoxy(27, 14); printf("Press Any Key to next Level");
	gotoxy(27, 11);
	switch (lv) {
	case 1: 
		gotoxy(20, 11); printf("???????? ?? ???? ?????????? ???? ????");
		gotoxy(21, 12); printf("???????? ???????? ???? ??????????!");
		break;
	case 2:
		gotoxy(18, 11); printf("???????? ?????? ???? ?????????? ???? ????");
		gotoxy(18, 12); printf("???? ?????????? ???? ???? ???? ??????????!");
		break;
	case 3:
		gotoxy(18, 11); printf("???????? ?????? ???? ?????????? ???? ????");
		gotoxy(14, 12); printf("???? ???????? ?? ?????? ???? ???? ???? ??????????!");
		break;
	case 4:
		gotoxy(22, 11); printf("???????? ?????? ?????? ?????????? ???? ????");
		gotoxy(27, 12); printf("?????? ??????????!");
		break;
	default:
		break;
	}
	gotoxy(61, 22); printf("| Q: Main menu |");
	g = _getch();
	if (g != 'q' && g != 'Q') {
		if (lv < 4) 
			Game_Core(lv + 1);
	}
	else if(g == 'q' || g == 'Q')  {

	}
}

void PrintTextS(uint16_t delay, uint8_t* ch) {
	int32_t i;
	int32_t length = strlen(ch);
	for (i = 0; i < length; i++) {
		printf("%c", ch[i]);
		Sleep(delay);
	}
}