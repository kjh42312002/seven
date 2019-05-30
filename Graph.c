#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int   numVertices;
int	  numEdges;

enum Colors {black, blue, green, cyan, red, purple, yellow, white, gray, Lblue, Lgreen, Lcyan, Lred, Lpurple, Lyellow, Lwhite};

typedef struct building {
	int buildingIndex;
	char buildingNumber[7];
	char buildingName[50];
}Building;

typedef struct alnode *adjListptr;
typedef struct alnode {
	Building building;
	int 		weight;
	adjListptr 	link;
}alnode;

Building* buildingList = NULL;
adjListptr *adjList = NULL;

short int *visited;

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetColor(unsigned short text, unsigned short back) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
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


//도움말 출력
void PrintHelp()
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

//타이틀 출력
void PrintTitle()
{
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	HBITMAP hImage, hOldBitmap;
	HDC hMemDC = CreateCompatibleDC(mydc);

	hImage = (HBITMAP)LoadImage(NULL, TEXT("6.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
	BitBlt(mydc, 0, 0, 200 * 10, 200 * 20, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hImage);
	DeleteDC(hMemDC);
	ReleaseDC(myconsole, mydc);
}

int SearchIndex(char target[]) {
	int i = 0;
	while (1) {
		if (strcmp(target, buildingList[i].buildingNumber) == 0)
			return i;
		i++;
		if (i > numVertices) {
			return -1;
		}
	}
}

Building* ReadBuildingData(const char *filename) {
	FILE *fp;
	char line[100];
	char *buffer;

	fp = fopen(filename, "r");

	printf("건물 정보를 불러오는 중...\n");
	fscanf_s(fp, "%d\n", &numVertices);
	Building* buildingList = (Building*)malloc(numVertices * sizeof(Building));

	for (int i = 0; i < numVertices; i++) {
		fgets(line, sizeof(line), fp);
		buildingList[i].buildingIndex = i;
		buffer = strtok(line, "/");
		strcpy(buildingList[i].buildingNumber, buffer);
		buffer = strtok(NULL, "\n");
		strcpy(buildingList[i].buildingName ,buffer);
	}
	return buildingList;
}

void CreateGraphFromFile(const char *filename)
{
	char	v1[7], v2[7];
	int		weight;
	FILE	*fp;

	adjListptr tmp1, tmp2;

	fp = fopen(filename, "r");

	printf("에지 정보를 불러오는 중.. \n");
	fscanf_s(fp, "%d", &numEdges);

	visited = (short int *)malloc(sizeof(short int));

	adjList = (adjListptr *)malloc(sizeof(adjListptr)*numVertices);
	for (int i = 0; i < numVertices; i++) {
		adjList[i] = NULL;
	}

	for (int i = 0; i < numEdges; i++)
	{
		fscanf_s(fp, "%s %s %d\n", &v1, 7, &v2, 7, &weight);


		tmp1 = (adjListptr)malloc(sizeof(struct alnode));
		tmp1->building = buildingList[SearchIndex(v2)];
		tmp1->weight = weight;
		tmp1->link = NULL;
		if (adjList[SearchIndex(v1)] == NULL) {
			adjList[SearchIndex(v1)] = tmp1;
		}
		else {
			tmp1->link = adjList[SearchIndex(v1)];
			adjList[SearchIndex(v1)] = tmp1;
		}

		tmp2 = (adjListptr)malloc(sizeof(struct alnode));
		tmp2->building = buildingList[SearchIndex(v1)];
		tmp2->weight = weight;
		tmp2->link = NULL;
		if (adjList[SearchIndex(v2)] == NULL) {
			adjList[SearchIndex(v2)] = tmp2;
		}
		else {
			tmp2->link = adjList[SearchIndex(v2)];
			adjList[SearchIndex(v2)] = tmp2;
		}
	}

	fclose(fp);
}

int ChooseMinimumDistance(int distance[], short int found[]) {
	int output = -1;
	for (int i = 0; i < numVertices; i++) {
		if (found[i] == 0 && distance[i] != 9999 && (output < 0 || distance[output] > distance[i])) {
			output = i;
		}
	}
	return output;
}

int* FindPath(int start, int finish) {
	int *distance = (int*)calloc(numVertices, sizeof(int));
	int *prevNode = (int*)calloc(numVertices, sizeof(int));
	short int* found = (short int*)calloc(numVertices, sizeof(short int));
	int *output;
	int cursor;
	alnode* search = adjList[start];;

	if (adjList[start] == NULL) {
		printf("여기서는 아무데도 못가요!\n");
		return NULL;
	}
	for (int i = 0; i < numVertices; i++) {
		distance[i] = 9999;	//9999 = INF
		prevNode[i] = -1;
	}
	while (1) {
		distance[search->building.buildingIndex] = search->weight;
		prevNode[search->building.buildingIndex] = start;
		if (search->link == NULL)
			break;
		search = search->link;
	}
	found[start] = 1;
	distance[start] = 0;
	for (int i = 0; i < numVertices - 2; i++) {
		cursor = ChooseMinimumDistance(distance, found);
		search = adjList[cursor];
		found[cursor] = 1;
		if (cursor == -1) {
			break;
		}
		while (1) {
			if (search != NULL && search->building.buildingIndex < numVertices && !found[search->building.buildingIndex])
			{
				if (distance[cursor] + search->weight < distance[search->building.buildingIndex]) {
					distance[search->building.buildingIndex] = distance[cursor] + search->weight;
					prevNode[search->building.buildingIndex] = cursor;
				}
			}
			else if (search == NULL || search->building.buildingIndex >= numVertices) {
				break;
			}
			search = search->link;
		}
	}
	if (finish < 0) {	//편의점(-1),카페(-2)를 검색
		int closestBuilding = 0;
		int closestDistance = 9999;
		for (int i = 0; i < numVertices; i++) {
			if (strstr(buildingList[i].buildingName, finish == -1 ? "편의점" : "카페") != NULL) {
				if (closestDistance > distance[i]) {
					closestDistance = distance[i];
					closestBuilding = i;
				}
			}
		}
		finish = closestBuilding;
	}
	int prevSearch = finish;
	int index = 1;
	while (prevSearch != -1) {
		prevSearch = prevNode[prevSearch];
		index++;
	}
	output = (int*)calloc(index + 1, sizeof(int));
	output[0] = distance[finish];
	output[1] = index;
	prevSearch = finish;
	for (; index > 1; index--) {
		output[index] = prevSearch;
		prevSearch = prevNode[prevSearch];
	}
	return output;
}

void DrawSquare() {
	gotoxy(2, 17);
	printf("┏");
	for (int d = 1; d < 63; d++) {
		printf("━");
	}
	printf("┓");
	gotoxy(2, 18);
	printf("┃");
	gotoxy(65, 18);
	printf("┃");
	gotoxy(2, 19);
	printf("┣");
	for (int d = 1; d < 63; d++) {
		printf("━");
	}
	printf("┫");
	for (int d = 20; d < 49; d++) {
		gotoxy(2, d);
		printf("┃");
		gotoxy(65, d);
		printf("┃");
	}
	gotoxy(2, 49);
	printf("┗");
	for (int d = 1; d < 63; d++) {
		printf("━");
	}
	printf("┛");
}

void RefreshScreen(int location, int* output) {
	SetColor(gray, Lwhite);
	for (int d = 20; d < 49; d++) {
		gotoxy(61, d);
		printf("∥∥");;
	}
	//스크롤바
	if (output[1] > 16) {
		int y = 21 + (float)((float)location / ((float)output[1] - 16)) * 22;
		for (int i = 0; i < 5; i++) {
			gotoxy(61, y+i);
			printf(" ▩ ");
		}
		gotoxy(61, y + 2);
		printf(" ■ ");
	}
	//스크롤 가능 표시등
	gotoxy(61, 20);
	if (location > 0) {printf(" ▲ ");}
	else {printf(" □ ");}
	gotoxy(61, 48);
	if (location + 16 < output[1]) {printf(" ▼ ");}
	else {printf(" □ ");}
	for (int d = 20; d < 49; d++) {
		gotoxy(12, d);
		printf("│");
	}
	//건물 이름 번호 표시
	SetColor(black, Lwhite);
	for (int i = 2; i < 17; i++) {
		gotoxy(4, 16 + i * 2);
		for (int x = 4; x != 12; x++) {
			printf(" ");
		}
		if (location + i == 2) {
			SetColor(red, Lwhite);
		}
		if (location + i == output[1]) {
			SetColor(blue, Lwhite);
		}
		gotoxy(4, 16 + i * 2);
		printf("%s", buildingList[output[location+i]].buildingNumber);
		gotoxy(15, 16 + i * 2);
		for (int x = 16; x != 50; x++) {
			printf(" ");
		}
		gotoxy(15, 16 + i * 2);
		printf("%s", buildingList[output[location+i]].buildingName);
		SetColor(black, Lwhite);
		gotoxy(13, 17 + i * 2);
		printf("│");
		gotoxy(3, 17 + i * 2);
		for (int d = 1; d < 57; d++) {
			printf("─");
		}
		if (location + i != output[1]) {
			gotoxy(8, 17 + i * 2);
			printf("v");
		}
		else {
			break;
		}
	}
}

void RefreshScreenDiv(int location, int* outputA, int* outputB) {
	//건물 이름 번호 표시
	SetColor(black, Lwhite);
	for (int i = 2; i < 17; i++) {
		if (location + i == 2) {
			SetColor(red, Lwhite);
		}
		if (location + i == outputA[1]) {
			SetColor(blue, Lwhite);
		}
		gotoxy(4, 16 + i * 2);
		printf("%s", buildingList[outputA[location + i]].buildingNumber);
		gotoxy(15, 16 + i * 2);
		printf("%.16s", buildingList[outputA[location + i]].buildingName);
		if (strlen(buildingList[outputA[location + i]].buildingName) > 16) {
			printf("…");
		}
		gotoxy(4, 17 + i * 2);
		SetColor(black, Lwhite);
		for (int d = 1; d < 28; d++) {
			printf("─");
		}
		if (location + i != outputA[1]) {
			gotoxy(8, 17 + i * 2);
			printf("v");
		}
		else {
			break;
		}
	}
	for (int i = 2; i < 17; i++) {
		if (location + i == 2) {
			SetColor(red, Lwhite);
		}
		if (location + i == outputB[1]) {
			SetColor(blue, Lwhite);
		}
		gotoxy(36, 16 + i * 2);
		printf("%s", buildingList[outputB[location + i]].buildingNumber);
		gotoxy(45, 16 + i * 2);
		printf("%.16s", buildingList[outputB[location + i]].buildingName);
		if (strlen(buildingList[outputB[location + i]].buildingName) > 16) {
			printf("…");
		}
		gotoxy(36, 17 + i * 2);
		SetColor(black, Lwhite);
		for (int d = 1; d < 28; d++) {
			printf("─");
		}
		if (location + i != outputB[1]) {
			gotoxy(40, 17 + i * 2);
			printf("v");
		}
		else {
			break;
		}
	}
}

void DisplayAB(char start[], char destination[]) {
	int startNum = SearchIndex(start);
	int destinationNum = SearchIndex(destination);
	int* output = NULL;
	int location = 0;
	int key = 0;
	if (startNum == -1) {
		printf("없는 건물인데요?\n");
		return;
	}
	else {
		output = FindPath(startNum, destinationNum);
	}
	DrawSquare();
	gotoxy(4, 18);
	SetColor(yellow, Lwhite);
	printf("검색결과│  예상 도보 시간: %d분", output[0] / 4 * 3);
	SetColor(black, Lwhite);
	RefreshScreen(location, output);
	while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == 224) {
				key = _getch();
				switch (key) {
				case 72:	//위 방향키
					if (location > 0) {
						location--;
						RefreshScreen(location, output);
					}
					break;
				case 80:	//아래 방향키
					if (location + 16 < output[1]) {
						location++;
						RefreshScreen(location, output);
					}
					break;
				default:
					break;
				}
			}
		}
		else if (key == 13) {
			break;
		}
	}
}

