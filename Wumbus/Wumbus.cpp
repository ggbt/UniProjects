#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <iostream>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define COMOARA 'c'
#define WUMBUS 'w'
#define ZID 'z'
#define GOL 'o'
#define VT 'v'
#define GLONT 'g'

#define F_SIZE 20 // dimensiunea campului de joc

int dim_x = 500;
int dim_y = 500;

char field[F_SIZE][F_SIZE];

class Vanator
{
public:
    int x;
    int y;
    int scor;
       
    Vanator(int x = 10, int y = 9, int scor = 0);
    void move(int direction);
    void shoot(int direction);
	void play(int NrTure = 20);
	void makeMap();
};

void makeCell(int corner_x, int corner_y)
{
	setcolor(BLACK);
	line(corner_x, corner_y, corner_x + 20, corner_y);
	line(corner_x + 20, corner_y, corner_x + 20, corner_y + 20);
	line(corner_x + 20, corner_y + 20, corner_x, corner_y + 20);
	line(corner_x, corner_y + 20, corner_x, corner_y);		
}

void fillCell(int corner_x, int corner_y, char continut = GOL)
{
	if (continut == GOL)
	{
		setcolor(WHITE);
		for (int i = 0; i < 19; i++)
		line(corner_x + i + 1, corner_y + 1, corner_x + i + 1, corner_y + 19);
	} else if (continut == GLONT)
	{
		setcolor(RED);
		for (int i = 0; i < 4; i++)
			circle(corner_x + 10, corner_y + 10, i);
	} else if (continut == ZID)
	{
        int randColor = rand() % 10 + 1;
		setcolor(randColor);
		for (int i = 0; i < 19; i++)
		line(corner_x + i + 1, corner_y + 1, corner_x + i + 1, corner_y + 19);
	} else if (continut == WUMBUS)
	{
		setcolor(WHITE);
		for (int i = 0; i < 19; i++)
		line(corner_x + i + 1, corner_y + 1, corner_x + i + 1, corner_y + 19);
		setcolor(GREEN);
		for (int i = 0; i < 4; i++)
			circle(corner_x + 11, corner_y + 6, i);
		for (int i = 0; i < 6; i++)
			circle(corner_x + 11, corner_y + 14, i);
	} else if (continut == COMOARA)
	{
		setcolor(WHITE);	
		for (int i = 0; i < 19; i++)
		line(corner_x + i + 1, corner_y + 1, corner_x + i + 1, corner_y + 19);
		setcolor(LIGHTRED);
		for (int i = 0; i < 8; i++)
			circle(corner_x + 11, corner_y + 11, i);
		setcolor(YELLOW);
		for (int i = 0; i < 5; i++)
			circle(corner_x + 11, corner_y + 9, i);
	} else if (continut == VT)
	{
		setcolor(WHITE);
		for (int i = 0; i < 19; i++)
			line(corner_x + i + 1, corner_y + 1, corner_x + i + 1, corner_y + 19);
		setcolor(LIGHTGRAY);
		for (int i = 0; i < 4; i++)
			circle(corner_x + 11, corner_y + 6, i);
		setcolor(LIGHTBLUE);
		for (int i = 0; i < 6; i++)
			circle(corner_x + 11, corner_y + 14, i);
	}		
}

void Vanator::makeMap()
{
	initwindow(dim_x + 1, dim_y + 1, "Wumbus", 500, 20);
	setbkcolor(WHITE);
	cleardevice();
	
	ifstream map("map.txt");
	for (int i = 0; i < F_SIZE; i++)
		for (int j = 0; j < F_SIZE; j++)
			map >> field[i][j];
			
	int randColor = rand() % 12 + 1;
    setcolor(randColor);
	for ( int i = 0; i < 48; i += 3)
	{
		line(i, i, dim_x - i, i);
		line(dim_x - i, i, dim_x - i, dim_y - i);
			line(dim_x - i - 1, i + 1, dim_x - i - 1, dim_y - i - 1);
		line(dim_x - i, dim_y - i, i, dim_y - i);
			line(dim_x - i - 1, dim_y - i - 1, i + 1, dim_y - i - 1);
		line(i, dim_y - i, i, i);
	}
	
	for (int i = 0; i < F_SIZE; i++)
		for (int j = 0; j < F_SIZE; j++)
			makeCell(j * 20 + 50, i * 20 + 50);
		
	for (int i = 0; i < F_SIZE; i++)
		for (int j = 0; j < F_SIZE; j++)
		{
			fillCell(j * 20 + 50, i * 20 + 50, field[i][j]);	
		}
	fillCell(y * 20 + 50, x * 20 + 50, VT);				
}

Vanator::Vanator(int abscisa, int ordonata , int punctaj)
{
    x = abscisa;
    y = ordonata;
    scor = punctaj;
}

