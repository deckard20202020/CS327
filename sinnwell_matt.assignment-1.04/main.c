#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<unistd.h>
#include <string.h>


#include "terrain.h"
//#include "heap.h"
#include "pq.h"
#include "characterQ.h"

int getRandomNumber(int n){

  int r = rand() % n + 1;
  return r;
}

void printTable(int table[21][80], int characterTable[21][80]){

  int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      //hiker
      if (characterTable[r][c] == 11) {
        printf("h");
      } else if (characterTable[r][c] == 12) {
        printf("r");
      } else if (characterTable[r][c] == 13) {
        printf("p");
      } else if (characterTable[r][c] == 14) {
        printf("w");
      } else if (characterTable[r][c] == 15) {
        printf("s");
      } else if (characterTable[r][c] == 16) {
        printf("e");
      }
      //boarder or boulder = -1 -> %
       else if (table[r][c] == -1) {
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

void placePlayerCharacter(map_t *w, int roadX, int roadY, int characterTable[21][80]) {

  //choose whether the player will be on the x or y road
  int xy = getRandomNumber(2);
  if (xy < 2) {
    //put the player on the x road
    //cannot be on the exits
    int xRand = getRandomNumber(78);
    w->t[roadX][xRand] = 10;
    w->playerCharX = roadX;
    w->playerCharY = xRand;
    characterTable[roadX][xRand] = 10;
  } else {
    //put the player on the y road
    //cannot be on the exits
    int yRand = getRandomNumber(19);
    w->t[yRand][roadY] = 10;
    w->playerCharX = yRand;
    w->playerCharY = roadY;
    characterTable[yRand][roadY] = 10;
  }
}

// void fly(map_t *w[401][401], int xRoad, int yRoad, int xCoord, int yCoord) {
//   if(w[xCoord][yCoord] == NULL) {
//     w[xCoord][yCoord] = malloc(sizeof(map_t));
//     w[xCoord][yCoord]->x = xRoad;
//     w[xCoord][yCoord]->y = yRoad;
//     // terrain_init(w[xCoord][yCoord]);
//     terrain_init(w[xCoord][yCoord], xCoord, yCoord); 
//   }
//   // placePlayerCharacter(w[xCoord][yCoord]->t, xRoad, yRoad);
//   placePlayerCharacter(w[xCoord][yCoord], xCoord, yCoord);
// }

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

int costOfTerrainOther(int xCoord, int yCoord, map_t *m) {
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

void djikstras(int playerCoordX, int playerCoordY, map_t *m, int h, int table[21][80]) {

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
  // int distTable[21][80];
    for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      table[r][c] = INT_MAX;
    }
  }

  //mark start as visited
  // visited[playerCoordX][playerCoordY] = 1;

  //mark distance to character = 0
  table[playerCoordX][playerCoordY] = 0;

  //initialize a heap
  //and put our starting location in the map
  Node* pq = newNode(playerCoordX, playerCoordY, 0);

  //while the pq is not empty
  while (!isEmpty(&pq)) {

    Node* current = peek(&pq);

    //cost  of the terrain
    int cost;

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
          if (table[current->xCoord - 1][current->yCoord] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord - 1][current->yCoord] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord, table[current->xCoord -1][current->yCoord]);
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
          if (table[current->xCoord - 1][current->yCoord + 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord - 1][current->yCoord + 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord + 1, table[current->xCoord -1][current->yCoord + 1]);
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
          if (table[current->xCoord][current->yCoord + 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord][current->yCoord + 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord, current->yCoord + 1, table[current->xCoord][current->yCoord + 1]);
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
          if (table[current->xCoord + 1][current->yCoord + 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord + 1][current->yCoord + 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord + 1, table[current->xCoord + 1][current->yCoord + 1]);
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
          if (table[current->xCoord + 1][current->yCoord] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord + 1][current->yCoord] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord, table[current->xCoord  + 1][current->yCoord]);
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
          if (table[current->xCoord + 1][current->yCoord - 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord + 1][current->yCoord - 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord + 1, current->yCoord - 1, table[current->xCoord + 1][current->yCoord - 1]);
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
          if (table[current->xCoord][current->yCoord - 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord][current->yCoord - 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord, current->yCoord - 1, table[current->xCoord][current->yCoord - 1]);
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
          if (table[current->xCoord - 1][current->yCoord - 1] > cost + table[current->xCoord][current->yCoord]) {
            table[current->xCoord - 1][current->yCoord - 1] = cost + table[current->xCoord][current->yCoord];
            push(&pq, current->xCoord - 1, current->yCoord - 1, table[current->xCoord - 1][current->yCoord - 1]);
          }
        }

      }

    }

    visited[current->xCoord][current->yCoord] = 1;
    pop(&pq);

  }

  //make exits unreachable
  makeExitsUnreachable(table);

  //We no longer need to print the distance maps
  // printIntTable(distTable);

}

//21 x 80
void createDistanceMaps(map_t *m, int hikerDistance[21][80], int rivalDistance[21][80]) {
// void createDistanceMaps(map_t *m) {

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
  //1 is hiker
  djikstras(playerCoordX, playerCoordY, m, 1, hikerDistance);
  // djikstras(hikerTable, playerCoordX, playerCoordY, m);
  // printIntTable(hikerDistance);
  // printf("\n");
  //0 is rival
  djikstras(playerCoordX, playerCoordY, m, 0, rivalDistance);
  // printIntTable(rivalDistance);
  // printf("test");

}

void setTableTo0(int t[21][80]) {
    int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      t[r][c] = 0;
    }
  }
}

