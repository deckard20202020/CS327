
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "terrain.h"

int findDistance(int xCoord, int yCoord);

void initializeTable(int table[21][80]) {

     int i, j;
     for (j = 0; j < 21; j++) {
       for (i = 0; i < 80; i++) {
             table[j][i] = 0;
         }
     }
}

//void printTable(int table[21][80]) {

//  int r, c;

//  for (r = 0; r < 21; r++) {
//    for (c = 0; c < 80; c++) {
//      if (table[r][c] == -1) {
//        printf("%%");
//      } else if (table[r][c] == 1) {
//        printf(":");
//      } else if (table[r][c] == 2) {
//        printf(".");
//      } else if (table[r][c] == 3) {
//        printf("#");
//      } else if (table[r][c] == 4) {
//        printf("M");
//      } else if (table[r][c] == 5) {
//        printf("C");
//      } else {
        //printf("%d ", table[r][c]);
//        printf("^");
//      }
//    }
//    printf("\n");
//  }
//  printf("\n");

//}

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

void growSeeds(int table[21][80], int tallGrassX1, int tallGrassY1, int tallGrassX2, int tal\
lGrassY2, int clearingX1, int clearingY1, int clearingX2, int clearingY2){

  // int xChange;
  int dxdy;

  for (dxdy = 1; dxdy < 80; dxdy++) {
    //tallgrass1 = 1
    //up
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1, 1);
    //up and right
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1 + dxdy, 1);
    //right
    growSeed(table, tallGrassX1, tallGrassY1 + dxdy, 1);
    //right and down
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1 + dxdy, 1);
    //down
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1, 1);
    //down and left
    growSeed(table, tallGrassX1 + dxdy, tallGrassY1 - dxdy, 1);
    //left
    growSeed(table, tallGrassX1, tallGrassY1 - dxdy, 1);
    //left and up
    growSeed(table, tallGrassX1 - dxdy, tallGrassY1 - dxdy, 1);

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

void deletePokeLocations(int t[21][80], int xCoord, int yCoord) {

  int rpm;
  int rpc;
  double p;
  int i;
  int j;
  //find random number between 0 and 100;
  rpm = getRandomNum(99);
  rpc = getRandomNum(99);
  //find probability of whether we should have the pokemart
  // p = findPokeProb(xCoord, yCoord);
  p = findDistance(xCoord, yCoord);
  if (xCoord == 200 && yCoord == 200) {
    p = 101;
  }

//piazza says if the random number is lower, then you spawn it
//I will delete it if my random number is higher
  if (p < rpm) {
    //remove the pokemarts 4
    for (i = 0; i < 21; i++) {
      for (j = 0; j < 80; j++) {
        if (t[i][j] == 4) {
          //reassign to clearing = 2
          t[i][j] = 2;
        }
      }
    }
  } 
  
  if (p < rpc) {
    //remove the pokecenters 5
    for (i = 0; i < 21; i++) {
      for (j = 0; j < 80; j++) {
        if (t[i][j] == 5) {
          //reassign to clearing = 2
          t[i][j] = 2;
        }
      }
    }
  }

}

int findDistance(int xCoord, int yCoord) {

  int prob = 0;
  int dist = abs(xCoord - 200) + abs(yCoord - 200);
  if (dist < 200) {
    prob = ((-45 * dist) / 200) + 50;
  } else {
    prob = 5;
  }
  
  return prob;

}

