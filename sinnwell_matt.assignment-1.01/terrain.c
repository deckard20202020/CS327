
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeTable(int table[21][80]) {

     int i, j;
     for (j = 0; j < 21; j++) {
       for (i = 0; i < 80; i++) {
             table[j][i] = 0;
         }
     }
}

void printTable(int table[21][80]) {

  int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      if (table[r][c] == -1) {
        printf("%%");
      } else if (table[r][c] == 1) {
	printf(":");
      } else if (table[r][c] == 2) {
	printf(".");
      } else if (table[r][c] == 3) {
	printf("#");
      } else if (table[r][c] == 4) {
	printf("M");
      } else if (table[r][c] == 5) {
	printf("C");
      } else {
        //printf("%d ", table[r][c]);
	printf("^");
      }
    }
    printf("\n");
  }
  printf("\n");

}

void addBoarder(int table[21][80]) {

    //boarder % = -1
  int r1, r2, c1, c2;

    //left side
    for (r1 = 0; r1 < 21; r1++) {
      table[r1][0] = -1;
    }
    //right side
    for (r2 = 0; r2 < 21; r2++) {
      table[r2][79] = -1;
    }
    //top
    for (c1 = 0; c1 < 80; c1++) {
      table[0][c1] = -1;
    }
    //bottom
    for (c2 = 1; c2 < 80; c2++) {
      table[20][c2] = -1;
    }
    
}

int getRandomNum(int n) {

  int r = rand() % n + 1;
  return r;
}

void growSeed(int table[21][80], int x, int y, int op) {

  // printf("%d\n", x);
  //printf("%d\n", y);
  //printf("%d\n", op);
  if ((x > 0) &&  (x < 21) && (y > 0) && (y < 80) && (table[x][y] == 0)) {
    table[x][y] = op;
  }
}

void growSeeds(int table[21][80], int tallGrassX1, int tallGrassY1, int tallGrassX2, int tallGrassY2, int clearingX1, int clearingY1, int clearingX2, int clearingY2){

  // int xChange;
  int dxdy;

  for (dxdy = 1; dxdy < 80; dxdy++) {
    //tallgrass1 = 1
    //up
    //printf("up\n");
    //printf("%d\n", tallGrassX1 - dxdy);
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1, 1);
    //up and right
    //printf("up and right\n");
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1 + dxdy, 1);
    //right
    //printf("right\n");
    growSeed(table, tallGrassX1, tallGrassY1 + dxdy, 1);
    //right and down
    //printf("right and down\n");
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1 + dxdy, 1);
    //down
    //printf("down\n");
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1, 1);
    //down and left
    //printf("down and left\n");
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1 - dxdy, 1);
    //left
    //printf("left\n");
    growSeed(table, tallGrassX1, tallGrassY1 - dxdy, 1);
    //left and up
    //printf("left and up\n");
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1 - dxdy, 1);

    //test print
    //printTable(table);
    //printf("%d\n ",dxdy);
    
    //tallgrass2
    //up
    growSeed(table, tallGrassX2 - dxdy, tallGrassY2, 1);
    //up and right
    growSeed(table, tallGrassX2 - dxdy, tallGrassY2 + dxdy, 1);
    //right
    growSeed(table, tallGrassX2, tallGrassY2 + dxdy, 1);
    //right and down
    growSeed(table, tallGrassX2 + dxdy, tallGrassY2 + dxdy, 1);
    //down
    growSeed(table, tallGrassX2 + dxdy, tallGrassY2, 1);
    //down and left
    growSeed(table, tallGrassX2 + dxdy, tallGrassY2 - dxdy, 1);
    //left
    growSeed(table, tallGrassX2, tallGrassY2 - dxdy, 1);
    //left and up
    growSeed(table, tallGrassX2 - dxdy, tallGrassY2 - dxdy, 1);
    
    //clearing1 = 2
    //up
    growSeed(table, clearingX1 - dxdy, clearingY1, 2);
    //up and right
    growSeed(table, clearingX1 - dxdy, clearingY1 + dxdy, 2);
    //right
    growSeed(table, clearingX1, clearingY1 + dxdy, 2);
    //right and down
    growSeed(table, clearingX1 + dxdy, clearingY1 + dxdy, 2);
    //down
    growSeed(table, clearingX1 + dxdy, clearingY1, 2);
    //down and left
    growSeed(table, clearingX1 + dxdy, clearingY1 - dxdy, 2);
    //left
    growSeed(table, clearingX1, clearingY1 - dxdy, 2);
    //left and up
    growSeed(table, clearingX1 - dxdy, clearingY1 - dxdy, 2);
    
    //clearing2
    //up
    growSeed(table, clearingX2 - dxdy, clearingY2, 2);
    //up and right
    growSeed(table, clearingX2 - dxdy, clearingY2 + dxdy, 2);
    //right
    growSeed(table, clearingX2, clearingY2 + dxdy, 2);
    //right and down
    growSeed(table, clearingX2 + dxdy, clearingY2 + dxdy, 2);
    //down
    growSeed(table, clearingX2 + dxdy, clearingY2, 2);
    //down and left
    growSeed(table, clearingX2 + dxdy, clearingY2 - dxdy, 2);
    //left
    growSeed(table, clearingX2, clearingY2 - dxdy, 2);
    //left and up
    growSeed(table, clearingX2 - dxdy, clearingY2 - dxdy, 2);
  }
  
}

