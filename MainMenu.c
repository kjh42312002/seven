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

void cur(short x, short y) //Ŀ�� �̵�  
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void MainMenu() //���θ޴� ���
{
	CursorView(0);
	int x, y;
	x = 20;
	y = 25;
	x -= 2;
	cur(x, y);
	printf("����������������������������������������������������������");
	cur(x, y + 1);
	printf("�� �� ��ϴ� ��ȳ� �����   ��");
	cur(x, y + 2);
	printf("����������������������������������������������������������");
	x += 2;
	y += 4;
	cur(x, y);
	printf("��������������������������������������������������");
	cur(x, y + 1);
	printf("�������� 1.���Ž����    ��");
	cur(x, y + 2);
	printf("��������������������������������������������������");
	y += 4;
	cur(x, y);
	printf("��������������������������������������������������");
	cur(x, y + 1);
	printf("��       2.���ǽü�      ��");
	cur(x, y + 2);
	printf("��������������������������������������������������");
	y += 4;
	cur(x, y);
	printf("��������������������������������������������������");
	cur(x, y + 1);
	printf("��       3. ���򸻡���   ��");
	cur(x, y + 2);
	printf("��������������������������������������������������");
	y += 4;
	cur(x, y);
	printf("��������������������������������������������������");
	cur(x, y + 1);
	printf("������   4.  ���ᡡ  ��  ��");
	cur(x, y + 2);
	printf("��������������������������������������������������");
	char key;
	x -= 3;
	y++;
	cur(x, y);
	printf("��");
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
			printf("��");
			y -= 4; cur(x, y);
			printf("��");
			break;
		}
		case down: if (y == 42) {
			break;
		}
				   else {
			cur(x, y);
			printf("��");
			y += 4; cur(x, y);
			printf("��");
			break;
		}
				   /*case space: if (y == 21)
					  input(�����ġ);//���Ž���Լ�
					  if (y == 22)
						input(���ǽü�);//���ǽü��˻��Լ�                 �޴������ϰ� �����̽��� ������ �ش� �޴��� �̵��ϵ���
					  if (y == 23)
						help();//���� �Լ�
					  if (y == 24)
				   return 0; //����
				   */
		}
	}
}

void CursorView(char show)//Ŀ�������
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}	