void assignRoads(int t[21][80], int roadX1, int roadY1, int xCoord, int yCoord) {
  
  int i, j;

  //top left
  if (xCoord == 0 && yCoord == 0) {
    // for (i = roadY1; i < 80; i++) {
    //   t[roadX1][i] = 3;
    // }
    // for (j = roadX1; j < 21; j++) {
    //   t[j][roadY1] = 3;
    // }
    for (i = 1; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 20; j++) {
      t[j][roadY1] = 3;
    }
  }
  //top right
  else if (xCoord == 0 && yCoord == 400) {
    // for (i = 0; i <= roadY1; i++) {
    //   t[roadX1][i] = 3;
    // }
    // for (j = roadX1; j < 21; j++) {
    //   t[j][roadY1] = 3;
    // }
    for (i = 0; i < 79; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 1; j < 21; j++) {
      t[j][roadY1] = 3;
    }
  }
  //bottom left
  else if (xCoord == 400 && yCoord == 0) {
    // for (i = roadY1; i < 80; i++) {
    //   t[roadX1][i] = 3;
    // }
    // for (j = 0; j <= roadX1; j++) {
    //   t[j][roadY1] = 3;
    // }
    for (i = 1; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 20; j++) {
      t[j][roadY1] = 3;
    }
  }
  //bottom right
  else if (xCoord == 400 && yCoord == 400) {
    // for (i = 0; i <= roadY1; i++) {
    //   t[roadX1][i] = 3;
    // }
    // for (j = 0; j <= roadX1; j++) {
    //   t[j][roadY1] = 3;
    // }
    for (i = 0; i < 79; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 20; j++) {
      t[j][roadY1] = 3;
    }
  }
  //top row
  else if (xCoord == 0) {
    for (i = 0; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 1; j < 21; j++) {
      t[j][roadY1] = 3;
    }
  }
  //bottom row
  else if (xCoord == 400) {
    for (i = 0; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 20; j++) {
      t[j][roadY1] = 3;
    }
  }
  //left side
  else if (yCoord == 0) {
    for (i = 1; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 21; j++) {
      t[j][roadY1] = 3;
    }
  }
  //right side
  else if (yCoord == 400) {
    // for (i = 0; i <= roadY1; i++) {
    //   t[roadX1][i] = 3;
    // }
    // for (j = 0; j < 21; j++) {
    //   t[j][roadY1] = 3;
    // }
    for (i = 0; i < 79; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 21; j++) {
      t[j][roadY1] = 3;
    }
  } else {
    for (i = 0; i < 80; i++) {
      t[roadX1][i] = 3;
    }
    for (j = 0; j < 21; j++) {
      t[j][roadY1] = 3;
    }
  }
}

  //player character = 10 -> @
// void placePlayerCharacter(int t[21][80], int roadX, int roadY) {
// // void placePlayerCharacter(int t[21][80], int roadX, int roadY, map_t *p) {
//   //choose whether the player will be on the x or y road
//   int xy = getRandomNum(2);
//   if (xy < 2) {
//     //put the player on the x road
//     //cannot be on the exits
//     int xRand = getRandomNum(78);
//     t[roadX][xRand] = 10;
//     // p->pcX = roadX;
//     // p->pcY = xRand;
//   } else {
//     //put the player on the y road
//     //cannot be on the exits
//     int yRand = getRandomNum(19);
//     t[yRand][roadY] = 10;
//     // p->pcX = yRand;
//     // p->pcY = roadY;
//   }
// }

// void terrain_init(map_t *p, int xCoord, int yCoord){
void terrain_init(map_t *p, int xCoord, int yCoord) {

  int x = p->x;
  int y = p->y;
  make_Map(x, y, p->t, xCoord, yCoord);
  // make_Map(x, y, p->t, xCoord, yCoord, p);

  //MAYBE I SHOULD PLACE THE CHARACTER HERE


}

