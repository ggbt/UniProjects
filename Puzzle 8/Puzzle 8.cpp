#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <graphics.h>
#include <stdlib.h>
#include <list>
#include <iostream>
#include <math.h>
#include <conio.h>
using namespace std;

const int LEFT = -1;
const int RIGHT = -2;
const int UP = -3;
const int DOWN = -4;

int positions[9], nrOfPos = 9;
short int movePosibilities = 0;
short int moveOrder[4];
int auxMove1[3][3];
int auxMove2[3][3];
int nrOfVisitedPos = 0;
int visitedPos[362880];
int solution[3][3];
int moves[362880];
int nrOfMoves = 0;
int startPos[3][3];
short int cellBack, cellBorder;

// pozitia casutei goale
struct emptyPos{
   int i;
   int j;   
};
emptyPos ePos;

int pop(int i){
   if (i == nrOfPos - 1){
      nrOfPos--;
      return positions[i];
   }
   else{
      int return_value = positions[i];
      for (int k = i; k < nrOfPos - 1; k++) 
         positions[k] = positions[k + 1];
      nrOfPos--;
      return return_value;
   }   
}

bool puzzle_rezolvabil(int field[3][3]){
   // raspandesc matricea intr-o lista pentru prelucrare usoara   
   int spreadField[9], index = 0;
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)         
         spreadField[index++] = field[i][j];
      
   int nrValidare = 0;
   for (int i = 0; i < 8; i++)
      for (int j = i + 1; j < 9; j++)
         if ( (spreadField[i] != 0) && (spreadField[i] > spreadField[j]) ) 
            nrValidare++;
   if (nrValidare % 2 == 0)
      return true;
   else
      return false;        
}

// numarul de cifre care sunt gresit pozitionate
int euristica1(int field[3][3]){
   short int pozCorecta = 1;
   int nrPozGresite = 0; 
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         if (field[i][j] != pozCorecta++)
            nrPozGresite++;
   return nrPozGresite;
}

// suma mutarilor necesare pentru ca toate cifrele sa ajunga la
// starea tinta ca si cum toate celelalte casute ar fi goale
int euristica2(int field[3][3]){
   int nrMutari = 0;
   for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
         if(field[i][j] == 1)
            nrMutari += abs(i - 0) + abs(j - 0);
         else if(field[i][j] == 2)
            nrMutari += abs(i - 0) + abs(j - 1);
         else if(field[i][j] == 3)
            nrMutari += abs(i - 0) + abs(j - 2);
         else if(field[i][j] == 4)
            nrMutari += abs(i - 1) + abs(j - 0);
         else if(field[i][j] == 5)
            nrMutari += abs(i - 1) + abs(j - 1);
         else if(field[i][j] == 6)
            nrMutari += abs(i - 1) + abs(j - 2);
         else if(field[i][j] == 7)
            nrMutari += abs(i - 2) + abs(j - 0);
         else if(field[i][j] == 8)
            nrMutari += abs(i - 2) + abs(j - 1);
         else 
            nrMutari += abs(i - 2) + abs(j - 2);    
   return nrMutari;  
}

bool isVisited(int pos){
   for (int i = 0; i < nrOfVisitedPos; i++)
      if (pos == visitedPos[i])
         return true; 
   return false;
}

class PuzzleField{
   public:
      int field[3][3];
      
      PuzzleField(){ 
         reGen();
      }
      
      void reGen(){
         nrOfVisitedPos = 0;
         do{
            // genereaza configuratie puzzle
            nrOfPos = 9;
            for (int i = 0; i < 9; i++)
               positions[i] = i;
            for (int i = 0; i < 3; i++)
               for (int j = 0; j < 3; j++)
                  field[i][j] = pop( rand() % nrOfPos );
         } while (!puzzle_rezolvabil(field));
         
         for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               if (field[i][j] == 0){
                  ePos.i = i;
                  ePos.j = j;
               }
               
         visitedPos[nrOfVisitedPos++] = toInt(field);
         for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               startPos[i][j] = field[i][j];         
      }
      