void Vanator::move(int direction)
{
	if (direction == UP)
	{
		if ( (x == 0) || (field[x - 1][y] == ZID) )
		{ 
			scor -= 1;
			cout << "\nAm dat cu capul in zidul de sus!";
		}
		else if (field[x - 1][y] == WUMBUS)
		{	
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1000;
			x -= 1;
			cout << "\nAm intrat in barlogul Wumbusului.";
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x - 1][y] == COMOARA)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor += 100;
			x -= 1;
			field[x][y] = GOL; // COMOARA luata
			cout << "\nAm luat comoara.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x - 1][y] == GOL)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1;
			x -= 1;
			cout << "\nAm urcat.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
	}
	else if (direction == DOWN)	
	{
		if ( (x == F_SIZE - 1) || (field[x + 1][y] == ZID) )
		{
			scor -= 1;	
			cout << "\nAm dat cu capul in zidul de jos!";
		}
		else if (field[x + 1][y] == WUMBUS)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1000;
			x += 1;
			cout << "\nAm intrat in barlogul Wumbusului.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x + 1][y] == COMOARA)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor += 100;
			x += 1;
			field[x][y] = GOL; // COMOARA luata
			cout << "\nAm luat comoara.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x + 1][y] == GOL)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1;
			x += 1;
			cout << "\nAm coborat.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
	}
	else if (direction == LEFT)	
	{
		if ( (y == 0) || (field[x][y - 1] == ZID) )
		{
			scor -= 1;	
			cout << "\nAm dat cu capul in zidul din stanga!";
		}
		else if (field[x][y - 1] == WUMBUS)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1000;
			y -= 1;
			cout << "\nAm intrat in barlogul Wumbusului.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x][y - 1] == COMOARA)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor += 100;
			y -= 1;
			field[x][y] = GOL; // COMOARA luata
			cout << "\nAm luat comoara.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x][y - 1] == GOL)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1;
			y -= 1;
			cout << "\nAm mers in stanga.";
			fillCell(y * 20 + 50, x * 20 + 50, VT);	
		}	
	}
	else if (direction == RIGHT)	
	{
		if ( (y == F_SIZE - 1) || (field[x][y + 1] == ZID) )
		{
			scor -= 1;	
			cout << "\nAm dat cu capul in zidul din dreapta!";
		}
		else if (field[x][y + 1] == WUMBUS)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1000;
			y += 1;
			cout << "\nAm intrat in barlogul Wumbusului.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x][y + 1] == COMOARA)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor += 100;
			y += 1;
			field[x][y] = GOL; // COMOARA luata
			cout << "\nAm luat comoara.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
		else if (field[x][y + 1] == GOL)
		{
			fillCell(y * 20 + 50, x * 20 + 50, field[x][y]);
			scor -= 1;
			y += 1;
			cout << "\nAm mers in dreapta.";	
			fillCell(y * 20 + 50, x * 20 + 50, VT);
		}
	}	
}

void Vanator::shoot(int direction)
{
	scor -= 25;
	if (direction == UP)
	{
		cout << "in sus...";
		int glont = x - 1;
		while ( (field[glont][y] != ZID) && (glont >= 0) )
		{
			fillCell(y * 20 + 50, glont * 20 + 50, GLONT);
			delay(30);
			if (field[glont][y] == WUMBUS)
			{
				scor += 250;
				field[glont][y] = GOL;
				cout << " (Wumbus lovit)";
			}	
			fillCell(y * 20 + 50, glont * 20 + 50, field[glont][y]);
			glont--;
		} 	
	}
	if (direction == DOWN)
	{
		cout << "in jos...";
		int glont = x + 1;
		while ( (field[glont][y] != ZID) && (glont < F_SIZE) )
		{
			fillCell(y * 20 + 50, glont * 20 + 50, GLONT);
			delay(30);
			if (field[glont][y] == WUMBUS)
			{
				scor += 250;
				field[glont][y] = GOL;
				cout << " (Wumbus lovit)";
			}
			fillCell(y * 20 + 50, glont * 20 + 50, field[glont][y]);		
			glont++;
		} 	
	}
	if (direction == LEFT)
	{
		cout << "in stanga...";
		int glont = y - 1;
		while ( (field[x][glont] != ZID) && (glont >= 0) )
		{
			fillCell(glont * 20 + 50, x * 20 + 50, GLONT);
			delay(30);
			if (field[x][glont] == WUMBUS)
			{
				scor += 250;
				field[x][glont] = GOL;
				cout << " (Wumbus lovit)";
			}
			fillCell(glont * 20 + 50, x * 20 + 50, field[x][glont]);		
			glont--;
		} 	
	}
	if (direction == RIGHT)
	{
		cout << "in dreapta...";
		int glont = y + 1;
		while ( (field[x][glont] != ZID) && (glont < F_SIZE) )
		{
			fillCell(glont * 20 + 50, x * 20 + 50, GLONT);
			delay(30);
			if (field[x][glont] == WUMBUS)
			{
				scor += 250;
				field[x][glont] = GOL;
				cout << " (Wumbus lovit)";
			}
			fillCell(glont * 20 + 50, x * 20 + 50, field[x][glont]);	
			glont++;
		} 	
	}
}

void Vanator::play(int NrTure)
{
	makeMap();
	
	time_t t;
	srand((unsigned) (time(&t)));
	
	delay(500);
	while (true)
	{	
		int directie = rand() % 4;
		move(directie);

        delay(500);
		cout << endl << "Trag... ";
		directie = rand() % 4;
        shoot(directie);
		
		//NrTure--;
		cout <<  "\nscor curent: " << scor << "\n";
		
		delay(100);
	}
}

int main()
{	
  srand (time(0));
    
	Vanator player;
	player.play(300);
	
	cout << "\nGATA!\n";		
	cin.get();
	return 0;	
}
