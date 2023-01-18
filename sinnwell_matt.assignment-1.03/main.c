#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#include "terrain.h"
//#include "heap.h"
#include "pq.h"

int getRandomNumber(int n){

  int r = rand() % n + 1;
  return r;
}

void printTable(int table[21][80]){

  int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      //boarder or boulder = -1 -> %
      if (table[r][c] == -1) {
        printf("%%");
        //tall grass = : -> 1
      } else if (table[r][c] == 1) {
        printf(":");
        //clearings = . -> 2
      } else if (table[r][c] == 2) {
        printf(".");
        //roads = # -> 3
      } else if (table[r][c] == 3) {
        printf("#");
        //pokemart = 4 -> M
      } else if (table[r][c] == 4) {
        printf("M");
        //pokecenter = 5 -> C
      } else if (table[r][c] == 5) {
        printf("C");
        //player character
      } else if (table[r][c] == 10) {
        printf("@");
      } else {
        //printf("%d ", table[r][c]);
        printf("^");
      }
    }
    printf("\n");
  }
  printf("\n");

}

void printIntTable(int table[21][80]) {

  int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      int toPrint = table[r][c];
      if (toPrint % 100 == 0) {
        printf("00 ");
      } else if (toPrint == INT_MAX) {
        printf("   ");
      } else if (toPrint % 100 < 10) {
        printf("0");
        printf("%d " , toPrint % 100);
      } else {
        printf("%d " , toPrint % 100);
      }
      
      // printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void cantMove(){
  printf("You can't move to that location\n");
}

//int table[21][80] move(
void printLocation(int x, int y) {
  // printf("Your internal coordinates are [");
  // printf("%d", x);
  // printf(" , ");
  // printf("%d", y);
  // printf("]\n");
  // printf("You are at (");
  // printf("%d", y - 200);
  // printf(" , ");
  // printf("%d", x - 200);
  // printf(") where would you like to go?\n");
}

void placePlayerCharacter(map_t *w, int roadX, int roadY) {
// void placePlayerCharacter(int t[21][80], int roadX, int roadY) {
// void placePlayerCharacter(int t[21][80], int roadX, int roadY, map_t *p) {
  //choose whether the player will be on the x or y road
  int xy = getRandomNumber(2);
  if (xy < 2) {
    //put the player on the x road
    //cannot be on the exits
    int xRand = getRandomNumber(78);
    w->t[roadX][xRand] = 10;
    w->playerCharX = roadX;
    w->playerCharY = xRand;
    // p->pcX = roadX;
    // p->pcY = xRand;
  } else {
    //put the player on the y road
    //cannot be on the exits
    int yRand = getRandomNumber(19);
    w->t[yRand][roadY] = 10;
    w->playerCharX = yRand;
    w->playerCharY = roadY;
    // p->pcX = yRand;
    // p->pcY = roadY;
  }
}

void fly(map_t *w[401][401], int xRoad, int yRoad, int xCoord, int yCoord) {
  if(w[xCoord][yCoord] == NULL) {
    w[xCoord][yCoord] = malloc(sizeof(map_t));
    w[xCoord][yCoord]->x = xRoad;
    w[xCoord][yCoord]->y = yRoad;
    // terrain_init(w[xCoord][yCoord]);
    terrain_init(w[xCoord][yCoord], xCoord, yCoord); 
  }
  // placePlayerCharacter(w[xCoord][yCoord]->t, xRoad, yRoad);
  placePlayerCharacter(w[xCoord][yCoord], xCoord, yCoord);
}

void skipWhiteSpace() {
  char chr;
  int z = 1;
  while(z == 1) {
    scanf("%c",&chr);
    if (chr == '\n') {
      z = 0;
    }
  }
}

void setTableToMaxVal(int t[21][80]) {
    int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      t[r][c] = INT_MAX;
    }
  }
}