      int toInt(int field[3][3]){
         int ret = 0;
         
         if (field[0][0] == 0){
            ret = 9;
            ret *= 10;
            ret += field[0][1];
            ret *= 10;
            ret += field[0][2];
            for (int i = 1; i < 3; i++)
               for (int j = 0; j < 3; j++)
                  ret = ret * 10 + field[i][j];
         }
         else{
            for (int i = 0; i < 3; i++)
               for (int j = 0; j < 3; j++)
                  ret = ret * 10 + field[i][j];
         }
         
         return ret;         
      }

      void makeAuxMove1(int direction){
         for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               auxMove1[i][j] = field[i][j];
               
         if (direction == UP){
            int aux = auxMove1[ePos.i][ePos.j];
            auxMove1[ePos.i][ePos.j] = auxMove1[ePos.i - 1][ePos.j];
            auxMove1[ePos.i - 1][ePos.j] = aux;
         }
         else if (direction == DOWN){
            int aux = auxMove1[ePos.i][ePos.j];
            auxMove1[ePos.i][ePos.j] = auxMove1[ePos.i + 1][ePos.j];
            auxMove1[ePos.i + 1][ePos.j] = aux;
         }
         else if (direction == LEFT){
            int aux = auxMove1[ePos.i][ePos.j];
            auxMove1[ePos.i][ePos.j] = auxMove1[ePos.i][ePos.j - 1];
            auxMove1[ePos.i][ePos.j - 1] = aux;   
         }
         else if (direction == RIGHT){
            int aux = auxMove1[ePos.i][ePos.j];
            auxMove1[ePos.i][ePos.j] = auxMove1[ePos.i][ePos.j + 1];
            auxMove1[ePos.i][ePos.j + 1] = aux;             
         } 
      }
      
      void makeAuxMove2(int direction){
         for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               auxMove2[i][j] = field[i][j];
         if (direction == UP){
            int aux = auxMove2[ePos.i][ePos.j];
            auxMove2[ePos.i][ePos.j] = auxMove2[ePos.i - 1][ePos.j];
            auxMove2[ePos.i - 1][ePos.j] = aux;
         }
         else if (direction == DOWN){
            int aux = auxMove2[ePos.i][ePos.j];
            auxMove2[ePos.i][ePos.j] = auxMove2[ePos.i + 1][ePos.j];
            auxMove2[ePos.i + 1][ePos.j] = aux;
         }
         else if (direction == LEFT){
            int aux = auxMove2[ePos.i][ePos.j];
            auxMove2[ePos.i][ePos.j] = auxMove2[ePos.i][ePos.j - 1];
            auxMove2[ePos.i][ePos.j - 1] = aux;   
         }
         else if (direction == RIGHT){
            int aux = auxMove2[ePos.i][ePos.j];
            auxMove2[ePos.i][ePos.j] = auxMove2[ePos.i][ePos.j + 1];
            auxMove2[ePos.i][ePos.j + 1] = aux;             
         } 
      }
      
      int whereToMove(){
	     movePosibilities = 0;
	     for (int i = 0; i < 4; i++)
	        moveOrder[i] = 0;   
	     int auxField[3][3], direction = 0;
	     bool okToMove = false;

        if (ePos.i != 0){
            makeAuxMove1(UP);
            if (!isVisited(toInt(auxMove1))){
		          moveOrder[movePosibilities++] = UP;
		          okToMove = true;
            }
	     }
	     if (ePos.i != 2){
            makeAuxMove1(DOWN);
            if (!isVisited(toInt(auxMove1))){
		          moveOrder[movePosibilities++] = DOWN;
		          okToMove = true;
            }
	     }
	     if (ePos.j != 0){
            makeAuxMove1(LEFT);
            if (!isVisited(toInt(auxMove1))){ 
		          moveOrder[movePosibilities++] = LEFT;
		          okToMove = true;
            }
	     }
        if (ePos.j != 2){
            makeAuxMove1(RIGHT);
            if (!isVisited(toInt(auxMove1))){ 
		          moveOrder[movePosibilities++] = RIGHT;
		          okToMove = true;
            }
	     }
        
        if (movePosibilities > 1)
	     for (int i = 0; i < movePosibilities - 1; i++){
          makeAuxMove1(moveOrder[i]);
          makeAuxMove2(moveOrder[i + 1]);
		    if (euristica2(auxMove1) > euristica2(auxMove2)){
			   int aux = moveOrder[i];
			   moveOrder[i] = moveOrder[i + 1];
			   moveOrder[i + 1] = aux;
		    }	
	     }
	     if (okToMove)
          return moveOrder[direction];
        else{
          return 88; 
        }
      }