char findCharacterChar(int c) {
  if (c == 12) {
    return 'r';
  } else if (c == 11) {
    return 'h';
  } else if (c == 15) {
    return 's';
  } else if (c == 13) {
    return 'p';
  } else if (c == 14) {
    return 'w';
  } else if (c == 16) {
    return 'e';
  }

  return '@';
}

void placeNPC(int table[21][80], map_t *w, int c, Character* characterQ, int direction) {

  //initially set to out of bounds
  int x = 22;
  int y = 81;

  //while we are out of bounds (can't be on boarder) or
  //the world has an impassable terrain at that location
  while (x <= 0 || x >= 20 || y <= 0 || y >=79
          //on the player character
          || (x == w->playerCharX && y == w->playerCharY)
          //on another character
          || table[x][y] != 0
          //on a tree or boarder
          || w->t[x][y] == -1 || w->t[x][y] == 0) {
    
    x = getRandomNumber(18);
    y = getRandomNumber(77);

    
  }

  char characterChar = findCharacterChar(c);

  table[x][y] = c;
  pushCharQ(&characterQ, 0, 1, 0, 0, x, y, characterChar, direction);

}

void moveRival(map_t * w, int characterTable[21][80], int rivalDistance[21][80], Character** characterQ) {
  
  //check the neighbors to find find the smallest one
  //make sure you don't hit the pc.

  Character* peeked = peekCharQ(characterQ);
  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int currentDistance = INT_MAX;

  int moveToX = INT_MAX;
  int moveToY = INT_MAX;

  //check all 8 neighbors
  //up
  //if we are in bound and there is no character at the location we are looking at
  if (currentX > 1 && characterTable[currentX - 1][currentY] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY] != 0 && rivalDistance[currentX - 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY];
      moveToX = currentX - 1;
      moveToY = currentY;
    }
  }
  //up and right
  if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY + 1] != 0 && rivalDistance[currentX - 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY + 1];
      moveToX = currentX - 1;
      moveToY = currentY + 1;
    }
  }
  //east
  if (currentY < 78 && characterTable[currentX][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY + 1] != 0 && rivalDistance[currentX][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY + 1];
      moveToX = currentX;
      moveToY = currentY + 1;
    }
  }
  //southeast
  if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY + 1] != 0 && rivalDistance[currentX + 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY + 1];
      moveToX = currentX + 1;
      moveToY = currentY + 1;
    }
  }
  //south
  if (currentX < 19 && characterTable[currentX + 1][currentY] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY] != 0 && rivalDistance[currentX + 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY];
      moveToX = currentX + 1;
      moveToY = currentY;
    }
  }
    //southwest
  if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY - 1] != 0 && rivalDistance[currentX + 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY - 1];
      moveToX = currentX + 1;
      moveToY = currentY - 1;
    }
  }
  //west
    if (currentY > 1 && characterTable[currentX][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY - 1] != 0 && rivalDistance[currentX][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY - 1];
      moveToX = currentX;
      moveToY = currentY - 1;
    }
  }
  //northwest
  if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY - 1] != 0 && rivalDistance[currentX - 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY - 1];
      moveToX = currentX - 1;
      moveToY = currentY - 1;
    }
  }

  int timeToAdd = costOfTerrainRival(moveToX, moveToY, w); 
  int time = peeked->nextTurn + timeToAdd;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, moveToX, moveToY, 'r', -1);
  
  //update the character map
  characterTable[currentX][currentY] = 0;
  characterTable[moveToX][moveToY] = 12;


  //move to that value
  //update next turn
  //pop the q
  //push that new thing into the queue
}