void makeExitsUnreachable(int table[21][80]) {

  int r, c;

  //left and right side
  for (r = 0; r < 21; r++) {
    table[r][0] = INT_MAX;
    table[r][80] = INT_MAX;
  }

  //top and bottom
  for (c = 0; c < 80; c++ ) {
    table[0][c] = INT_MAX;
    table[20][c] = INT_MAX;
  }
}

int costOfTerrainHiker(int xCoord, int yCoord, map_t *m) {
  int key = m->t[xCoord][yCoord];

  if (key == -1) {
    //boarder
    return INT_MAX;
  } else if (key == 1) {
    //tall grass
    return 15;
  } else if (key == 2) {
    //clearing
    return 10;
  } else if (key == 3) {
    //roads
    return 10;
  } else if (key == 4) {
    //pokemart
    return 50;
  } else if (key == 5) {
    //pokecenter
    return 50;
  } else if (key == 10) {
    //player character
    return 0;
  } else {
    //^
    return INT_MAX;
  }
  return 0;
}

int costOfTerrainRival(int xCoord, int yCoord, map_t *m) {
  int key = m->t[xCoord][yCoord];

  if (key == -1) {
    //boarder
    return INT_MAX;
  } else if (key == 1) {
    //tall grass
    return 20;
  } else if (key == 2) {
    //clearing
    return 10;
  } else if (key == 3) {
    //roads
    return 10;
  } else if (key == 4) {
    //pokemart
    return 50;
  } else if (key == 5) {
    //pokecenter
    return 50;
  } else if (key == 10) {
    //player character
    return 0;
  } else {
    //^
    return INT_MAX;
  }
  return 0;
}

void djikstras(int playerCoordX, int playerCoordY, map_t *m, int h) {
// void djikstras(int distTable[21][80], int playerCoordX, int playerCoordY, map_t *m) {
  //mark everything as unvisited
  //1 = visited, 0 = not visited
  int visited[21][80];
  int r, c;
  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      visited[r][c] = 0;
    }
  }

  //initialize distance table
  int distTable[21][80];
    for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      distTable[r][c] = INT_MAX;
    }
  }

  //mark start as visited
  // visited[playerCoordX][playerCoordY] = 1;

  //mark distance to character = 0
  distTable[playerCoordX][playerCoordY] = 0;

  //initialize a heap
  //and put our starting location in the map
  Node* pq = newNode(playerCoordX, playerCoordY, 0);

  // int test = isEmpty(*pq);

  //while the pq is not empty
  while (!isEmpty(&pq)) {
    //pop the q
    Node* current = peek(&pq);
    // pop(&pq);
    //make it as visited


    //get the cost  of the terrain
    int cost;
    // int cost = costOfTerrainHiker(current->xCoord, current->yCoord, m);
    //check for visited
    // if (cost != INT_MAX && visited[current->xCoord][current->yCoord] == 0) {
    if (visited[current->xCoord][current->yCoord] == 0) {
      
      //for all the neighbors
      //update thier distance
      //insert into priority queue

      //up
      if (current->xCoord - 1 >= 0) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord - 1, current->yCoord, m);
        } else {
          cost = costOfTerrainRival(current->xCoord - 1, current->yCoord, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord - 1][current->yCoord] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord - 1][current->yCoord] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord, distTable[current->xCoord -1][current->yCoord]);
          }
        }
      }
      //northeast
      if (current->xCoord - 1 >= 0 && current->yCoord + 1 <= 79) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord - 1, current->yCoord + 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord - 1, current->yCoord + 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord - 1][current->yCoord + 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord - 1][current->yCoord + 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord + 1, distTable[current->xCoord -1][current->yCoord + 1]);
          }
        }

      }
      //east
      if (current->yCoord + 1 <=79) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord, current->yCoord + 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord, current->yCoord + 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord][current->yCoord + 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord][current->yCoord + 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord, current->yCoord + 1, distTable[current->xCoord][current->yCoord + 1]);
          }
        }

      }
      //southeast
      if (current->xCoord + 1 <= 20 && current->yCoord + 1 <= 79) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord + 1, current->yCoord + 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord + 1, current->yCoord + 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord + 1][current->yCoord + 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord + 1][current->yCoord + 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord + 1, distTable[current->xCoord + 1][current->yCoord + 1]);
          }
        }

      }
      //south
      if (current->xCoord + 1 <= 20) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord + 1, current->yCoord, m);
        } else {
          cost = costOfTerrainRival(current->xCoord + 1, current->yCoord, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord + 1][current->yCoord] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord + 1][current->yCoord] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord, distTable[current->xCoord  + 1][current->yCoord]);
          }
        }

      }
      //southwest
      if (current->xCoord + 1 <= 20 && current->yCoord - 1 >= 0) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord + 1, current->yCoord - 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord + 1, current->yCoord - 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord + 1][current->yCoord - 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord + 1][current->yCoord - 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord - 1, distTable[current->xCoord + 1][current->yCoord - 1]);
          }
        }

      }
      //west
      if (current->yCoord - 1 >= 0) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord, current->yCoord - 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord, current->yCoord - 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord][current->yCoord - 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord][current->yCoord - 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord, current->yCoord - 1, distTable[current->xCoord][current->yCoord - 1]);
          }
        }

      }
      //northwest
      if (current->xCoord - 1 >= 0 && current->yCoord - 1 >= 0) {
        if (h == 1) {
          cost = costOfTerrainHiker(current->xCoord - 1, current->yCoord - 1, m);
        } else {
          cost = costOfTerrainRival(current->xCoord - 1, current->yCoord - 1, m);
        }
        
        if (cost != INT_MAX) {
          if (distTable[current->xCoord - 1][current->yCoord - 1] > cost + distTable[current->xCoord][current->yCoord]) {
            distTable[current->xCoord - 1][current->yCoord - 1] = cost + distTable[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord - 1, distTable[current->xCoord - 1][current->yCoord - 1]);
          }
        }

      }

    }

    visited[current->xCoord][current->yCoord] = 1;
    pop(&pq);

  }


  //add the neighbors to the heap

  //while the heap is not empty
    //pull out a node


  //for each neighbor
    //calculate the new distance
    //if it's less than the current distance
      //update the distance table
    //mark the current node as visited

  //make exits unreachable
  makeExitsUnreachable(distTable);

  printIntTable(distTable);

}