      bool move(int direction){
         if (direction == 88)
            return false;
            
         visitedPos[nrOfVisitedPos++] = toInt(field);
         
         int aux = field[ePos.i][ePos.j];
         if (direction == UP){
            field[ePos.i][ePos.j] = field[ePos.i - 1][ePos.j];
            field[ePos.i - 1][ePos.j] = aux;
            ePos.i--;
         }
         else if (direction == DOWN){
            field[ePos.i][ePos.j] = field[ePos.i + 1][ePos.j];
            field[ePos.i + 1][ePos.j] = aux;
            ePos.i++;
         }
         else if (direction == LEFT){
            field[ePos.i][ePos.j] = field[ePos.i][ePos.j - 1];
            field[ePos.i][ePos.j - 1] = aux;
            ePos.j--;
         }
         else if (direction == RIGHT){
            field[ePos.i][ePos.j] = field[ePos.i][ePos.j + 1];
            field[ePos.i][ePos.j + 1] = aux;
            ePos.j++;
         }
         return true;
      }
      
      bool rezolvat(){
         for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               if (field[i][j] != solution[i][j])
                  return false;
         return true;       
      }
};

void getEmptyPos(){
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         if (startPos[i][j] == 0){ 
            ePos.i = i;
            ePos.j = j;
         }
}

void drawCell(int x, int y, int nr, short int bkcolor, short int bordercolor){
   int X = x * 155 + 50;
   int Y = y * 155 + 50;

   if (nr == 0){
      setcolor(WHITE);
      for (int i = 0; i < 150; i++)
         line(Y, X + i, Y + 150, X + i);
      line(Y, X, Y + 150, X);
      line(Y + 150, X, Y + 150, X + 150);
      line(Y + 150, X + 150, Y, X + 150);
      line(Y, X + 150, Y, X);
   }
   else {
      setcolor(bkcolor);
      for (int i = 0; i < 150; i++)
         line(Y, X + i, Y + 150, X + i);
      
      setcolor (WHITE);
      setbkcolor (bkcolor);
      
      switch (nr) {
             case 1:
                  outtextxy(Y + 21, X + 14, "1");
                  break;    
             case 2:
                  outtextxy(Y + 21, X + 14, "2");
                  break;   
             case 3:
                  outtextxy(Y + 21, X + 14, "3");
                  break;   
             case 4:
                  outtextxy(Y + 21, X + 14, "4");
                  break;   
             case 5:
                  outtextxy(Y + 21, X + 14, "5");
                  break;   
             case 6:
                  outtextxy(Y + 21, X + 14, "6"); 
                  break;   
             case 7:
                  outtextxy(Y + 21, X + 14, "7"); 
                  break;   
             case 8:
                  outtextxy(Y + 21, X + 14, "8"); 
                  break;   
      }

      setcolor(bordercolor);
      line(Y, X, Y + 150, X);
      line(Y + 150, X, Y + 150, X + 150);
      line(Y + 150, X + 150, Y, X + 150);
      line(Y, X + 150, Y, X);
   }   
}

