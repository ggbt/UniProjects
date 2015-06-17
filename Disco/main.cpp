#define _WIN32_WINNT 0x0500 // *hide console

#include <windows.h> // *hide console
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>  // puncte aleatorii
using namespace std;

#define Vector Punct
#define max(x, y) (x) > (y) ? (x) : (y)

int NrP = 6500;   // numarul de puncte implicit
int dim_x = 600;
int dim_y = 500;
int M = max(dim_x, dim_y);
short int switcheroo = 1;

struct Punct     // initializare, obligatoriu, cu pointer - Punct *numeVar;
{                // folosit si ca Vector
 	  int x;
 	  int y;
};

// initializare vector cu coordonatele puntelor, cu originea in 
// mijloc/stanga/dreapta/sus/jos in functie de change_origin 
void init(Punct* &p, const int &nr_puncte, short int change_origin = 0)
{
	switch (change_origin)
	{
		case 0:
 			p[0].x = dim_x/2;
			p[0].y = dim_y/2;
			break;       
		case 1:
			p[0].x = 20;
			p[0].y = dim_y/2;
			break;
		case 2:
			p[0].x = dim_x/2;
			p[0].y = dim_y - 20;
			break;
		case 3:
			p[0].x = dim_x - 20;
			p[0].y = dim_y/2;
			break;
		case 4:
			p[0].x = dim_x/2;
			p[0].y = 20;
			break;
	}

 	for (int i = 1; i < nr_puncte; i++)
 	{
	 	 p[i].x = 20 + rand() % (dim_x - 40);
	 	 p[i].y = 20 + rand() % (dim_y - 40); 
	}
}

float produs_scalar(Vector &u, Vector &v)
{
 		return (u.x * v.x + u.y * v.y);
}

// Toate cosinusurile sunt pozitive, chiar daca sunt negative
float cos_unghi(Vector &u, Vector &v)
{
    	float COS = ( produs_scalar(u,v) / sqrt( produs_scalar(u,u) * produs_scalar(v,v) ) );
		if (COS < 0) COS *= -1;
		return COS;   
}

void ordonare_cos(Punct* &p, const int &nr_puncte)  // ordonare dupa cosinus
{ 	  	  
        Punct plus = p[0];       // punct pe aceasi linie cu punctul de y min
 	  	plus.x += 1;				 
 	  	plus.x -= p[0].x;	                  // translatie cu p[0].x spre O(0,0)
 	  	plus.y -= p[0].y;				      // translatie cu p[0].y spre O(0,0)
 	  	  
 	  	float cos_values[nr_puncte];
 	  	  
 	  	Punct p_aux;
 	  	for (int i = 1; i < nr_puncte; i++)
 	  	{
		    p_aux = p[i];
		  	p_aux.x -= p[0].x;			   // translatie cu p[0].x spre O(0,0)
 	  	  	p_aux.y -= p[0].y;			   // translatie cu p[0].y spre O(0,0)
 	  	  	cos_values[i] = cos_unghi(plus, p_aux);
        }
        
        // ordonare - cos
        for (int i = 1; i < nr_puncte-1; i++)
        	for (int j = i + 1; j < nr_puncte; j++)
        		 if (cos_values[i] < cos_values[j])
        		 {
				  	 float temp = cos_values[i];
					 cos_values[i] = cos_values[j];
					 cos_values[j] = temp;		
						 	
					 Punct aux = p[i];
					 p[i] = p[j];
					 p[j] = aux;
				 }
}

void desen_puncte(Punct* &p, const int &nr_puncte, short int size, short int color)
{
 	  setcolor(color);
 	  
	  if (switcheroo == -1)
	  for (int i = 1; i < nr_puncte; i++)
		  for (int s = size; s > 0; s--)
	  			 circle (p[i].x, p[i].y, s);

	  if (switcheroo == 1)
	  for (int i = nr_puncte - 1; i > 0; i--)
		  for (int s = size; s > 0; s--)
	  			 circle (p[i].x, p[i].y, s);
}

void desen_puncte2(Punct* &p, const int &nr_puncte, short int size, short int color)
{
 	  setcolor(color);
 	  
	  if (switcheroo == -1)
	  for (int i = 1; i < nr_puncte/2; i++)
	  {
		  for (int s = size; s > 0; s--)
		  {
	  			 circle (p[i].x, p[i].y, s);
				 circle (p[nr_puncte - i].x, p[nr_puncte - i].y, s);
		  }
	  }

	  if (switcheroo == 1)
	  for (int i = (nr_puncte - 1)/2; i > 0; i--)
	  {
		  for (int s = size; s > 0; s--)
		  {
	  			 circle (p[i].x, p[i].y, s);
				 circle (p[nr_puncte - i].x, p[nr_puncte - i].y, s);
		  }
	  }
}

