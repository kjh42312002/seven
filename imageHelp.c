#include <stdio.h>
#include <windows.h>
#include<conio.h>

void gotoxy(int x, int y) { //gotoxyÇÔ¼ö 
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Print_Board()
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	HBITMAP hImage, hOldBitmap;
	HDC hMemDC = CreateCompatibleDC(mydc);

	hImage = (HBITMAP)LoadImage(NULL, TEXT("7.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
	BitBlt(mydc, 0, 0, 200 * 10, 200 * 20, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hImage);
	DeleteDC(hMemDC);
	ReleaseDC(myconsole, mydc);
}


void main() {
	while (1) {
		Print_Board();
		if (_kbhit())
		{
			if (_getch() == 'z')
				break;
		}
	}
	gotoxy(0, 100);
}