void pokeLocations(int table[21][80], int roadR, int roadC){

  //I will place the pokemart along the left/right road and
  //the pokecenter along the up/down road

  int pmRow;
  int pmCol;
  int pcRow;
  int pcCol;

  //if the left/right road is at the top
  if (roadR == 1) {
    //we will place the pokemart under the road
    pmRow = 2;
  } else {
    //place the pokemart above the road
    pmRow = roadR - 1;
  }
  pmCol = getRandomNum(78);
  //make sure our pm isn't on the up/down road
  while (pmCol == roadC) {
    pmCol = getRandomNum(78);
  }
  table[pmRow][pmCol] = 4;

  //if the up down row is on the left
  if (roadC == 1) {
    //we will place the pokecenter on the right side of the road
    pcCol = 2;
  } else {
    //place the pokecenter on the left
    pcCol = roadC - 1;
  }
  pcRow = getRandomNum(19);
  //make sure our pc is not on the left/right row
  while (pcRow == roadR) {
    pcRow = getRandomNum(19);
  }

  table[pcRow][pcCol] = 5;
  
}

int main(int argc, char *argv[]) {

  //seed randomizer
  srand(time(NULL));
  
  int t[21][80];

  initializeTable(t);

  //tall grass = ; -> 1
  //we need two
  int tallGrassX1 = getRandomNum(19);
  //printf("tallGrassX1 = ; is ");
  //printf("%d\n", tallGrassX1);
  int tallGrassX2 = getRandomNum(19);
  //printf("tallGrassX2 = ; is ");
  //printf("%d\n", tallGrassX2);
  int tallGrassY1 = getRandomNum(78);
  //printf("tallGrassY1 = ; is ");
  //printf("%d\n", tallGrassY1);
  int tallGrassY2 = getRandomNum(78);
  //printf("tallGrassY2 = ; is ");
  //printf("%d\n", tallGrassY2);
  //printf("\n");
   
  //assign tall grass seeds
  t[tallGrassX1][tallGrassY1] = 1;
  t[tallGrassX2][tallGrassY2] = 1;

  //clearings = . -> 2
  //we need two
  int clearingX1 = getRandomNum(19);
  //printf("clearingX1 = . is ");
  //printf("%d\n", clearingX1);
  int clearingX2 = getRandomNum(19);
  //printf("clearingX2 = . is ");
  //printf("%d\n", clearingX2);
  int clearingY1 = getRandomNum(78);
  //printf("clearingY1 = . is ");
  //printf("%d\n", clearingY1);
  int clearingY2 = getRandomNum(78);
  //printf("clearingY2 = . is ");
  //printf("%d\n", clearingY2);
  //printf("\n");

  //assign clearing seeds
  t[clearingX1][clearingY1] = 2;
  t[clearingX2][clearingY2] = 2;

  //grow the seeds
  growSeeds(t, tallGrassX1, tallGrassY1, tallGrassX2, tallGrassY2, clearingX1, clearingY1, clearingX2, clearingY2);

  //boarder = % -> -1
  addBoarder(t);

  //roads = # -> 3
  //get road seeds
  int roadX1 = getRandomNum(19);
  //printf("road x = ");
  //printf("%d\n", roadX1);
  int roadY1 = getRandomNum(78);
  //printf("road y = ");
  //printf("%d\n", roadY1);

  //assign roads
  int i, j;
  //left to right
  for (int i = 0; i < 80; i++) {
    t[roadX1][i] = 3;
  }
  for (int j = 0; j < 21; j++) {
    t[j][roadY1] = 3;
  }

  //assign PokeCenter and Pokemart
  pokeLocations(t, roadX1, roadY1);
   
  printTable(t);

  return 0;
}