void make_Map(int x, int y, int t[21][80], int xc, int yc){
// void make_Map(int x, int y, int t[21][80], int xc, int yc, map_t *p){

  //seed randomizer
  srand(time(NULL));

  int xCoord = xc;
  int yCoord = yc;

  // int t[21][80];

  initializeTable(t);

  for (int i = 0; i < 5; i++) {
    //tall grass = ; -> 1
    //we need two
    int tallGrassX1 = getRandomNum(19);
    int tallGrassX2 = getRandomNum(19);
    int tallGrassY1 = getRandomNum(78);
    int tallGrassY2 = getRandomNum(78);

    //assign tall grass seeds
    t[tallGrassX1][tallGrassY1] = 1;
    t[tallGrassX2][tallGrassY2] = 1;

    int clearingX1 = getRandomNum(19);
    int clearingX2 = getRandomNum(19);
    int clearingY1 = getRandomNum(78);
    int clearingY2 = getRandomNum(78);

    //assign clearing seeds
    t[clearingX1][clearingY1] = 2;
    t[clearingX2][clearingY2] = 2;

    //grow the seeds
    growSeeds(t, tallGrassX1, tallGrassY1, tallGrassX2, tallGrassY2, clearingX1, clearingY1, clearingX2, clearingY2);
  }
  // //tall grass = ; -> 1
  // //we need two
  // int tallGrassX1 = getRandomNum(19);
  // int tallGrassX2 = getRandomNum(19);
  // int tallGrassY1 = getRandomNum(78);
  // int tallGrassY2 = getRandomNum(78);

  // //assign tall grass seeds
  // t[tallGrassX1][tallGrassY1] = 1;
  // t[tallGrassX2][tallGrassY2] = 1;

  //   //tall grass = ; -> 1
  // //we need two more
  // int tallGrassX3 = getRandomNum(19);
  // int tallGrassX4 = getRandomNum(19);
  // int tallGrassY3 = getRandomNum(78);
  // int tallGrassY4 = getRandomNum(78);

  // //assign tall grass seeds
  // t[tallGrassX3][tallGrassY3] = 1;
  // t[tallGrassX4][tallGrassY4] = 1;

  //clearings = . -> 2
  //we need two
  // int clearingX1 = getRandomNum(19);
  // int clearingX2 = getRandomNum(19);
  // int clearingY1 = getRandomNum(78);
  // int clearingY2 = getRandomNum(78);

  // //assign clearing seeds
  // t[clearingX1][clearingY1] = 2;
  // t[clearingX2][clearingY2] = 2;

  //   //clearings = . -> 2
  // //we need two more
  // int clearingX3 = getRandomNum(19);
  // int clearingX4 = getRandomNum(19);
  // int clearingY3 = getRandomNum(78);
  // int clearingY4 = getRandomNum(78);

  // assign clearing seeds
  // t[clearingX3][clearingY3] = 2;
  // t[clearingX4][clearingY4] = 2;

//   grow the seeds
//   growSeeds(t, tallGrassX1, tallGrassY1, tallGrassX2, tallGrassY2, clearingX1, clearingY1, clearingX2, clearingY2);

//   grow the two extra seeds I placed
//   growSeeds(t, tallGrassX3, tallGrassY3, tallGrassX4, tallGrassY4, clearingX3, clearingY3, clearingX4, clearingY4);

  //boarder = % -> -1
  addBoarder(t);

  //roads = # -> 3
  //get road seeds
  //int roadX1 = getRandomNum(19);
  int roadX1 = x;
  //int roadY1 = getRandomNum(78);
  int roadY1 = y;

  assignRoads(t, roadX1, roadY1, xCoord, yCoord);
  
  // //assign roads
  // int i, j;
  // //left to right
  // for (i = 0; i < 80; i++) {
  //   t[roadX1][i] = 3;
  // }
  // for (j = 0; j < 21; j++) {
  //   t[j][roadY1] = 3;
  // }

  //new assign roads function

  //assign PokeCenter and Pokemart
  pokeLocations(t, roadX1, roadY1);
  deletePokeLocations(t, xCoord, yCoord);
  //player character = 10 -> @
  // placePlayerCharacter(t, roadX1, roadY1);
  // placePlayerCharacter(t, roadX1, roadY1, p);

  // printTable(t);

  // terrain->map = t;
  // terrain->xRoad = roadX1;
  // terrain->yRoad = roadY1;

  //return t;

  //return 0;
}