void moveHiker(map_t * w, int characterTable[21][80], int rivalDistance[21][80], Character** characterQ) {
  
  //check the neighbors to find find the smallest one
  //make sure you don't hit the pc.

  Character* peeked = peekCharQ(characterQ);
  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int currentDistance = INT_MAX;

  int moveToX = INT_MAX;
  int moveToY = INT_MAX;

  //check all 8 neighbors
  //up
  //if we are in bound and there is no character at the location we are looking at
  if (currentX > 1 && characterTable[currentX - 1][currentY] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY] != 0 && rivalDistance[currentX - 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY];
      moveToX = currentX - 1;
      moveToY = currentY;
    }
  }
  //up and right
  if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY + 1] != 0 && rivalDistance[currentX - 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY + 1];
      moveToX = currentX - 1;
      moveToY = currentY + 1;
    }
  }
  //east
  if (currentY < 78 && characterTable[currentX][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY + 1] != 0 && rivalDistance[currentX][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY + 1];
      moveToX = currentX;
      moveToY = currentY + 1;
    }
  }
  //southeast
  if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY + 1] != 0 && rivalDistance[currentX + 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY + 1];
      moveToX = currentX + 1;
      moveToY = currentY + 1;
    }
  }
  //south
  if (currentX < 19 && characterTable[currentX + 1][currentY] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY] != 0 && rivalDistance[currentX + 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY];
      moveToX = currentX + 1;
      moveToY = currentY;
    }
  }
    //southwest
  if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY - 1] != 0 && rivalDistance[currentX + 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY - 1];
      moveToX = currentX + 1;
      moveToY = currentY - 1;
    }
  }
  //west
    if (currentY > 1 && characterTable[currentX][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY - 1] != 0 && rivalDistance[currentX][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY - 1];
      moveToX = currentX;
      moveToY = currentY - 1;
    }
  }
  //northwest
  if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == 0) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY - 1] != 0 && rivalDistance[currentX - 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY - 1];
      moveToX = currentX - 1;
      moveToY = currentY - 1;
    }
  }

  int timeToAdd = costOfTerrainHiker(moveToX, moveToY, w); 
  int time = peeked->nextTurn + timeToAdd;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, moveToX, moveToY, 'h', -1);
  
  //update the character map
  characterTable[currentX][currentY] = 0;
  characterTable[moveToX][moveToY] = 11;


  //move to that value
  //update next turn
  //pop the q
  //push that new thing into the queue
}

void moveSentry(map_t * w, int characterTable[21][80], Character** characterQ) {
    
  Character* peeked = peekCharQ(characterQ);

  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int timeToAdd = costOfTerrainOther(currentX, currentY, w); 
  int time = peeked->nextTurn + timeToAdd;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, currentX, currentY, 's', -1);
}

