#pragma once
#pragma comment(lib, "winmm.lib")
#include<iostream>
#include "windows.h"
#include <conio.h>
using namespace std;
class Snake
{
private:
	int length;
	int score;
	int color;
	int oldColor;
public:
	Snake()
	{
		length = 4;
		score = 0;
		color = 7;
		oldColor = 7;
	}
	void DrawTopLine();
	void DrawBotLine();
	void DrawLeftLine();
	void DrawRightLine();
	void DrawAllLine();
	void DrawSnake(int X[], int Y[]);
	void DeleteData(int X[], int Y[]);
	void Init(int X[], int Y[], int x, int y);
	void Processing(int tX[], int tY[], int x, int y, int& x0, int& y0, int check);
	void Add(int a[], int k);
	void Delete(int a[], int vt);
	void CreateDollar(int& x0, int& y0, int toaDoX[], int toaDoY[]);
	bool IsSnakeTouchBody(int X[], int Y[]);
	bool IsGameOver(int x0, int y0);
	bool IsSnakeOnDollar(int X[], int Y[], int x0, int y0);
	bool IsSnakeEatDollar(int& x0, int& y0, int X[], int Y[]);
	void Play(int level);
	void PlayModern(int level);
	void Menu(int& play);
	void gotoXY(int x, int y);
	void SetColor(WORD color);
	void Nocursortype();
	void Level(int type, int &play);
};

