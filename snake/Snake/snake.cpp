#include<iostream>
#include<graphics.h>
#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<mmsystem.h>
#include<stdlib.h>
#include<time.h>
#pragma comment(lib,"winmm.lib")
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define MAX_NUM 100
using namespace std;
IMAGE BKIMG;
struct coor
{
	int x;
	int y;
};
struct Food
{
	int flag;
	coor foodc;
}food;
struct snake
{
	coor skc[MAX_NUM];
	int n;
	int ch;
}s;
void welcome();
void initgame();
void movesnake();
void changemove();
void coorfood();
void drawfood();
void judge();
HWND hwnd = initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
int main()
{
	welcome();
	mciSendString("open ./resource/music2.mp3 alias bgm2", 0, 0, 0);
	mciSendString("play bgm2 repeat", 0, 0, 0);
	initgame();
	while (1)
	{
		while (!_kbhit())
		{
			if (food.flag == 0)
				coorfood();
			cleardevice();
			movesnake();
			judge();
			drawfood();
			if (s.skc[0].x == food.foodc.x && s.skc[0].y == food.foodc.y)
			{
				food.flag = 0;
				s.n++;
			}
			Sleep(100);
		}
		judge();
		changemove();
	}
	closegraph();
	return 0;
}
void welcome()
{
	mciSendString("open ./resource/music.mp3 alias bgm", 0, 0, 0);
	mciSendString("play bgm repeat", 0, 0, 0);
	MOUSEMSG msg = { 0 };
	loadimage(&BKIMG, "./resource/Rem.jpg", 640, 480);
	putimage(0, 0, &BKIMG);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, "Ravie");
	while (1)
	{
		msg = GetMouseMsg();
		settextcolor(RGB(0, 0, 255));
		outtextxy(470, 60, "Begin!");
		outtextxy(470, 120, "Exit!");
		settextstyle(15, 0, "Ravie");
		outtextxy(470, 250, "由孙延浩开发");
		outtextxy(470, 280, "未经允许不准商用");
		settextstyle(50, 0, "Ravie");
		if (msg.x > 470 && msg.x < 610 && msg.y>60 && msg.y < 110)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(470, 60, "Begin!");
		}
		else if (msg.x > 470 && msg.x < 610 && msg.y>120 && msg.y < 170)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(470, 120, "Exit!");
		}
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (msg.x > 470 && msg.x < 610 && msg.y>60 && msg.y < 110)
			{
				cleardevice();
				mciSendString("stop bgm", 0, 0, 0);
				return;
			}
			else if (msg.x > 470 && msg.x < 610 && msg.y>120 && msg.y < 170)
			{
				MessageBox(hwnd, "じゃね", "", MB_OK);
				exit(1);
			}
			break;
		default:
			break;
		}
	}
}
void initgame()
{
	food.flag = 0;
	srand((unsigned int)time(NULL));
	setbkcolor(RGB(122, 233, 233));
	cleardevice();
	setlinecolor(RED);
	s.skc[0].x = 0;
	s.skc[0].y = 0;
	s.n = 1;
	s.ch = 77; //上72 下80 左75 右77
}
void movesnake()
{
	setfillcolor(GREEN);
	for (int i = s.n - 1; i > 0; i--)
	{
		s.skc[i].x = s.skc[i - 1].x;
		s.skc[i].y = s.skc[i - 1].y;
	}
	switch (s.ch)
	{
	case 72:
		s.skc[0].y -= 10;
		break;
	case 80:
		s.skc[0].y += 10;
		break;
	case 75:
		s.skc[0].x -= 10;
		break;
	case 77:
		s.skc[0].x += 10;
		break;
	}
	for (int i = 0; i < s.n; i++)
	{
		fillrectangle(s.skc[i].x, s.skc[i].y, s.skc[i].x + 10, s.skc[i].y + 10);
	}
}
void changemove()
{
	int move;
	move = getch();
	switch (move)
	{
	case 72:
		if (s.ch != 80)
			s.ch = move;
		break;
	case 80:
		if (s.ch != 72)
			s.ch = move;
		break;
	case 75:
		if (s.ch != 77)
			s.ch = move;
		break;
	case 77:
		if (s.ch != 75)
			s.ch = move;
		break;
	default:
		break;
	}
}
void coorfood()
{
	food.foodc.x = rand() % 64 * 10;
	food.foodc.y = rand() % 48 * 10;
	food.flag = 1;
}
void drawfood()
{
	setfillcolor(RED);
	fillroundrect(food.foodc.x, food.foodc.y, food.foodc.x + 10, food.foodc.y + 10, 10, 10);
}
void judge()
{
	if (s.skc[0].x < 0 || s.skc[0].x>640 || s.skc[0].y < 0 || s.skc[0].y>480)
	{
		MessageBox(hwnd, "さようなら", "", MB_OK);
		exit(1);
	}
	for (int i = 1; i < s.n; i++)
	{
		if (s.skc[0].x == s.skc[i].x && s.skc[0].y == s.skc[i].y)
		{
			MessageBox(hwnd, "さようなら", "", MB_OK);
			exit(1);
		}
	}
}