//21 x 80
void createDistanceMaps(map_t *m) {

  //Boulder Tree Path Mart Center Grass Clearing Mountain Forrest Exit

  //I don't think I care where the roads are.
  // int xRoad = m->x;
  // int yRoad = m->y;
  int playerCoordX = m->playerCharX;
  int playerCoordY = m->playerCharY;

  //make a table for the hiker
  // int hikerTable[21][80] = malloc(sizeof(int [21][80]));
  // int hikerTable[21][80];
  // setTableToMaxVal(hikerTable);
  djikstras(playerCoordX, playerCoordY, m, 1);
  // djikstras(hikerTable, playerCoordX, playerCoordY, m);
  // printIntTable(hikerTable);
  printf("\n");
  djikstras(playerCoordX, playerCoordY, m, 0);

}

int main(int argc, char *argv[]){
  
  //seed randomizer
  srand(time(NULL));

  //we will have an array of pointers
  //our world will measure 401x401
 
  map_t *w[401][401];
  int i;
  int j;
  // int inputX;
  // int inputY;
  //initialize world to null
  for (i = 0; i < 401; i++) {
    for (j = 0; j < 401; j++) {
      w[i][j] = NULL;
    }
  }

  //find random numbers for your roads
  int xRoad = getRandomNumber(19);
  int yRoad = getRandomNumber(78);


  //make our initial map
  if(w[200][200] == NULL) {
    //w[200][200] = malloc(sizeof(*map_t));
    w[200][200] = malloc(sizeof(map_t));
    w[200][200]->x = xRoad;
    w[200][200]->y = yRoad;
    terrain_init(w[200][200], 200, 200);
  }

  //Place my player Character
    //player character = 10 -> @
  placePlayerCharacter(w[200][200], xRoad, yRoad);
  // placePlayerCharacter(w[200][200]->t, xRoad, yRoad);

  //print the initial map
  printTable(w[200][200]->t);
  int xCoord = 200;
  int yCoord = 200;
  printLocation(xCoord, yCoord);

  createDistanceMaps(w[xCoord][yCoord]);

  // int cont = 1;

  // //run our program
  // while (cont == 1) {
  //   char chr;
  //   printf("Enter a value: ");
  //   scanf("%c",&chr);     
  //   // printf("You entered %c.\n", chr);

  //   if (chr == 'q') {
  //     cont = 0;
  //     printf("The game has ended");
  //     skipWhiteSpace();
  //     continue;
  //   }
  //   if (chr == 'f') {
  //     scanf(" %d %d", &inputX, &inputY);
  //     //check for valid input
  //     if (inputX < -200 || inputX > 200 || inputY < -200 || inputY > 200) {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("You can't go that direction\n");
  //       skipWhiteSpace();
  //       continue;
  //     }
  //     //otherwise we know are in bounds
  //     //convert the input values
  //     xCoord = 200 + inputY;
  //     yCoord = 200 + inputX;
  //     fly(w, xRoad, yRoad, xCoord, yCoord);
  //     printTable(w[xCoord][yCoord]->t);
  //     printLocation(xCoord, yCoord);
  //     skipWhiteSpace();
  //     continue;
  //   }
  //   if (chr == 'n') {
  //     //go up
  //     if (xCoord == 0) {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("You can't go that direction\n");
  //       skipWhiteSpace();
  //       continue;
  //     } else {
  //       xCoord = xCoord - 1;
  //       fly(w, xRoad, yRoad, xCoord, yCoord);
  //       printTable(w[xCoord][yCoord]->t);
  //       printLocation(xCoord, yCoord);
  //       //create our other maps
  //       createDistanceMaps(w[xCoord][yCoord]);
  //       skipWhiteSpace();
  //       continue;
  //     }
  //   }
  //   if (chr == 's') {
  //     //go down
  //     if (xCoord == 400) {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("You can't go that direction\n");
  //       skipWhiteSpace();
  //       continue;
  //     } else {
  //       xCoord = xCoord + 1;
  //       fly(w, xRoad, yRoad, xCoord, yCoord);
  //       printTable(w[xCoord][yCoord]->t);
  //       printLocation(xCoord, yCoord);
  //       skipWhiteSpace();
  //       continue;
  //     }
  //   }
  //   if (chr == 'e') {
  //     //go right
  //     if (yCoord == 400) {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("You can't go that direction\n");
  //       skipWhiteSpace();
  //       continue;
  //     } else {
  //       yCoord = yCoord + 1;
  //       fly(w, xRoad, yRoad, xCoord, yCoord);
  //       printTable(w[xCoord][yCoord]->t);
  //       printLocation(xCoord, yCoord);
  //       skipWhiteSpace();
  //       continue;
  //     }
  //   }
  //   if (chr == 'w') {
  //     //go right
  //     if (yCoord == 0) {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("You can't go that direction\n");
  //       skipWhiteSpace();
  //       continue;
  //     } else {
  //       yCoord = yCoord - 1;
  //       fly(w, xRoad, yRoad, xCoord, yCoord);
  //       printTable(w[xCoord][yCoord]->t);
  //       printLocation(xCoord, yCoord);
  //       skipWhiteSpace();
  //       continue;
  //     }
  //   } else {
  //       printTable(w[xCoord][yCoord]->t);
  //       printf("Incorrect Input\n");
  //       printLocation(xCoord, yCoord);
  //       skipWhiteSpace();
  //       continue;
  //   }

  //   // int z = 1;
  //   // while(z == 1) {
  //   //   scanf("%c",&chr);
  //   //   if (chr == '\n') {
  //   //     z = 0;
  //   //   }
  //   // }
  // } 
    return 0;


}
