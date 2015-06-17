#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;

#define STAY -1
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define COMOARA 'c'
#define WUMBUS 'w'
#define ZID 'z'
#define GOL 'o'
#define VT 'v'

// nivele de feromon
#define F1 '1'
#define F2 '2'
#define F3 '3'
#define F4 '4'
#define F5 '5'
#define F6 '6'
#define F7 '7'
#define F8 '8'

#define F_SIZE_I 15
#define F_SIZE_J 15     // 22
#define Cell_SIZE 35

#define BKC LIGHTGREEN
#define FEC LIGHTBLUE
#define DONT -999

#define EvaporationRate 7

#define startI 13
#define startJ 9

int dim_x = F_SIZE_J * Cell_SIZE;
int dim_y = F_SIZE_I * Cell_SIZE;

// harta campului de joc
char field[F_SIZE_I][F_SIZE_J];
float pheromone[F_SIZE_I][F_SIZE_J];
int pheromoneTimer[F_SIZE_I][F_SIZE_J];

void InitialisePheromone()
{
	for (int k = 0; k < F_SIZE_I; ++k)
	{
		for (int h = 0; h < F_SIZE_J; ++h)
		{
			if (field[k][h] == COMOARA || field[k][h] == ZID || field[k][h] == WUMBUS)
			{
				pheromone[k][h]	= 8888;	
			}
			else
			{
				pheromone[k][h] = 1;
				pheromoneTimer[k][h] = 0;	
			}
		}		
	}	
}

void DrawCell(int j, int i, char continut);

void EvaporatePheromone()
{
	for (int k = 0; k < F_SIZE_I; ++k)
	{
		for (int h = 0; h < F_SIZE_J; ++h)
		{
			bool update = false;
			pheromoneTimer[k][h]--;
			if (field[k][h] == COMOARA || field[k][h] == ZID || field[k][h] == WUMBUS)
			{
			    // leave it
			}
			else
			{
				if (pheromoneTimer[k][h] == 1)
				{
					pheromone[k][h] -= 0.04;
					if (pheromone[k][h] < 1)
					{
						pheromone[k][h] = 1;
					}
					pheromoneTimer[k][h] = EvaporationRate;
					update = true;	
				}
			}
			
			if (update)
			{
				if (pheromone[k][h] == 8888)
				{
					// leave it as is
				}
				else if (pheromone[k][h] >= 1.01f && pheromone[k][h] < 1.1f)
				{
					field[k][h] = F1;	
				}
				else if (pheromone[k][h] >= 1.1f && pheromone[k][h] < 1.2f)
				{
					field[k][h] = F2;	
				}
				else if (pheromone[k][h] >= 1.2f && pheromone[k][h] < 1.3f)
				{
					field[k][h] = F3;	
				}
				else if (pheromone[k][h] >= 1.3f && pheromone[k][h] < 1.4f)
				{
					field[k][h] = F4;	
				}
				else if (pheromone[k][h] >= 1.4f && pheromone[k][h] < 1.5f)
				{
					field[k][h] = F5;	
				}
				else if (pheromone[k][h] >= 1.5f && pheromone[k][h] < 1.6f)
				{
					field[k][h] = F6;	
				}
				else if (pheromone[k][h] >= 1.6f && pheromone[k][h] < 1.7f)
				{
					field[k][h] = F7;	
				}
				else if (pheromone[k][h] >= 1.7f && pheromone[k][h] < 1.8f)
				{
					field[k][h] = F8;	
				}
				else if (pheromone[k][h] == 1)
				{
					field[k][h] = GOL;	
				}
				DrawCell(k, h, field[k][h]);
			}
		}
	}	
}

bool LoadMap()
{
	ifstream map("map.txt");
	if (map)
	{	
		for (int i = 0; i < F_SIZE_I; ++i)
		{
			for (int j = 0; j < F_SIZE_J; ++j)
			{
				map >> field[i][j];
			}	
		}
		map.close();
		return true;		
	}
	return false;
}

typedef struct Tabu
{
	int i;
	int j;
};

// Vanator stie pozitia pe campul de joc a vanatorului
struct Vanator
{
	int i;
	int j;
	
	int vizit[F_SIZE_I][F_SIZE_J];
	
	Tabu tabu[900];
	int nrMutari;
	float nrMF;
	bool goingBack;
	