void desen_puncte3(Punct* &p, const int &nr_puncte, short int size, short int color)
{
 	  setcolor(color);
 	  
	  if (switcheroo == -1)
	  for (int i = 1; i < nr_puncte/4; i++)
	  {
	  		for (int s = size; s > 0; s--)
			{
	  			 circle (p[i].x, p[i].y, s);
				 circle (p[nr_puncte - i].x, p[nr_puncte - i].y, s);
				 circle (p[nr_puncte/2 + i].x, p[nr_puncte/2 + i].y, s);
				 circle (p[nr_puncte/2 - i].x, p[nr_puncte/2 - i].y, s);
			}	  			 
	  }

	  if (switcheroo == 1)
	  for (int i = (nr_puncte - 1)/4; i > 0; i--)
	  {
	  		for (int s = size; s > 0; s--)
			{
	  			 circle (p[i].x, p[i].y, s);
				 circle (p[nr_puncte - i].x, p[nr_puncte - i].y, s);
				 circle (p[nr_puncte/2 + i].x, p[nr_puncte/2 + i].y, s);
				 circle (p[nr_puncte/2 - i].x, p[nr_puncte/2 - i].y, s);
			}	  			 
	  }
}

void desen_raze(Punct* &p, const int &nr_puncte, short int color)
{
 	  setlinestyle(3, 0, 2);
	  setcolor(color);
	  
	  if (switcheroo == 1)
	  for (int i = 1; i < nr_puncte; i++)
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);

	  if (switcheroo == -1)
	  for (int i = nr_puncte - 1; i > 0; i--)
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);
}

void desen_raze2(Punct* &p, const int &nr_puncte, short int color)
{
 	  setlinestyle(3, 0, 2);
	  setcolor(color);

	  if (switcheroo == 1)
	  for (int i = 1; i < nr_puncte/2; i++)
	  {
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);
			line (p[0].x, p[0].y, p[nr_puncte - i].x, p[nr_puncte - i].y);
      }
      
	  if (switcheroo == -1)
	  for (int i = (nr_puncte - 1)/2; i > 0; i--)
	  {
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);
			line (p[0].x, p[0].y, p[nr_puncte - i].x, p[nr_puncte - i].y);
      }
}

void desen_raze3(Punct* &p, const int &nr_puncte, short int color)
{
 	  setlinestyle(3, 0, 2);
	  setcolor(color);

	  if (switcheroo == 1)
	  for (int i = 1; i < nr_puncte/4; i++)
	  {
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);
			line (p[0].x, p[0].y, p[nr_puncte/2 + i].x, p[nr_puncte/2 + i].y);
			line (p[0].x, p[0].y, p[nr_puncte/2 - i].x, p[nr_puncte/2 - i].y);
			line (p[0].x, p[0].y, p[nr_puncte - i].x, p[nr_puncte - i].y);
      }
      
	  if (switcheroo == -1)
	  for (int i = (nr_puncte - 1)/4; i > 0; i--)
	  {
	  		line (p[0].x, p[0].y, p[i].x, p[i].y);
			line (p[0].x, p[0].y, p[nr_puncte/2 + i].x, p[nr_puncte/2 + i].y);
			line (p[0].x, p[0].y, p[nr_puncte/2 - i].x, p[nr_puncte/2 - i].y);
			line (p[0].x, p[0].y, p[nr_puncte - i].x, p[nr_puncte - i].y);
      }
}

int main()
{   
    // ascunde cosola
	HWND hWnd = GetConsoleWindow(); 
	ShowWindow( hWnd, SW_HIDE );

	short int color = 9 , bkcolor = 1, change = 0, change_origin = 2;
   
	Punct *p;
    p = new Punct[NrP];

	init(p, NrP, change_origin);
	ordonare_cos(p,NrP);
   
    initwindow(dim_x,dim_y,"",20,20);
  
    do	
	{
	    setbkcolor(bkcolor);
		cleardevice();
		
		if(!change) 
		{
			switcheroo *= -1; 
			desen_puncte(p, NrP, 2, color); 
			desen_raze(p, NrP, color);
		}else
		if(change == 1 || change == -1 || change == -3) 
		{
			desen_puncte2(p, NrP, 2, color); 
			desen_raze2(p, NrP, color);
		}else
		if(change == 2 || change == -2) 
		{
			desen_puncte3(p, NrP, 2, color); 
			desen_raze3(p, NrP, color);
		}
		switcheroo *= -1;
		
		change_origin < 4 ? change_origin++ : change_origin = 1;
		init(p, NrP, change_origin);
		ordonare_cos(p, NrP);
		
		change < 2 ? change++ : change = -3;

		if (color == 14) color = 7;
		else if (color == 7) color = 9;
		else if (color < 14) color++;		 		

		if (bkcolor == 8) bkcolor = 1;
		else if (bkcolor < 6) bkcolor++;	
		else if (bkcolor == 6) bkcolor = 8;	

	} while ( !kbhit() );
	
	closegraph();
	return 0;
}
