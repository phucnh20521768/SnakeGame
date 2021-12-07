#include "Snake.h"
#include <mmsystem.h>
void Snake::Menu(int& play)
{
	system("cls");
	int countMenu = 0;
	length = 4;
	gotoXY(60, 10);
	SetColor(6);
	cout << "CLASSIC";
	SetColor(7);
	gotoXY(60, 11);
	cout << "MODERN";
	gotoXY(60, 12);
	cout << "QUIT";
	char kiTu;
	while (true)
	{
		if (_kbhit())
		{
			kiTu = _getch();
			if (kiTu == -32)
			{
				kiTu = _getch();
				if (kiTu == 72) // di len
				{
					PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (countMenu == 0)
					{
						countMenu = 2;
						gotoXY(60, 10);
						SetColor(7);
						cout << "CLASSIC";
						SetColor(7);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(6);
						gotoXY(60, 12);
						cout << "QUIT";
					}
					else if (countMenu == 1)
					{
						countMenu = 0;
						gotoXY(60, 10);
						SetColor(6);
						cout << "CLASSIC";
						SetColor(7);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(7);
						gotoXY(60, 12);
						cout << "QUIT";
					}
					else
					{
						countMenu = 1;
						gotoXY(60, 10);
						SetColor(7);
						cout << "CLASSIC";
						SetColor(6);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(7);
						gotoXY(60, 12);
						cout << "QUIT";
					}
				}
				else if (kiTu == 80) // di xuong
				{
					PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (countMenu == 0)
					{
						countMenu = 1;
						gotoXY(60, 10);
						SetColor(7);
						cout << "CLASSIC";
						SetColor(6);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(7);
						gotoXY(60, 12);
						cout << "QUIT";
					}
					else if (countMenu == 1)
					{
						countMenu = 2;
						gotoXY(60, 10);
						SetColor(7);
						cout << "CLASSIC";
						SetColor(7);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(6);
						gotoXY(60, 12);
						cout << "QUIT";
					}
					else
					{
						countMenu = 0;
						gotoXY(60, 10);
						SetColor(6);
						cout << "CLASSIC";
						SetColor(7);
						gotoXY(60, 11);
						cout << "MODERN";
						SetColor(7);
						gotoXY(60, 12);
						cout << "QUIT";
					}
				}
			}
			else if (kiTu == (int)'n')
			{
				PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
				if (countMenu == 0)
				{
					SetColor(7);
					system("cls");
					Level(0, play);
					return;
				}
				else if (countMenu == 1)
				{
					SetColor(7);
					system("cls");
					Level(1, play);
					return;
				}
				else
				{
					play = 0;
					return;
				}
			}
		}
	}
}
void Snake::Play(int level)
{
	bool gameover = false;
	score = 0;
	Nocursortype();
	srand(time(NULL));
	int x = rand() % (60 - 15 + 1) + 15;
	int y = rand() % (21 - 5 + 1) + 5;
	int xM = 0, yM = 0;
	int X[100], Y[100];
	Init(X, Y, x, y);
	DrawAllLine();
	gotoXY(82, 6);
	cout << "Score: " << score;
	gotoXY(82, 1);
	cout << " - Use arrow keys to move";
	gotoXY(82, 2);
	cout << " - Press P to pause";
	gotoXY(82, 3);
	cout << " - Press R to countinue";
	gotoXY(82, 4);
	cout << " - Press Q to quit";
	DrawSnake(X, Y);
	CreateDollar(xM, yM, X, Y);
	int check = 2;
	int oldCheck = -1;
	char kiTu;
	while (gameover == false)
	{
		DeleteData(X, Y);

		if (_kbhit())
		{
			kiTu = _getch();
			if (kiTu == -32)
			{
				kiTu = _getch();
				if (kiTu == 72 && check != 0) // di len
				{
					check = 1;
				}
				else if (kiTu == 80 && check != 1) // di xuong
				{
					check = 0;
				}
				else if (kiTu == 75 && check != 2) // sang trai
				{
					check = 3;
				}
				else if (kiTu == 77 && check != 3) // sang phai
					check = 2;
			}
			else if (kiTu == (int)'p' && oldCheck == -1)
			{
				oldCheck = check;
				check = 4;
				gotoXY(82, 5);
				cout << "Paused";
			}
			else if (kiTu == (int)'r' && oldCheck != -1)
			{
				check = oldCheck;
				oldCheck = -1;
				gotoXY(82, 5);
				cout << "      ";
			}
			else if (kiTu == (int)'q')
			{
				return;
			}
		}
		if (check == 0) // di xuong
		{
			y++;
		}
		else if (check == 1) // di len
		{
			y--;
		}
		else if (check == 2) // sang phai
		{
			x++;
		}
		else if (check == 3) // sang trai
		{
			x--;
		}
		Processing(X, Y, x, y, xM, yM, check);
		if (IsGameOver(X[0], Y[0]) == true || IsSnakeTouchBody(X, Y) == true)
		{
			PlaySound(TEXT("Sound/endGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gameover = true;
			gotoXY(82, 5);
			cout << "Game over";
			gotoXY(82, 7);
			cout << "Exiting...";
			Sleep(3000);
		}
		if (check == 1 || check == 0)
		{
			Sleep(level);
		}
		else
			Sleep(level / 2);
	}
}
void Snake::PlayModern(int level)
{
	bool gameover = false;
	score = 0;
	Nocursortype();
	srand(time(NULL));
	int x = rand() % (60 - 15 + 1) + 15;
	int y = rand() % (21 - 5 + 1) + 5;
	int xM = 0, yM = 0;
	int X[100], Y[100];
	Init(X, Y, x, y);
	DrawAllLine();
	gotoXY(82, 6);
	cout << "Score: " << score;
	gotoXY(82, 1);
	cout << " - Use arrow keys to move";
	gotoXY(82, 2);
	cout << " - Press P to pause";
	gotoXY(82, 3);
	cout << " - Press R to countinue";
	gotoXY(82, 4);
	cout << " - Press Q to quit";
	DrawSnake(X, Y);
	CreateDollar(xM, yM, X, Y);
	int check = 2;
	int oldCheck = -1;
	char kiTu;
	while (gameover == false)
	{
		DeleteData(X, Y);

		if (_kbhit())
		{
			kiTu = _getch();
			if (kiTu == -32)
			{
				kiTu = _getch();
				if (kiTu == 72 && check != 0) // di len
				{
					check = 1;
				}
				else if (kiTu == 80 && check != 1) // di xuong
				{
					check = 0;
				}
				else if (kiTu == 75 && check != 2) // sang trai
				{
					check = 3;
				}
				else if (kiTu == 77 && check != 3) // sang phai
					check = 2;
			}
			else if (kiTu == (int)'p' && oldCheck == -1)
			{
				oldCheck = check;
				check = 4;
				gotoXY(82, 5);
				cout << "Paused";
			}
			else if (kiTu == (int)'r' && oldCheck != -1)
			{
				check = oldCheck;
				oldCheck = -1;
				gotoXY(82, 5);
				cout << "      ";
			}
			else if (kiTu == (int)'q')
			{
				return;
			}
		}
		if (check == 0) // di xuong
		{
			y++;
			if (y == 26)
				y = 2;
		}
		else if (check == 1) // di len
		{
			y--;
			if (y == 1)
				y = 25;
		}
		else if (check == 2) // sang phai
		{
			x++;
			if (x == 80)
				x = 11;
		}
		else if (check == 3) // sang trai
		{
			x--;
			if (x == 10)
				x = 79;
		}
		Processing(X, Y, x, y, xM, yM, check);
		if (IsSnakeTouchBody(X, Y) == true)
		{
			PlaySound(TEXT("Sound/endGame.wav"), NULL, SND_FILENAME | SND_ASYNC);
			gameover = true;
			gotoXY(82, 5);
			cout << "Game over";
			gotoXY(82, 7);
			cout << "Exiting...";
			Sleep(3000);
		}
		if (check == 1 || check == 0)
		{
			Sleep(level);
		}
		else
			Sleep(level / 2);
	}
}
void Snake::DrawTopLine()
{
	int x = 10, y = 1;
	while (x < 80)
	{
		gotoXY(x, y);
		cout << "+";
		x++;
		Sleep(5);
	}
}
void Snake::DrawBotLine()
{
	int x = 80, y = 26;
	while (x > 10)
	{
		gotoXY(x, y);
		cout << "+";
		x--;
		Sleep(5);
	}
}
void Snake::DrawLeftLine()
{
	int x = 10, y = 26;
	while (y >= 1)
	{
		gotoXY(x, y);
		cout << "+";
		y--;
		Sleep(5);
	}
}
void Snake::DrawRightLine()
{
	int x = 80, y = 1;
	while (y <= 26)
	{
		gotoXY(x, y);
		cout << "+";
		y++;
		Sleep(5);
	}
}
void Snake::DrawAllLine()
{
	DrawTopLine();
	DrawRightLine();
	DrawBotLine();
	DrawLeftLine();

}
void Snake::DrawSnake(int X[], int Y[])
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(X[i], Y[i]);
		if (i == 0)
		{
			cout << "0";
		}
		else
		{
			cout << "o";
		}
	}
}
void Snake::DeleteData(int X[], int Y[])
{
	for (int i = 0; i < length; i++)
	{
		gotoXY(X[i], Y[i]);
		cout << " ";
	}
}
void Snake::Init(int X[], int Y[], int x, int y)
{
	for (int i = 0; i < length; i++)
	{
		X[i] = x;
		Y[i] = y;
		x--;
	}
}
void Snake::Processing(int X[], int Y[], int xx, int yy, int& x0, int& y0, int check)
{
	if (check != 4)
	{
		Add(X, xx);
		Add(Y, yy);
		if (IsSnakeEatDollar(x0, y0, X, Y) == false)
		{
			Delete(X, length - 1);
			Delete(Y, length - 1);
		}
		else
		{
			PlaySound(TEXT("Sound/eatFood.wav"), NULL, SND_FILENAME | SND_ASYNC);
			CreateDollar(x0, y0, X, Y);
			score += 10;
			gotoXY(82, 6);
			SetColor(oldColor);
			cout << "Score: " << score;
			length--;
		}
	}
	SetColor(oldColor);
	DrawSnake(X, Y);
}
void Snake::Add(int a[], int k)
{
	for (int i = length; i > 0; i--)
	{
		a[i] = a[i - 1];
	}
	a[0] = k;
	length++;
}
void Snake::Delete(int a[], int vt)
{
	for (int i = vt; i < length; i++)
	{
		a[i] = a[i + 1];
	}
	length--;
}
bool Snake::IsGameOver(int x0, int y0)
{
	if (y0 == 1 && (x0 >= 10 && x0 <= 80))
	{
		return true;
	}
	else if (y0 == 26 && (x0 >= 10 && x0 <= 80))
	{
		return true;
	}
	else if (x0 == 10 && (y0 >= 1 && y0 <= 26))
	{
		return true;
	}
	else if (x0 == 80 && (y0 >= 1 && y0 <= 26))
	{
		return true;
	}
	return false;
}
bool Snake::IsSnakeTouchBody(int X[], int Y[])
{
	for (int i = 1; i < length; i++)
	{
		if ((X[0] == X[i]) && Y[0] == Y[i])
			return true;
	}
	return false;
}
void Snake::CreateDollar(int& x0, int& y0, int X[], int Y[])
{
	do
	{
		//11 <= x0 <= 79
		x0 = rand() % (79 - 11 + 1) + 11;
		//2 <= y0 <= 25
		y0 = rand() % (25 - 2 + 1) + 2;
	} while (IsSnakeOnDollar(X, Y, x0, y0) == true);
	oldColor = color;
	color = rand() % (15 - 1 + 1) + 1;
	SetColor(color);
	gotoXY(x0, y0);
	cout << "$";
	SetColor(7);//mau trang
}
bool Snake::IsSnakeOnDollar(int X[], int Y[], int x0, int y0)
{
	for (int i = 0; i < length; i++)
	{
		if ((x0 == X[i]) && (y0 == Y[i]))
			return true;
	}
	return false;
}
bool Snake::IsSnakeEatDollar(int& x0, int& y0, int X[], int Y[])
{
	if (x0 == X[0] && y0 == Y[0])
	{
		return true;
	}
	return false;
}
void Snake::gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void Snake::SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Snake::Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void Snake::Level(int type, int &play)
{
	system("cls");
	int countMenu = 0;
	gotoXY(60, 10);
	SetColor(6);
	cout << "LEVEL 1";
	SetColor(7);
	gotoXY(60, 11);
	cout << "LEVEL 2";
	gotoXY(60, 12);
	cout << "LEVEL 3";
	gotoXY(60, 13);
	cout << "LEVEL 4";
	gotoXY(60, 14);
	cout << "LEVEL 5";
	gotoXY(60, 15);
	cout << "RETURN";
	char kiTu;
	while (true)
	{
		if (_kbhit())
		{
			kiTu = _getch();
			if (kiTu == -32)
			{
				kiTu = _getch();
				if (kiTu == 72) // di len
				{
					PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (countMenu == 0)
					{
						countMenu = 5;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						SetColor(6);
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 1)
					{
						countMenu = 0;
						gotoXY(60, 10);
						SetColor(6);
						cout << "LEVEL 1";
						SetColor(7);
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 2)
					{
						countMenu = 1;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						SetColor(6);
						gotoXY(60, 11);
						cout << "LEVEL 2";
						SetColor(7);
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 3)
					{
						countMenu = 2;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						SetColor(6);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						SetColor(7);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 4)
					{
						countMenu = 3;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						SetColor(6);
						cout << "LEVEL 4";
						SetColor(7);
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else
					{
						countMenu = 0;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						SetColor(6);
						gotoXY(60, 14);
						cout << "LEVEL 5";
						SetColor(7);
						gotoXY(60, 15);
						cout << "RETURN";
					}
				}
				else if (kiTu == 80) // di xuong
				{
					PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
					if (countMenu == 0)
					{
						countMenu = 1;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						SetColor(6);
						gotoXY(60, 11);
						cout << "LEVEL 2";
						SetColor(7);
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 1)
					{
						countMenu = 2;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						SetColor(6);
						gotoXY(60, 12);
						cout << "LEVEL 3";
						SetColor(7);
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 2)
					{
						countMenu = 3;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						SetColor(6);
						gotoXY(60, 13);
						cout << "LEVEL 4";
						SetColor(7);
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 3)
					{
						countMenu = 4;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						SetColor(6);
						gotoXY(60, 14);
						cout << "LEVEL 5";
						SetColor(7);
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else if (countMenu == 4)
					{
						countMenu = 5;
						gotoXY(60, 10);
						SetColor(7);
						cout << "LEVEL 1";
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						SetColor(6);
						gotoXY(60, 15);
						cout << "RETURN";
					}
					else
					{
						countMenu = 0;
						gotoXY(60, 10);
						SetColor(6);
						cout << "LEVEL 1";
						SetColor(7);
						gotoXY(60, 11);
						cout << "LEVEL 2";
						gotoXY(60, 12);
						cout << "LEVEL 3";
						gotoXY(60, 13);
						cout << "LEVEL 4";
						gotoXY(60, 14);
						cout << "LEVEL 5";
						gotoXY(60, 15);
						cout << "RETURN";
					}
				}
			}
			else if (kiTu == (int)'n')
			{
				PlaySound(TEXT("Sound/start.wav"), NULL, SND_FILENAME | SND_ASYNC);
				system("cls");
				if (countMenu == 0)
				{
					SetColor(7);
					system("cls");
					if (type == 0)
						Play(120);
					else
						PlayModern(120);
					return;
				}
				else if (countMenu == 1)
				{
					SetColor(7);
					system("cls");
					if (type == 0)
						Play(100);
					else
						PlayModern(100);
					return;
				}
				else if (countMenu == 2)
				{
					SetColor(7);
					system("cls");
					if (type == 0)
						Play(80);
					else
						PlayModern(80);
					return;
				}
				else if (countMenu == 3)
				{
					SetColor(7);
					system("cls");
					if (type == 0)
						Play(60);
					else
						PlayModern(60);
					return;
				}
				else if (countMenu == 4)
				{
					SetColor(7);
					system("cls");
					if (type == 0)
						Play(40);
					else
						PlayModern(40);
					return;
				}
				else
				{
					return;
				}
			}
		}
	}
}