	Vanator()
	{
		i = startI;
		j = startJ;
		nrMutari = 0;
		goingBack = false;
		
		for (int k = 0; k < F_SIZE_I; ++k)
		{
			for (int h = 0; h < F_SIZE_J; ++h)
			{
				if (field[k][h] == ZID || field[k][h] == WUMBUS)
				{
					vizit[k][h] = DONT;
				}
				else
				{
					vizit[k][h] = 0;		
				}
			}	
		}
		vizit[i][j]++;
		tabu[nrMutari].i = i;
		tabu[nrMutari].j = j;
		nrMutari++;
	}
	void ResetPos()
	{
		i = startI;
		j = startJ;
		nrMutari = 0;
		goingBack = false;
		
		for (int k = 0; k < F_SIZE_I; ++k)
		{
			for (int h = 0; h < F_SIZE_J; ++h)
			{
				if (field[k][h] == ZID || field[k][h] == WUMBUS)
				{
					vizit[k][h] = DONT;
				}
				else
				{
					vizit[k][h] = 0;		
				}
			}	
		}
		vizit[i][j]++;
		tabu[nrMutari].i = i;
		tabu[nrMutari].j = j;
		nrMutari++;
	}
	void DropPheromone()
	{
		pheromone[i][j] += (1/nrMF); // - (vizit[i][j]/1000)
		pheromoneTimer[i][j] = EvaporationRate;
		if (pheromone[i][j] == 8888)
		{
			// leave it as is
		}
		else if (pheromone[i][j] >= 1.01f && pheromone[i][j] < 1.1f)
		{
			field[i][j] = F1;	
		}
		else if (pheromone[i][j] >= 1.1f && pheromone[i][j] < 1.2f)
		{
			field[i][j] = F2;	
		}
		else if (pheromone[i][j] >= 1.2f && pheromone[i][j] < 1.3f)
		{
			field[i][j] = F3;	
		}
		else if (pheromone[i][j] >= 1.3f && pheromone[i][j] < 1.4f)
		{
			field[i][j] = F4;	
		}
		else if (pheromone[i][j] >= 1.4f && pheromone[i][j] < 1.5f)
		{
			field[i][j] = F5;	
		}
		else if (pheromone[i][j] >= 1.5f && pheromone[i][j] < 1.6f)
		{
			field[i][j] = F6;	
		}
		else if (pheromone[i][j] >= 1.6f && pheromone[i][j] < 1.7f)
		{
			field[i][j] = F7;	
		}
		else if (pheromone[i][j] >= 1.7f && pheromone[i][j] < 1.8f)
		{
			field[i][j] = F8;	
		}
	}
	bool AtStart()
	{
		if (i == startI && j == startJ)
		{
			return true;	
		}
		return false;		
	}
	bool TreasureStatus(int direction)
	{
		if (direction == UP)
		{
			if (field[i - 1][j] == COMOARA)
			{
				return true;	
			}	
		}
		else if (direction == DOWN)
		{	
			if (field[i + 1][j] == COMOARA)
			{
				return true;	
			}
		}
		else if (direction == LEFT)
		{
			if (field[i][j - 1] == COMOARA)
			{
				return true;	
			}	
		}
		else if (direction == RIGHT)
		{
			if (field[i][j + 1] == COMOARA)
			{
				return true;	
			}	
		}
		return false;
	}
	int VizitStatus(int direction)
	{
		if (direction == UP)
		{
			return vizit[i - 1][j];	
		}
		else if (direction == DOWN)
		{
			return vizit[i + 1][j];	
		}
		else if (direction == LEFT)
		{
			return vizit[i][j - 1];	
		}
		else if (direction == RIGHT)
		{
			return vizit[i][j + 1];
		}
	}
	float PheromoneStatus(int direction)
	{
		if (direction == UP)
		{
			return pheromone[i - 1][j];	
		}
		else if (direction == DOWN)
		{
			return pheromone[i + 1][j];	
		}
		else if (direction == LEFT)
		{
			return pheromone[i][j - 1];	
		}
		else if (direction == RIGHT)
		{
			return pheromone[i][j + 1];
		}
	}
};

void HideConsole()
{
	HWND hWnd = GetConsoleWindow(); 
	ShowWindow( hWnd, SW_HIDE );	
}