void Display(char start[]) {
	int startNum = SearchIndex(start);
	int* outputCVS = NULL;
	int* outputCafe = NULL;
	int location = 0;
	int key = 0;
	if (startNum == -1) {
		printf("없는 건물인데요?\n");
		return;
	}
	else {
		outputCVS = FindPath(startNum, -1);
		outputCafe = FindPath(startNum, -2);
	}
	DrawSquare();
	for (int d = 18; d < 49; d++) {
		gotoxy(33, d);
		printf("┃┃");
	}
	gotoxy(10, 16);
	SetColor(purple, Lwhite);
	printf("가장 가까운 편의점");
	gotoxy(43, 16);
	printf("가장 가까운 카페");
	gotoxy(3, 18);
	SetColor(yellow, Lwhite);
	printf(" 예상 도보 시간: %d분", outputCVS[0] / 4 * 3);
	gotoxy(36, 18);
	printf(" 예상 도보 시간: %d분", outputCafe[0] / 4 * 3);
	SetColor(black, Lwhite);
	RefreshScreenDiv(location, outputCVS, outputCafe);
	while (1) {
		if (_kbhit()) {
			key = _getch();
			if (key == 13) {
				break;
			}
		}
	}
}

void input(int mode) {
	system("cls");
	char start[10];
	if (mode == 0)	//경로 탐색
	{
		char destination[10];
		gotoxy(1, 1);
		printf("출발지 입력: ");
		scanf_s("%s", start, 10);
		printf("도착지 입력: ");
		scanf_s("%s", destination, 10);
		DisplayAB(start, destination);
	}
	else if (mode == 1) {
		gotoxy(1, 1);
		printf("출발지 입력: ");
		scanf_s("%s", start, 10);
		Display(start);
	}
}

