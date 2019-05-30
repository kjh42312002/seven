#include <stdio.h>
#include <windows.h>
#include<conio.h>
#define up 72
#define down 80
#define space 32

void cur();
void MainMenu();
void CursorView();
int main(void)
{
	system("mode con: cols=67 lines=50");
	system("color f0");
	MainMenu();


	return 0;
}

void cur(short x, short y) //커서 이동  
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void MainMenu() //메인메뉴 출력
{
	CursorView(0);
	int x, y;
	x = 20;
	y = 25;
	x -= 2;
	cur(x, y);
	printf("┌───────────────────────────┐");
	cur(x, y + 1);
	printf("│ 　 충북대 길안내 도우미   │");
	cur(x, y + 2);
	printf("└───────────────────────────┘");
	x += 2;
	y += 4;
	cur(x, y);
	printf("┌───────────────────────┐");
	cur(x, y + 1);
	printf("│　　　 1.경로탐색　    │");
	cur(x, y + 2);
	printf("└───────────────────────┘");
	y += 4;
	cur(x, y);
	printf("┌───────────────────────┐");
	cur(x, y + 1);
	printf("│       2.편의시설      │");
	cur(x, y + 2);
	printf("└───────────────────────┘");
	y += 4;
	cur(x, y);
	printf("┌───────────────────────┐");
	cur(x, y + 1);
	printf("│       3. 도움말　　   │");
	cur(x, y + 2);
	printf("└───────────────────────┘");
	y += 4;
	cur(x, y);
	printf("┌───────────────────────┐");
	cur(x, y + 1);
	printf("│　　   4.  종료　  　  │");
	cur(x, y + 2);
	printf("└───────────────────────┘");
	char key;
	x -= 3;
	y++;
	cur(x, y);
	printf("▷");
	while (1)
	{
		key = _getch();
		switch (key)
		{
		case up: if (y == 30) {
			break;
		}
				 else {
			cur(x, y);
			printf("　");
			y -= 4; cur(x, y);
			printf("▷");
			break;
		}
		case down: if (y == 42) {
			break;
		}
				   else {
			cur(x, y);
			printf("　");
			y += 4; cur(x, y);
			printf("▷");
			break;
		}
				   /*case space: if (y == 21)
					  input(경로위치);//경로탐색함수
					  if (y == 22)
						input(편의시설);//편의시설검색함수                 메뉴선택하고 스페이스바 누를때 해당 메뉴로 이동하도록
					  if (y == 23)
						help();//도움말 함수
					  if (y == 24)
				   return 0; //종료
				   */
		}
	}
}

void CursorView(char show)//커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}	