void DrawWindow()
{
	initwindow(dim_x, dim_y, "Creier de Furnica", 10, 10);
	setbkcolor(BKC);
	cleardevice();	
}

void EraseWindow()
{
	closegraph();
}

void DrawCell(int j, int i, char continut)
{
	int x = i * Cell_SIZE;
	int y = j * Cell_SIZE;
	
	if (continut == GOL)
	{
		setcolor(BKC);
		for (int k = 0; k < Cell_SIZE; k++)
		{
			line (x, y + k, x + Cell_SIZE - 1, y + k);
		}
	}
	else if (continut == WUMBUS)
	{
		setcolor(BLACK);
		setbkcolor(LIGHTBLUE);
		setfillstyle(EMPTY_FILL, YELLOW);
		fillellipse(x + Cell_SIZE/2, y + Cell_SIZE - Cell_SIZE/4 + 1, Cell_SIZE/4 - 3, Cell_SIZE/4 - 3);
		
		setbkcolor(BLUE);
		setfillstyle(CLOSE_DOT_FILL, WHITE);
		fillellipse(x + Cell_SIZE/2, y + Cell_SIZE/2 - 1, Cell_SIZE/2 - 7, Cell_SIZE/2 - 8);
	}
	else if (continut == ZID)
	{
		setcolor(BLACK);
		setbkcolor(BROWN);
		setfillstyle(EMPTY_FILL, YELLOW);
		fillellipse(x + Cell_SIZE/2, y + Cell_SIZE - Cell_SIZE/4 - 1, Cell_SIZE/4 - 1, Cell_SIZE/4 - 1);
		
		setbkcolor(GREEN);
		setfillstyle(CLOSE_DOT_FILL, YELLOW);
		fillellipse(x + Cell_SIZE/2, y + Cell_SIZE/2 - 4, Cell_SIZE/2 - 3, Cell_SIZE/2 - 5);		
	}
	else  if (continut == COMOARA)
	{
		setbkcolor(LIGHTBLUE);
		setcolor(WHITE);
		setfillstyle(LTSLASH_FILL, WHITE);
		fillellipse(x + Cell_SIZE/2, y + Cell_SIZE/2, Cell_SIZE/2 - 1, Cell_SIZE/2 - 1);	
	}
	else if (continut == VT)
	{
		setbkcolor(BLACK);
		setcolor(BLACK);
		
		setfillstyle(SOLID_FILL, BROWN);
		fillellipse(x + Cell_SIZE/2 - 3, y + 29, 3, 3);
		fillellipse(x + Cell_SIZE/2 + 3, y + 29, 3, 3);
		
		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(x + Cell_SIZE/2, y + 7, 5, 5);
		
		setfillstyle(SOLID_FILL, LIGHTRED);
		fillellipse(x + Cell_SIZE/2, y + 19, 9, 9);
	}
	else if (continut == F1)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 10, y + 10, x + Cell_SIZE - 1 - 10, y + 10, x + Cell_SIZE - 1 - 10, y + Cell_SIZE - 1 - 10, x + 10, y + Cell_SIZE - 1 - 10, x + 10, y + 10};
		fillpoly(5, points);
	}
	else if (continut == F2)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 9, y + 9, x + Cell_SIZE - 1 - 9, y + 9, x + Cell_SIZE - 1 - 9, y + Cell_SIZE - 1 - 9, x + 9, y + Cell_SIZE - 1 - 9, x + 9, y + 9};
		fillpoly(5, points);
	}
	else if (continut == F3)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 8, y + 8, x + Cell_SIZE - 1 - 8, y + 8, x + Cell_SIZE - 1 - 8, y + Cell_SIZE - 1 - 8, x + 8, y + Cell_SIZE - 1 - 8, x + 8, y + 8};
		fillpoly(5, points);
	}
	else if (continut == F4)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 7, y + 7, x + Cell_SIZE - 1 - 7, y + 7, x + Cell_SIZE - 1 - 7, y + Cell_SIZE - 1 - 7, x + 7, y + Cell_SIZE - 1 - 7, x + 7, y + 7};
		fillpoly(5, points);
	}
	else if (continut == F5)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 6, y + 6, x + Cell_SIZE - 1 - 6, y + 6, x + Cell_SIZE - 1 - 6, y + Cell_SIZE - 1 - 6, x + 6, y + Cell_SIZE - 1 - 6, x + 6, y + 6};
		fillpoly(5, points);
	}
	else if (continut == F6)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, FEC);
		int points[] = { x + 5, y + 5, x + Cell_SIZE - 1 - 5, y + 5, x + Cell_SIZE - 1 - 5, y + Cell_SIZE - 1 - 5, x + 5, y + Cell_SIZE - 1 - 5, x + 5, y + 5};
		fillpoly(5, points);
	}
	else if (continut == F7)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, BLACK);
		int points[] = { x + 4, y + 4, x + Cell_SIZE - 1 - 4, y + 4, x + Cell_SIZE - 1 - 4, y + Cell_SIZE - 1 - 4, x + 4, y + Cell_SIZE - 1 - 4, x + 4, y + 4};
		fillpoly(5, points);
	}
	else if (continut == F8)
	{
		setbkcolor(BKC);
		setcolor(BKC);
		setfillstyle(CLOSE_DOT_FILL, BLACK);
		int points[] = { x + 3, y + 3, x + Cell_SIZE - 1 - 3, y + 3, x + Cell_SIZE - 1 - 3, y + Cell_SIZE - 1 - 3, x + 3, y + Cell_SIZE - 1 - 3, x + 3, y + 3};
		fillpoly(5, points);
	}
}