//메인메뉴
void MainMenu()
{
	int x, y;
	while (1) {

		x = 18; y = 25;
		gotoxy(x, y);
		printf("┌───────────────────────────┐");
		gotoxy(x, y + 1);
		printf("│ 　 충북대 길안내 도우미   │");
		gotoxy(x, y + 2);
		printf("└───────────────────────────┘");
		x += 2;
		y += 4;
		for (int i = 0; i < 4; i++) {
			gotoxy(x, y + i * 4);
			printf("┌───────────────────────┐");
			gotoxy(x, y + i * 4 + 2);
			printf("└───────────────────────┘");
		}
		gotoxy(x, 30);
		printf("│　　　 1.경로탐색　    │");
		gotoxy(x, 34);
		printf("│       2.편의시설      │");
		gotoxy(x, 38);
		printf("│       3. 도움말　　   │");
		gotoxy(x, 42);
		printf("│　　   4.  종료　  　  │");
		char key;
		x -= 3;
		y++;
		y = 30;
		gotoxy(x, y);
		printf("▷");
		while (1)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				if (y != 30) {
					gotoxy(x, y);
					printf("　");
					y -= 4; gotoxy(x, y);
					printf("▷");
				}
				break;
			case 80:
				if (y != 42) {
					gotoxy(x, y);
					printf("　");
					y += 4; gotoxy(x, y);
					printf("▷");
				}
				break;
			case 13:
				if (y == 30) {
					input(0);//경로탐색함수
				}
				else if (y == 34) {
					input(1);//편의시설검색함수                 메뉴선택하고 스페이스바 누를때 해당 메뉴로 이동하도록
				}
				else if (y == 38) {
					PrintHelp();//도움말 함수 
					while (!_kbhit());
				}
				else if (y == 42) {
					return; //종료
				}
				break;
			}
			if (key == 13) {
				system("cls");
				break;
			}
		}
	}
}


void main()
{
	//char start[10]; //= { 'S','4','-','1' };
	//char destination[10]; //= { 'N','1','4' };
	system("color F0");
	system("mode con cols=67 lines=50");
	system("title 2019.06.09(07조 CBNU DIRECTION GUIDE ");
	CursorView(0);
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 500, -10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	buildingList = ReadBuildingData("BuildingData.txt");
	CreateGraphFromFile("RoadData.txt");
	PrintTitle();
	while (!_kbhit());
	getchar();
	PrintHelp();
	while (!_kbhit());
	system("cls");
	getchar();
	MainMenu();
}