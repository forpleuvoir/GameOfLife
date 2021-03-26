#include <iostream>
#include <easyx.h>
#include "LifeGame.h"
#include <thread>
#include <conio.h>

#define random(x) rand() % x;

const int CELL_SIZE = 10;
const int WIDTH = 100;
const int HEIGHT = 80;
const int TPS = 50;
bool run = true;
int cell[WIDTH][HEIGHT] = { {0} };
int temp[WIDTH][HEIGHT] = { {0} };
MOUSEMSG msg;

int main()
{
	initWindows();
	initData();
	randomCell();
	std::thread gkp(getKeyPress);
	std::thread gm(getMouseMsg);
	start();
}

void start()
{
	while (true)
	{
		if (run)
		{
			Sleep(1000 / TPS);
			update();
		}
	}
}


void initWindows()
{
	initgraph(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE);
}

void getKeyPress()
{
	while (true)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 114:
				if (!run)
					randomCell();
				break;
			case 99:
				if (!run)
					initData();
				break;
			case 32:run = !run;
				break;
			}
		}
	}

}

void getMouseMsg()
{
	while (true)
	{
		if (!run)
		{
			msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				setCell(msg.x / CELL_SIZE, msg.y / CELL_SIZE, 1);
				break;
			case WM_RBUTTONDOWN:
				setCell(msg.x / CELL_SIZE, msg.y / CELL_SIZE, 0);
				break;
			}
		}
	}
}

void setCell(int x, int y, int tag)
{
	cell[x][y] = tag;
	draw();
	initTemp();
}

void randomCell()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			cell[i][j] = random(2);
		}
	}
	draw();
}

void update()
{
	initTemp();
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			updateCell(i, j, cell[i][j]);
		}
	}
	draw();
}

void draw()
{
	IMAGE img(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE);
	SetWorkingImage(&img);
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			drawCell(i, j, cell[i][j]);
		}
	}
	drawBackground();
	SetWorkingImage();
	putimage(0, 0, &img);
}

void drawCell(int x, int y, int tag)
{
	if (tag == 0)
	{
		setfillcolor(WHITE);
	}
	else if (tag == 1)
	{
		setfillcolor(BLACK);
	}
	fillrectangle((x * CELL_SIZE), (y * CELL_SIZE), (x * CELL_SIZE) + CELL_SIZE, (y * CELL_SIZE) + CELL_SIZE);
}

void drawBackground()
{
	setlinecolor(0xD3D3D3);
	for (int i = 0; i < WIDTH; i++)
	{
		line(i * CELL_SIZE, 0, i * CELL_SIZE, HEIGHT * CELL_SIZE);
	}
	for (int j = 0; j < HEIGHT; j++)
	{
		line(0, j * CELL_SIZE, WIDTH * CELL_SIZE, j * CELL_SIZE);
	}
}

void initData()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			cell[i][j] = 0;
		}
	}
	update();
}

void updateCell(int x, int y, int tag)
{
	int size = getCountOfSurroundingCells(x, y);
	if (tag == 0)
	{
		if (size == 3)
		{
			cell[x][y] = 1;
		}
	}
	else if (tag == 1)
	{
		if (size < 2)
		{
			cell[x][y] = 0;
		}
		if (size == 2 || size == 3)
		{
			cell[x][y] = 1;
		}
		if (size > 3)
		{
			cell[x][y] = 0;
		}
	}
}

int getCountOfSurroundingCells(int x, int y)
{
	int size = 0;
	if (x != 0) {
		if (y != 0)
			size += temp[x - 1][y - 1];
		if (y != HEIGHT - 1)
			size += temp[x - 1][y + 1];
		size += temp[x - 1][y];
	}
	if (x != WIDTH - 1) {
		if (y != 0)
			size += temp[x + 1][y - 1];
		if (y != HEIGHT - 1)
			size += temp[x + 1][y + 1];
		size += temp[x + 1][y];
	}
	if (y != 0)
		size += temp[x][y - 1];
	if (y != HEIGHT - 1)
		size += temp[x][y + 1];
	return size;
}

void initTemp()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			temp[i][j] = cell[i][j];
		}
	}
}