int ChooseMove(Vanator &v)
{
	if (!v.goingBack)
	{
		int availableMove[4];
		int nrAvailableMoves = 0;
	
		if (v.VizitStatus(UP) != DONT)
		{	
			availableMove[nrAvailableMoves] = UP;
			nrAvailableMoves++;
		}
		if (v.VizitStatus(DOWN) != DONT)
		{
			availableMove[nrAvailableMoves] = DOWN; 
			nrAvailableMoves++;
		}
		if (v.VizitStatus(LEFT) != DONT)
		{
			availableMove[nrAvailableMoves] = LEFT;
			nrAvailableMoves++;	
		}
		if (v.VizitStatus(RIGHT) != DONT)
		{
			availableMove[nrAvailableMoves] = RIGHT;
			nrAvailableMoves++;	
		}
	
		// make decision
		if (nrAvailableMoves > 0)
		{	
			int unvisited[4];
			int nrUnvisited = 0;
			for (int k = 0; k < nrAvailableMoves; ++k)
			{
				if (v.VizitStatus(availableMove[k]) == 0)
				{
					unvisited[nrUnvisited++] = availableMove[k];
				}	
			}
			// Choose from unvisited
			if (nrUnvisited > 0)
			{
				float bestPheromone = v.PheromoneStatus(unvisited[0]);
				for (int k = 0; k < nrUnvisited - 1; ++k)
				{
					for (int h = k + 1; h < nrUnvisited; ++h)
					{
						if (v.PheromoneStatus(unvisited[k]) < v.PheromoneStatus(unvisited[h]))
						{
							swap(unvisited[k], unvisited[h]);	
						}
					}	
				}
				bestPheromone = v.PheromoneStatus(unvisited[0]);
				int nrSame = 0;
				for (int k = 0; k < nrUnvisited; ++k)
				{
					if (v.PheromoneStatus(unvisited[k]) == bestPheromone)
					{
						nrSame++;	
					}
				}
				if (nrSame == 1)
				{
					return unvisited[0];		
				}
				else
				{
					return (unvisited[rand() % nrSame]);	
				}
			}
			// choose from visited
			else 
			{
				for (int k = 0; k < nrAvailableMoves - 1; ++k)
				{
					for (int h = k + 1; h < nrAvailableMoves; ++h)
					{
						if (v.VizitStatus(availableMove[k]) > v.VizitStatus(availableMove[h]))
						{
							swap (availableMove[k], availableMove[h]);
						}	
					}
				}
			
				bool rem = false;
				int remove;
				for (int k = 0; k < nrAvailableMoves; ++k)
				{
					if (v.i - 1 == v.tabu[v.nrMutari - 2].i && v.j == v.tabu[v.nrMutari - 2].j)
					{
						rem = true;
						remove = UP;	
					}
					else if (v.i + 1 == v.tabu[v.nrMutari - 2].i && v.j == v.tabu[v.nrMutari - 2].j)
					{
						rem = true;
						remove = DOWN;	
					}
					else if (v.i == v.tabu[v.nrMutari - 2].i && v.j - 1 == v.tabu[v.nrMutari - 2].j)
					{
						rem = true;
						remove = LEFT;	
					}
					else if (v.i == v.tabu[v.nrMutari - 2].i && v.j + 1 == v.tabu[v.nrMutari - 2].j)
					{
						rem = true;
						remove = RIGHT;	
					}
				}
			
				if (rem == true)
				{
					int rr;
					for (int k = 0; k < nrAvailableMoves; ++k)
					{
						if (availableMove[k] == remove)
						{
							rr = k;
						}
					}
					nrAvailableMoves--;
					for (int k = rr; k < nrAvailableMoves; ++k)
					{
						availableMove[k] = availableMove[k + 1];	
					}
				}
			
				int bestMove = availableMove[0];
				int nrSame = 0;
				for (int k = 0; k < nrAvailableMoves; ++k)
				{
					nrSame++;	
				}
				if (nrSame > 1)
				{
					return availableMove[rand() % nrSame];	
				}
				else
				{
					return availableMove[0];	
				}
			}
		}
		else 
		{
			return STAY;	
		}			
	}
	else
	{
		v.nrMutari--;
		if (v.nrMutari >= 0)
		{
			if ( (v.tabu[v.nrMutari].i == (v.i - 1)) && (v.tabu[v.nrMutari].j == v.j) )
			{
				return UP;	
			}
			else if ( (v.tabu[v.nrMutari].i == (v.i + 1)) && (v.tabu[v.nrMutari].j == v.j) )
			{
				return DOWN;	
			}
			else if ( (v.tabu[v.nrMutari].i == v.i) && (v.tabu[v.nrMutari].j == (v.j - 1)) )
			{
				return LEFT;	
			}
			else if ( (v.tabu[v.nrMutari].i == v.i) && (v.tabu[v.nrMutari].j == (v.j + 1)) )
			{
				return RIGHT;	
			}
			else 
			{
				return STAY;	
			}	
		}
		else
		{
			v.ResetPos();
			DrawCell(v.i, v.j, VT);
			return 	ChooseMove(v);
		}
	}
}