void moveCell(int direction){
   if (direction == UP){
      drawCell(ePos.i - 1, ePos.j, 0, WHITE, WHITE);
      drawCell(ePos.i, ePos.j, startPos[ePos.i - 1][ePos.j], cellBack, cellBorder);
      delay(100);
      int aux = startPos[ePos.i][ePos.j];
      startPos[ePos.i][ePos.j] = startPos[ePos.i - 1][ePos.j];
      startPos[ePos.i - 1][ePos.j] = aux;
      ePos.i--;
   } 
   else if (direction == DOWN){
      drawCell(ePos.i + 1, ePos.j, 0, WHITE, WHITE);
      drawCell(ePos.i, ePos.j, startPos[ePos.i + 1][ePos.j], cellBack, cellBorder);
      delay(100);
      int aux = startPos[ePos.i][ePos.j];
      startPos[ePos.i][ePos.j] = startPos[ePos.i + 1][ePos.j];
      startPos[ePos.i + 1][ePos.j] = aux;
      ePos.i++;
   }
   else if (direction == LEFT){
      drawCell(ePos.i, ePos.j - 1, 0, WHITE, WHITE);
      drawCell(ePos.i, ePos.j, startPos[ePos.i][ePos.j - 1], cellBack, cellBorder);
      delay(100);
      int aux = startPos[ePos.i][ePos.j];
      startPos[ePos.i][ePos.j] = startPos[ePos.i][ePos.j - 1];
      startPos[ePos.i][ePos.j - 1] = aux;
      ePos.j--;
   }
   else if (direction == RIGHT){
      drawCell(ePos.i, ePos.j + 1, 0, WHITE, WHITE);
      drawCell(ePos.i, ePos.j, startPos[ePos.i][ePos.j + 1], cellBack, cellBorder);
      delay(100);
      int aux = startPos[ePos.i][ePos.j];
      startPos[ePos.i][ePos.j] = startPos[ePos.i][ePos.j + 1];
      startPos[ePos.i][ePos.j + 1] = aux;
      ePos.j++;
   }   
}

int main(){
   
   srand((unsigned) (time(0)));
   
   short int backcolors[4] = {10, 12, 13, 9};
   short int bordercolors[4] = {2, 4, 5, 1};
   short int c = rand() % 4;
   cellBack = backcolors[c]; 
   cellBorder = bordercolors[c];
   
   solution[0][0] = 1;
   solution[0][1] = 2;
   solution[0][2] = 3;
   solution[1][0] = 4;
   solution[1][1] = 5;
   solution[1][2] = 6;
   solution[2][0] = 7;
   solution[2][1] = 8;
   solution[2][2] = 0;
   
   PuzzleField p;

   bool cont = true;
   nrOfMoves = 0;
   while (!p.rezolvat()){
      moves[nrOfMoves] = p.whereToMove();
      cont = p.move(moves[nrOfMoves++]);
      if (!cont){ 
         p.reGen();
         nrOfMoves = 0;
         moves[nrOfMoves] = p.whereToMove();
         cont = p.move(moves[nrOfMoves++]);
      }
   } 

   getEmptyPos();

   HWND hWnd = GetConsoleWindow(); 
   ShowWindow( hWnd, SW_HIDE );

   initwindow(560, 560, "Puzzle8", 40, 40);
   setbkcolor(WHITE);
   cleardevice();
   settextstyle(GOTHIC_FONT,HORIZ_DIR,10);
   
   setcolor(cellBack);

   for (int i = 0; i < 46; i += 2){
		line(i, i, 560 - i, i);
		line(560 - i, i, 560 - i, 560 - i);
		line(560 - i, 560 - i, i, 560 - i);
		line(i, 560 - i, i, i);
   }
   
   for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
         drawCell(i, j, startPos[i][j], cellBack, cellBorder);
   
   delay (1400);
   for (int i = 0; i < nrOfMoves; i++){
      moveCell(moves[i]); 
   }
   
   for (int i = 0; i < 3; i++){
      setcolor(WHITE);
         for (int i = 0; i < 46; i += 2){
		       line(i, i, 560 - i, i);
		       line(560 - i, i, 560 - i, 560 - i);
		       line(560 - i, 560 - i, i, 560 - i);
		       line(i, 560 - i, i, i);
		       delay(1);
         }
         setcolor(cellBack);
         for (int i = 46; i >= 0; i -= 2){
		       line(i, i, 560 - i, i);
		       line(560 - i, i, 560 - i, 560 - i);
		       line(560 - i, 560 - i, i, 560 - i);
		       line(i, 560 - i, i, i);
		       delay(1);
         }
   }

   getch();
   
   closegraph();
   return 0;   
}