void moveExplorer(map_t * w, int characterTable[21][80], Character** characterQ) {
    
  Character* peeked = peekCharQ(characterQ);

  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int moveX;
  int moveY;

  int proceed = 1;

  int count = 0;

  //check to see if a direction has been assigned
  //or if we need to assign a new direction
  //directions will be 1-8
  //starting at north and going clockwise

  while (proceed == 1) {

    if (peeked->direction == -1) {
      peeked->direction = getRandomNumber(7);
    }

    //check to see if we can go that direction
    //up
    if (peeked->direction == 1) {           //no character                                        3 = #                                     0 = ^
      // if (currentX > 1 && characterTable[currentX - 1][currentY] == 0 && w->t[currentX - 1][currentY] != 3 && w->t[currentX -1][currentY] != 0) {
      if (currentX > 1 && characterTable[currentX - 1][currentY] == 0 && w->t[currentX -1][currentY] != 0) {
        moveX = currentX - 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //up right
    if (peeked->direction == 2) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == 0 && w->t[currentX -1][currentY + 1] != 0) {
        moveX = currentX - 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right
    if (peeked->direction == 3) {           //no character                                        3 = #                                     0 = ^
      if (currentY < 78 && characterTable[currentX][currentY + 1] == 0 && w->t[currentX][currentY + 1] != 0) {
        moveX = currentX;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right and down
    if (peeked->direction == 4) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == 0 && w->t[currentX + 1][currentY + 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //down
    if (peeked->direction == 5) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && characterTable[currentX + 1][currentY] == 0 && w->t[currentX + 1][currentY] != 0) {
        moveX = currentX + 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }  

        //down and left
    if (peeked->direction == 6) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == 0 && w->t[currentX + 1][currentY - 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left
    if (peeked->direction == 7) {           //no character                                        3 = #                                     0 = ^
      if (currentY > 1 && characterTable[currentX][currentY - 1] == 0 && w->t[currentX][currentY - 1] != 0) {
        moveX = currentX;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left and up
    if (peeked->direction == 8) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == 0 && w->t[currentX - 1][currentY - 1] != 0) {
        moveX = currentX - 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //we have nowhere to go
    if (count == 9) {
      moveX = currentX;
      moveY = currentY;
      proceed = 0;
    }

    count++;

  }

  characterTable[currentX][currentY] = 0;
  characterTable[moveX][moveY] = 16;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int direction = peeked->direction;

  popCharQ(characterQ);
  //NEED TO FIX THIS!!!
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'e', direction);

}

void movePacer(map_t * w, int characterTable[21][80], Character** characterQ) {

  Character* peeked = peekCharQ(characterQ);
  
  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int moveX;
  int moveY;

  int direction = peeked->direction;

  int proceed = 1;

  int count = 0;

  //if we haven't assigned a direction yet, we need to assign one.
  if (direction == -1) {
    peeked->direction = getRandomNumber(7);
  }

  while (proceed) {

    //up
    if (peeked->direction == 1) {
      //try to move up
      if (currentX > 1 && characterTable[currentX - 1][currentY] == 0 && w->t[currentX -1][currentY] != 0) {
        moveX = currentX - 1;
        moveY = currentY;
        proceed = 0;
      } else {
        //move south
        peeked->direction = 5;
      }
    }

    //right and up
    if (peeked->direction == 2) {
      //try to move 
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == 0 && w->t[currentX -1][currentY + 1] != 0) {
        moveX = currentX - 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        //move south
        peeked->direction = 6;
      }
    }

        //right
    if (peeked->direction == 3) {
      //try to move 
      if (currentY < 78 && characterTable[currentX][currentY + 1] == 0 && w->t[currentX][currentY + 1] != 0) {
        moveX = currentX;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        //move left
        peeked->direction = 7;
      }
    }

        //right and down
    if (peeked->direction == 4) {
      //try to move 
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == 0 && w->t[currentX + 1][currentY + 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        //move left and up
        peeked->direction = 8;
      }
    }

    //down
    if (peeked->direction == 5) {
      //try to move 
      if (currentX < 19 && characterTable[currentX + 1][currentY] == 0 && w->t[currentX + 1][currentY] != 0) {
        moveX = currentX + 1;
        moveY = currentY;
        proceed = 0;
      } else {
        //move left
        peeked->direction = 1;
      }
    }

      //down and left
    if (peeked->direction == 6) {
      //try to move 
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == 0 && w->t[currentX + 1][currentY - 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        //move right and up
        peeked->direction = 2;
      }
    }

        //left
    if (peeked->direction == 7) {
      //try to move 
      if (currentY > 1 && characterTable[currentX][currentY - 1] == 0 && w->t[currentX][currentY - 1] != 0) {
        moveX = currentX;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        //move right
        peeked->direction = 3;
      }
    }

      //left and up
    if (peeked->direction == 8) {
      //try to move 
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == 0 && w->t[currentX - 1][currentY - 1] != 0) {
        moveX = currentX - 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        //move right and down
        peeked->direction = 4;
      }
    }

    count++;

    if (count == 9) {
      moveX = currentX;
      moveY = currentY;
      proceed = 0;
    }
  }



  characterTable[currentX][currentY] = 0;
  characterTable[moveX][moveY] = 13;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int newDirection = peeked->direction;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'p', newDirection);
}

void moveWanderer(map_t * w, int characterTable[21][80], Character** characterQ) {
    
  Character* peeked = peekCharQ(characterQ);

  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int moveX;
  int moveY;

  int proceed = 1;

  int count = 0;

  //check to see if a direction has been assigned
  //or if we need to assign a new direction
  //directions will be 1-8
  //starting at north and going clockwise

  while (proceed == 1) {

    if (peeked->direction == -1) {
      peeked->direction = getRandomNumber(7);
    }

    //check to see if we can go that direction
    //up
    if (peeked->direction == 1) {           //no character                                        3 = #                                     0 = ^
      // if (currentX > 1 && characterTable[currentX - 1][currentY] == 0 && w->t[currentX - 1][currentY] != 3 && w->t[currentX -1][currentY] != 0) {
      if (currentX > 1 && characterTable[currentX - 1][currentY] == 0 && w->t[currentX -1][currentY] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY]) {
        moveX = currentX - 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //up right
    if (peeked->direction == 2) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == 0 && w->t[currentX -1][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY + 1]) {
        moveX = currentX - 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right
    if (peeked->direction == 3) {           //no character                                        3 = #                                     0 = ^
      if (currentY < 78 && characterTable[currentX][currentY + 1] == 0 && w->t[currentX][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX][currentY + 1]) {
        moveX = currentX;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right and down
    if (peeked->direction == 4) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == 0 && w->t[currentX + 1][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY + 1]) {
        moveX = currentX + 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //down
    if (peeked->direction == 5) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && characterTable[currentX + 1][currentY] == 0 && w->t[currentX + 1][currentY] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY]) {
        moveX = currentX + 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }  

        //down and left
    if (peeked->direction == 6) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == 0 && w->t[currentX + 1][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY - 1]) {
        moveX = currentX + 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left
    if (peeked->direction == 7) {           //no character                                        3 = #                                     0 = ^
      if (currentY > 1 && characterTable[currentX][currentY - 1] == 0 && w->t[currentX][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX][currentY - 1]) {
        moveX = currentX;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left and up
    if (peeked->direction == 8) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == 0 && w->t[currentX - 1][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY - 1]) {
        moveX = currentX - 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //we have nowhere to go
    if (count == 9) {
      moveX = currentX;
      moveY = currentY;
      proceed = 0;
    }

    count++;

  }

  characterTable[currentX][currentY] = 0;
  characterTable[moveX][moveY] = 14;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int direction = peeked->direction;

  popCharQ(characterQ);
  //NEED TO FIX THIS!!!
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'w', direction);

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

  //make a map to store location of characters
  int characterTable[21][80];
  setTableTo0(characterTable);

  //Place my player Character
  //Player Character is on the terrain map!!!
  //player character = 10 -> @
  placePlayerCharacter(w[200][200], xRoad, yRoad, characterTable);
  Character* characterQ = newCharacter(1, 0, 0, 0, w[200][200]->playerCharX, w[200][200]->playerCharY, '@', -1);

  //default the number of characters to 10
  int numCharactersFromInput = 10;

  int numCharactersAdded = 0;

  //if the number of characters is provided
  // (!strcmp(argv[i], "--fps")
  for (int i = 0; i < argc; i++) {
    //update the number of characters
    if (strcmp(argv[i], "--numtrainers") == 0) {
      numCharactersFromInput = atoi(argv[i + 1]);
      break;
    }
  }

  switch (numCharactersFromInput) {

  //10	
  case 10 :
      //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(characterTable, w[200][200], 11, characterQ, -1);

    //place one Rival
      //Rival = 12 -> r
    placeNPC(characterTable, w[200][200], 12, characterQ, -1);

    // //place two Pacers
    //   //Pacer -> 13 = p
    placeNPC(characterTable, w[200][200], 13, characterQ, -1);
    placeNPC(characterTable, w[200][200], 13, characterQ, -1);

    // //place two Wanderers
    //   //Wanderer -> 14 = w
    placeNPC(characterTable, w[200][200], 14, characterQ, -1);
    placeNPC(characterTable, w[200][200], 14, characterQ, -1);

    // //place two Sentries
    //   //Sentry -> 15 = "s"
    placeNPC(characterTable, w[200][200], 15, characterQ, -1);
    placeNPC(characterTable, w[200][200], 15, characterQ, -1);
    
    // //place two Explorers
    //   //Explorer -> 16 = "e"
    placeNPC(characterTable, w[200][200], 16, characterQ, -1);
    placeNPC(characterTable, w[200][200], 16, characterQ, -1);
    break;
  //1  
  case 1 :
    //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(characterTable, w[200][200], 11, characterQ, -1);
    break;
  //2  
  case 2 :
    //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(characterTable, w[200][200], 11, characterQ, -1);
    //place one Rival
    //Rival = 12 -> r
    placeNPC(characterTable, w[200][200], 12, characterQ, -1);
    break;
  default : 
    //do something
    while (numCharactersAdded < numCharactersFromInput) {
      if (numCharactersAdded < numCharactersFromInput) {
        //place one Hikers
        //Hiker = 11 -> h
        placeNPC(characterTable, w[200][200], 11, characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //place one Rival
        //Rival = 12 -> r
        placeNPC(characterTable, w[200][200], 12, characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Pacer -> 13 = p
        placeNPC(characterTable, w[200][200], 13, characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Wanderer -> 14 = w
        placeNPC(characterTable, w[200][200], 14, characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Sentry -> 15 = "s"
        placeNPC(characterTable, w[200][200], 15, characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Explorer -> 16 = "e"
        placeNPC(characterTable, w[200][200], 16, characterQ, -1);
        numCharactersAdded++;
      }
    }
}

  // //place one Hikers
  //   //Hiker = 11 -> h
  // placeNPC(characterTable, w[200][200], 11, characterQ, -1);

  // //place one Rival
  //   //Rival = 12 -> r
  // placeNPC(characterTable, w[200][200], 12, characterQ, -1);

  // // //place two Pacers
  // //   //Pacer -> 13 = p
  // placeNPC(characterTable, w[200][200], 13, characterQ, -1);
  // placeNPC(characterTable, w[200][200], 13, characterQ, -1);

  // // //place two Wanderers
  // //   //Wanderer -> 14 = w
  // placeNPC(characterTable, w[200][200], 14, characterQ, -1);
  // placeNPC(characterTable, w[200][200], 14, characterQ, -1);

  // // //place two Sentries
  // //   //Sentry -> 15 = "s"
  // placeNPC(characterTable, w[200][200], 15, characterQ, -1);
  // placeNPC(characterTable, w[200][200], 15, characterQ, -1);
  
  // // //place two Explorers
  // //   //Explorer -> 16 = "e"
  // placeNPC(characterTable, w[200][200], 16, characterQ, -1);
  // placeNPC(characterTable, w[200][200], 16, characterQ, -1);

  //print the initial map
  // printTable(w[200][200]->t, characterTable);
  int xCoord = 200;
  int yCoord = 200;
  // printLocation(xCoord, yCoord);

  int hikerDistance[21][80];
  int rivalDistance[21][80];

  createDistanceMaps(w[xCoord][yCoord], hikerDistance, rivalDistance);

  int cont = 1;

  while (cont == 1) {
    Character* peeking = peekCharQ(&characterQ);
    if (peeking->charValue == '@') {
        printTable(w[200][200]->t, characterTable);
        int nextTurn = peeking->nextTurn;
        int x = peeking->xCoord;
        int y = peeking->yCoord;
        popCharQ(&characterQ);
        pushCharQ(&characterQ, 1, 0, nextTurn + 10, 0, x, y, '@', -1);
        usleep(250000);
    } else if (peeking->charValue == 'h') {
      moveHiker(w[200][200], characterTable, hikerDistance, &characterQ);
    } else if (peeking->charValue == 'r') {
      moveRival(w[200][200], characterTable, rivalDistance, &characterQ);
    } else if (peeking->charValue == 's') {
      moveSentry(w[200][200], characterTable, &characterQ);
    } else if (peeking->charValue == 'e') {
      moveExplorer(w[200][200], characterTable, &characterQ);
    } else if (peeking->charValue == 'p') {
      movePacer(w[200][200], characterTable, &characterQ);
    } else if (peeking->charValue == 'w') {
      moveWanderer(w[200][200], characterTable, &characterQ);
    }
  }

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
