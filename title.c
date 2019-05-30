#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void setcursortype(CURSOR_TYPE c) { //커서 안보이게 하는 함수 
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void setColor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

void titleMenu(void) { // 게임타이틀
	int i, j;
	int text_Direction_x = 1;
	int text_Direction_y = 8;
	int text_Guide_x = 13;
	int text_Guide_y = 15;
	
	int text_Direction[5][33] = {
	   1,1,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,
	   1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,
	   1,0,1,0,1,0,1,1,0,0,1,1,1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,
	   1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,
	   1,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,0,1,0,0,1,0,1,1,1,0,1,0,1,0,0,
	};

	int text_Guide[5][21] = {
	   0,1,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0,
	   1,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,0,0,0,
	   1,1,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,1,1,0,0,
	   1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,0,0,0,
	   0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0,0
	};

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
	Sleep(200);
	for (int cnt = 0;; cnt++) {
		Sleep(10);

		if (cnt % 50 == 0) {
			setColor(cnt % 7 + 2, 15);
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 33; j++) {
					gotoxy(text_Direction_x + j, text_Direction_y + i);
					if (text_Direction[i][j] == 1) printf("■");
				}
			}
		}
		if (cnt % 50 == 0) {
			setColor(cnt % 7 + 2, 15);
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 21; j++) {
					gotoxy(text_Guide_x + j, text_Guide_y + i);
					if (text_Guide[i][j] == 1) printf("■");
				}
			}
		}
		if (GetAsyncKeyState(VK_RETURN)) break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}

int main() {
	system("mode con:cols=67 lines=50");
	system("title 2019.06.09(07조 CBNU DIRECTION GUIDE) "); //상단문구 뭐로 정할지 검토!!!!!
	system("color f0");
	setColor(10, 15);
	srand((unsigned)time(NULL)); //난수표생성 
	setcursortype(NOCURSOR); //커서 없앰 
	titleMenu(); //게임타이틀
}