void Move(Vanator &v, int direction)
{
	if (direction != STAY)
	{
		DrawCell(v.i, v.j, GOL);
		DrawCell(v.i, v.j, field[v.i][v.j]);
	
		if (v.TreasureStatus(direction))
		{
			v.goingBack = true;
			v.nrMF = v.nrMutari;
		}
		
		if (direction == UP)
		{	
			v.i--;	
		}
		else if (direction == DOWN)
		{	
			v.i++;	
		}
		else if (direction == LEFT)
		{		
			v.j--;
		}
		else if (direction == RIGHT)
		{	
			v.j++;
		}
		
		if (!v.goingBack)
		{
			if (!v.AtStart())
			{
				v.vizit[v.i][v.j]++;
				v.tabu[v.nrMutari].i = v.i;
				v.tabu[v.nrMutari].j = v.j;
				v.nrMutari++;	
			}
			else
			{
				v.ResetPos();	
			}	
		}
		else
		{
			v.DropPheromone();
		}
		DrawCell(v.i, v.j, GOL);
		DrawCell(v.i, v.j, field[v.i][v.j]);
		DrawCell(v.i, v.j, VT);
	}
}

int main()
{
	if (LoadMap())
	{
		srand ( (unsigned)time(0) );
		HideConsole();
	
		InitialisePheromone();
		Vanator v1;
		Vanator v2;
		Vanator v3;
		Vanator v4;
		Vanator v5;
		//Vanator v6;
		
		DrawWindow();
	
		for (int i = 0; i < F_SIZE_I; ++i)
		{
			for (int j = 0; j < F_SIZE_J; ++j)
			{
				DrawCell(i, j, field[i][j]);	
			}	
		}
		DrawCell(v1.i, v1.j, VT);
	
		delay(200);
		while (true)
		{
			Move(v1, ChooseMove(v1));
			Move(v2, ChooseMove(v2));
			Move(v3, ChooseMove(v3));
			Move(v4, ChooseMove(v4));
			Move(v5, ChooseMove(v5));
			//Move(v6, ChooseMove(v6));

			delay(10);
			EvaporatePheromone();	
		}
	
		//getch();
	
		EraseWindow();	
	}
	else
	{
		cout << "Nu am gasit fisierul 'map.txt'...";
		cin.get();
	}
	
	return 0;
}
