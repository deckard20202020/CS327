#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<unistd.h>
//#include <string.h>
#include <ncurses.h>
#include "parse.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <cstring>

#include "terrain.h"
//#include "heap.h"
#include "pq.h"
#include "characterQ.h"

using namespace std;

void placeNPCs(int numCharactersFromInput, map_t* w);

int worldX;
int worldY;

int counter = 0;

int hasMovedMapsOnLastMove = 0;

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

// char[] printTable(int table[21][80], int characterTable[21][80]){

//   int r, c;
//   // char* s;

//   // char s[21][80];

//   for (r = 0; r < 21; r++) {
//     for (c = 0; c < 80; c++) {
//       //hiker
//       if (characterTable[r][c] == 11) {
//         s
//         *s = *s + "h";
//         // s[r][c] = 'h';
//       } else if (characterTable[r][c] == 12) {
//         *s = *s + "r";
//         // s[r][c] = 'r';
//       } else if (characterTable[r][c] == 13) {
//         *s = *s + "p";
//         // s[r][c] = 'p';
//       } else if (characterTable[r][c] == 14) {
//         *s = *s +"w";
//         // s[r][c] = 'w';
//       } else if (characterTable[r][c] == 15) {
//         *s = *s +"s";
//         // s[r][c] = 's';
//       } else if (characterTable[r][c] == 16) {
//         *s = *s + "e";
//         // s[r][c] = 'e';
//       }
//       //boarder or boulder = -1 -> %
//        else if (table[r][c] == -1) {
//         *s = *s + "%%";
//         // s[r][c] = '%';
//         //tall grass = : -> 1
//       } else if (table[r][c] == 1) {
//         *s = *s + ":";
//         // s[r][c] = ':';
//         //clearings = . -> 2
//       } else if (table[r][c] == 2) {
//         *s = *s + ".";
//         // s[r][c] = '.';
//         //roads = # -> 3
//       } else if (table[r][c] == 3) {
//         *s = *s + "#";
//         // s[r][c] = '#';
//         //pokemart = 4 -> M
//       } else if (table[r][c] == 4) {
//         *s = *s + "M";
//         // s[r][c] = 'M';
//         //pokecenter = 5 -> C
//       } else if (table[r][c] == 5) {
//         *s = *s + "C";
//         // s[r][c] = 'C';
//         //player character
//       } else if (table[r][c] == 10) {
//         *s = *s + "@";
//         // s[r][c] = '@';
//       } else {
//         //printf("%d ", table[r][c]);
//         *s = *s + "^";
//         // s[r][c] = '^';
//       }
//     }
//     *s = *s + "\n";
//   }
//   // *s = *s + "\n";

//   return s;

// }

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

void placePlayerCharacter(map_t *w, int roadX, int roadY, Character* characterTable[21][80]) {

  //choose whether the player will be on the x or y road
  int xy = getRandomNumber(2);
  if (xy < 2) {
    //put the player on the x road
    //cannot be on the exits
    int xRand = getRandomNumber(78);
    //change it back to road
    w->t[roadX][xRand] = 3;
    w->playerCharX = roadX;
    w->playerCharY = xRand;
    // Character* character = newCharacter(1, 0, 0, 0, w->playerCharX, w->playerCharY, '@', -1, 0);
    Character* character = newCharacterForCharacterMap(w->playerCharX, w->playerCharY, '@', 0);
    characterTable[roadX][xRand] = character;
  } else {
    //put the player on the y road
    //cannot be on the exits
    int yRand = getRandomNumber(19);
    //change it back to road
    w->t[yRand][roadY] = 3;
    w->playerCharX = yRand;
    w->playerCharY = roadY;
    // Character* characterQ = newCharacter(1, 0, 0, 0, w->playerCharX, w->playerCharY, '@', -1, 0);
    // characterTable[yRand][roadY] = characterQ;
    Character* character = newCharacterForCharacterMap(w->playerCharX, w->playerCharY, '@', 0);
    characterTable[yRand][roadY] = character;
  }
}

int findPlayerCharX(int xRoad, int yRoad, int xChange, int yChange) {
  
  //if we are going up
  if (xChange == -1) {
    //bottom of the next map
    return 19;
  }

  //if we are going down
  if (xChange == 1) {
    //top of the next map
    return 1;
  }

  //otherwise we are going left or right so stay on the road
  return xRoad;
}

int findPlayerCharY(int xRoad, int yRoad, int xChange, int yChange) {
  
  //if we are going left
  if (yChange == -1) {
    //right of the next map
    return 78;
  }

  //if we are going right
  if (yChange == 1) {
    //left of the next map
    return 1;
  }

  //otherwise we are going up or down so stay on the road
  return yRoad;
}

// fly(w, xRoad, yRoad, worldX, worldY);
// void fly(map_t *w[401][401], int xRoad, int yRoad, int xCoord, int yCoord) {
void fly(map_t *w[401][401], int xRoad, int yRoad, int xWorldMove, int yWorldMove, int numCharactersFromInput) {

  // int xWorldMove = worldX;
  // int yWorldMove = worldY;

  Character* peeking = peekCharQ(&(w[worldX][worldY]->characterQ));

  if(w[xWorldMove][yWorldMove] == NULL) {

    w[xWorldMove][yWorldMove] = new map_t();
    // w[xWorldMove][yWorldMove] = malloc(sizeof(map_t));
    w[xWorldMove][yWorldMove]->x = xRoad;
    w[xWorldMove][yWorldMove]->y = yRoad;
    // terrain_init(w[xCoord][yCoord]);
    // terrain_init(w[xWorldMove][yWorldMove], xCoord, yCoord); 
    // terrain_init(w[xWorldMove][yWorldMove], xRoad, yRoad); 
    terrain_init(w[xWorldMove][yWorldMove], xWorldMove, yWorldMove); 

    //pop from the Q
    //Maybe I don't pop from the Q so I know when my turn is if I return to this map
    // popCharQ(&w[worldX][worldY]->characterQ);

    //update the character table of our current map
      //could do this by scrolling through the caracter map and 
      //assigning all '@' to 0
    w[worldX][worldY]->characterTable[peeking->xCoord][peeking->yCoord] = NULL;

    //update the world coordinates
    worldX = xWorldMove;
    worldY = yWorldMove;

    //create a new PC table for the new world
    //I don't want to place the player character here.  I want to place him where he should be
    int movePCX = xRoad;
    int movePCY = yRoad;

    //update the variables in the world I don't think I use anymore
    w[xWorldMove][yWorldMove]->playerCharX = movePCX;
    w[xWorldMove][yWorldMove]->playerCharY = movePCY;

    //make our character table point to that character
    Character* character = newCharacterForCharacterMap(movePCX, movePCY, '@', 0);

    //scroll through the character table and assign all null
    for (int r = 0; r < 21; r++) {
      for (int c = 0; c < 80; c++) {
        w[xWorldMove][yWorldMove]->characterTable[r][c] = NULL;
      }
    }

    //update the characterTable of where we are going
    w[xWorldMove][yWorldMove]->characterTable[movePCX][movePCY] = character;
  
    //initialize character queue and put pc in the queue
    // Character* characterQ = newCharacter(1, 0, 0, 0, w[200][200]->playerCharX, w[200][200]->playerCharY, '@', -1, 0);
    w[xWorldMove][yWorldMove]->characterQ = newCharacter(1, 0, 0, 0, movePCX, movePCY, '@', -1, 0);

    placeNPCs(numCharactersFromInput, w[xWorldMove][yWorldMove]);

    //Do I need to update the distance maps???

    hasMovedMapsOnLastMove = 1;

  } else {
    //I AM RETURNING TO A MAP I HAVE ALREADY BEEN TO
    // int xWorldMove = worldX + xChange;
    // int yWorldMove = worldY + yChange;

    //our PC should still be at the top of the q in this map
    Character* peeking = peekCharQ(&(w[xWorldMove][yWorldMove]->characterQ));

    //find where the PC should be
    int movePCX = xRoad;
    int movePCY = yRoad;

    //assign those values to our PC
    peeking->xCoord = movePCX;
    peeking->yCoord = movePCY;

    //place the PC in the character map
    w[xWorldMove][yWorldMove]->characterTable[movePCX][movePCY] = peeking;

    //update the info I don't think I ever use
    w[xWorldMove][yWorldMove]->playerCharX = movePCX;
    w[xWorldMove][yWorldMove]->playerCharY = movePCY;

    //update the world coordinates
    worldX = xWorldMove;
    worldY = yWorldMove;

    //since the PC will be the first to move the distance maps
    //should be updated after the first move

    hasMovedMapsOnLastMove = 1;
  }
  // placePlayerCharacter(w[xCoord][yCoord]->t, xRoad, yRoad);
 //Can I place the player character at the right place???
  // placePlayerCharacter(w[xCoord][yCoord], xCoord, yCoord);

  //we need to place the npcs
}

// flyOne(w[worldX][worldY], numCharactersFromInput, worldX,  worldY, xRoad, yRoad, -1, 0 );
void flyOne(map_t *w[401][401], int numCharactersFromInput, int xRoad, int yRoad, int xChange, int yChange) {
  
  counter = 0;

  Character* peeking = peekCharQ(&(w[worldX][worldY]->characterQ));

  int xWorldMove = worldX + xChange;
  int yWorldMove = worldY + yChange;
  
  if(w[xWorldMove][yWorldMove] == NULL) {
    w[xWorldMove][yWorldMove] = new map_t();
    // w[xWorldMove][yWorldMove] = malloc(sizeof(map_t));
    w[xWorldMove][yWorldMove]->x = xRoad;
    w[xWorldMove][yWorldMove]->y = yRoad;
    // terrain_init(w[xCoord][yCoord]);
    // terrain_init(w[xWorldMove][yWorldMove], xCoord, yCoord); 
    terrain_init(w[xWorldMove][yWorldMove], xWorldMove, yWorldMove); 

    //pop from the Q
    //Maybe I don't pop from the Q so I know when my turn is if I return to this map
    // popCharQ(&w[worldX][worldY]->characterQ);

    //update the character table of our current map
      //could do this by scrolling through the caracter map and 
      //assigning all '@' to 0
    w[worldX][worldY]->characterTable[peeking->xCoord][peeking->yCoord] = NULL;

    //update the world coordinates
    worldX = xWorldMove;
    worldY = yWorldMove;

    //create a new PC table for the new world
    //I don't want to place the player character here.  I want to place him where he should be
    int movePCX = findPlayerCharX(xRoad, yRoad, xChange, yChange);
    int movePCY = findPlayerCharY(xRoad, yRoad, xChange, yChange);

    //update the variables in the world I don't think I use anymore
    w[xWorldMove][yWorldMove]->playerCharX = movePCX;
    w[xWorldMove][yWorldMove]->playerCharY = movePCY;

    //make our character table point to that character
    Character* character = newCharacterForCharacterMap(movePCX, movePCY, '@', 0);

    //scroll through the character table and assign all null
    for (int r = 0; r < 21; r++) {
      for (int c = 0; c < 80; c++) {
        w[xWorldMove][yWorldMove]->characterTable[r][c] = NULL;
      }
    }

    //update the characterTable of where we are going
    w[xWorldMove][yWorldMove]->characterTable[movePCX][movePCY] = character;
  
    //initialize character queue and put pc in the queue
    // Character* characterQ = newCharacter(1, 0, 0, 0, w[200][200]->playerCharX, w[200][200]->playerCharY, '@', -1, 0);
    w[xWorldMove][yWorldMove]->characterQ = newCharacter(1, 0, 0, 0, movePCX, movePCY, '@', -1, 0);

    placeNPCs(numCharactersFromInput, w[xWorldMove][yWorldMove]);

    //Do I need to update the distance maps???

    hasMovedMapsOnLastMove = 1;

  } else {
    //I AM RETURNING TO A MAP I HAVE ALREADY BEEN TO
    int xWorldMove = worldX + xChange;
    int yWorldMove = worldY + yChange;

    //our PC should still be at the top of the q in this map
    Character* peeking = peekCharQ(&(w[xWorldMove][yWorldMove]->characterQ));

    //find where the PC should be
    int movePCX = findPlayerCharX(xRoad, yRoad, xChange, yChange);
    int movePCY = findPlayerCharY(xRoad, yRoad, xChange, yChange);

    //assign those values to our PC
    peeking->xCoord = movePCX;
    peeking->yCoord = movePCY;

    //place the PC in the character map
    w[xWorldMove][yWorldMove]->characterTable[movePCX][movePCY] = peeking;

    //update the info I don't think I ever use
    w[xWorldMove][yWorldMove]->playerCharX = movePCX;
    w[xWorldMove][yWorldMove]->playerCharY = movePCY;

    //update the world coordinates
    worldX = xWorldMove;
    worldY = yWorldMove;

    //since the PC will be the first to move the distance maps
    //should be updated after the first move

    hasMovedMapsOnLastMove = 1;
  }

    // pushCharQ(characterQ, 1, 0, nextTurn, 0, x, y, '@', -1, 0);

    //update the distance maps
    // createDistanceMaps(w, hikerDistance, rivalDistance, characterTable);

    //we need to place the npcs
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

int costOfTerrainPC(int xCoord, int yCoord, map_t *m) {
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
    return 10;
  } else if (key == 5) {
    //pokecenter
    return 10;
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
void createDistanceMaps(map_t *m, int hikerDistance[21][80], int rivalDistance[21][80], Character* characterTable[21][80]) {
// void createDistanceMaps(map_t *m) {

  //Boulder Tree Path Mart Center Grass Clearing Mountain Forrest Exit

  //I don't think I care where the roads are.
  // int xRoad = m->x;
  // int yRoad = m->y;

  int playerCoordX;
  int playerCoordY;

  //find where the pc is
  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 79; j++) {
      if (characterTable[i][j] && characterTable[i][j]->charValue == '@') {
        playerCoordX = i;
        playerCoordY = j;
      }
    }
  }
  // int playerCoordX = m->playerCharX;
  // int playerCoordY = m->playerCharY;

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

//placeNPC(characterTable, w[200][200], 13, characterQ, -1);
void placeNPC(Character* table[21][80], map_t *w, int c, Character* characterQ, int direction) {

  //initially set to out of bounds
  int x = 22;
  int y = 81;

  //while we are out of bounds (can't be on boarder) or
  //the world has an impassable terrain at that location
  while (x <= 0 || x >= 20 || y <= 0 || y >=79
          //on the player character
          || (x == w->playerCharX && y == w->playerCharY)
          //on another character
          || table[x][y] != NULL
          //on a tree or boarder
          || w->t[x][y] == -1 || w->t[x][y] == 0) {
    
    x = getRandomNumber(18);
    y = getRandomNumber(77);

    
  }

  char characterChar = findCharacterChar(c);
  Character* characterForMap = newCharacterForCharacterMap(x, y, characterChar, 0);

  table[x][y] = characterForMap;
  pushCharQ(&characterQ, 0, 1, 0, 0, x, y, characterChar, direction, 0);

}

void moveRival(map_t * w, Character * characterTable[21][80], int rivalDistance[21][80], Character** characterQ) {
  
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
  if (currentX > 1 && characterTable[currentX - 1][currentY] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY] != 0 && rivalDistance[currentX - 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY];
      moveToX = currentX - 1;
      moveToY = currentY;
    }
  }
  //up and right
  if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY + 1] != 0 && rivalDistance[currentX - 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY + 1];
      moveToX = currentX - 1;
      moveToY = currentY + 1;
    }
  }
  //east
  if (currentY < 78 && characterTable[currentX][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY + 1] != 0 && rivalDistance[currentX][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY + 1];
      moveToX = currentX;
      moveToY = currentY + 1;
    }
  }
  //southeast
  if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY + 1] != 0 && rivalDistance[currentX + 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY + 1];
      moveToX = currentX + 1;
      moveToY = currentY + 1;
    }
  }
  //south
  if (currentX < 19 && characterTable[currentX + 1][currentY] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY] != 0 && rivalDistance[currentX + 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY];
      moveToX = currentX + 1;
      moveToY = currentY;
    }
  }
    //southwest
  if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY - 1] != 0 && rivalDistance[currentX + 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY - 1];
      moveToX = currentX + 1;
      moveToY = currentY - 1;
    }
  }
  //west
    if (currentY > 1 && characterTable[currentX][currentY - 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY - 1] != 0 && rivalDistance[currentX][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY - 1];
      moveToX = currentX;
      moveToY = currentY - 1;
    }
  }
  //northwest
  if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == NULL) {
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
  pushCharQ(characterQ, 0, 1, time, 0, moveToX, moveToY, 'r', -1, 0);
  
  //update the character map
  free(characterTable[currentX][currentY]);
  characterTable[currentX][currentY] = NULL;
  Character * character = newCharacterForCharacterMap(moveToX, moveToY, 'r', 0);
  characterTable[moveToX][moveToY] = character;


  //move to that value
  //update next turn
  //pop the q
  //push that new thing into the queue
}

void moveHiker(map_t * w, Character * characterTable[21][80], int rivalDistance[21][80], Character** characterQ) {
  
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
  if (currentX > 1 && characterTable[currentX - 1][currentY] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY] != 0 && rivalDistance[currentX - 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY];
      moveToX = currentX - 1;
      moveToY = currentY;
    }
  }
  //up and right
  if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX - 1][currentY + 1] != 0 && rivalDistance[currentX - 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX - 1][currentY + 1];
      moveToX = currentX - 1;
      moveToY = currentY + 1;
    }
  }
  //east
  if (currentY < 78 && characterTable[currentX][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY + 1] != 0 && rivalDistance[currentX][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY + 1];
      moveToX = currentX;
      moveToY = currentY + 1;
    }
  }
  //southeast
  if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY + 1] != 0 && rivalDistance[currentX + 1][currentY + 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY + 1];
      moveToX = currentX + 1;
      moveToY = currentY + 1;
    }
  }
  //south
  if (currentX < 19 && characterTable[currentX + 1][currentY] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY] != 0 && rivalDistance[currentX + 1][currentY] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY];
      moveToX = currentX + 1;
      moveToY = currentY;
    }
  }
    //southwest
  if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX + 1][currentY - 1] != 0 && rivalDistance[currentX + 1][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX + 1][currentY - 1];
      moveToX = currentX + 1;
      moveToY = currentY - 1;
    }
  }
  //west
    if (currentY > 1 && characterTable[currentX][currentY - 1] == NULL) {
    //if the distance we are looking at is less than the current distance
    if (rivalDistance[currentX][currentY - 1] != 0 && rivalDistance[currentX][currentY - 1] < currentDistance) {
      currentDistance = rivalDistance[currentX][currentY - 1];
      moveToX = currentX;
      moveToY = currentY - 1;
    }
  }
  //northwest
  if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == NULL) {
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

  //if we should move
  // if (characterTable[moveToX][moveToY] == NULL || characterTable[currentX][currentY]->isBattled == 0) {
  //   //move
  //   pushCharQ(characterQ, 0, 1, time, 0, moveToX, moveToY, 'h', -1, 0);
  
  //   //update the character map
  //   free(characterTable[currentX][currentY]);
  //   characterTable[currentX][currentY] = NULL;
  //   Character * character = newCharacterForCharacterMap(moveToX, moveToY, 'h', 0);
  //   characterTable[moveToX][moveToY] = character;
  // }


  pushCharQ(characterQ, 0, 1, time, 0, moveToX, moveToY, 'h', -1, 0);
  
  //update the character map
  free(characterTable[currentX][currentY]);
  characterTable[currentX][currentY] = NULL;
  Character * character = newCharacterForCharacterMap(moveToX, moveToY, 'h', 0);
  characterTable[moveToX][moveToY] = character;


  //move to that value
  //update next turn
  //pop the q
  //push that new thing into the queue
}

void moveSentry(map_t * w, Character* characterTable[21][80], Character** characterQ) {
    
  Character* peeked = peekCharQ(characterQ);

  int currentX = peeked->xCoord;
  int currentY = peeked->yCoord;

  int timeToAdd = costOfTerrainOther(currentX, currentY, w); 
  int time = peeked->nextTurn + timeToAdd;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, currentX, currentY, 's', -1, 0);
}

void moveExplorer(map_t * w, Character * characterTable[21][80], Character** characterQ) {
    
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
      if (currentX > 1 && characterTable[currentX - 1][currentY] == NULL && w->t[currentX -1][currentY] != 0) {
        moveX = currentX - 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //up right
    if (peeked->direction == 2) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == NULL && w->t[currentX -1][currentY + 1] != 0) {
        moveX = currentX - 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right
    if (peeked->direction == 3) {           //no character                                        3 = #                                     0 = ^
      if (currentY < 78 && characterTable[currentX][currentY + 1] == NULL && w->t[currentX][currentY + 1] != 0) {
        moveX = currentX;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right and down
    if (peeked->direction == 4) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == NULL && w->t[currentX + 1][currentY + 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //down
    if (peeked->direction == 5) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && characterTable[currentX + 1][currentY] == NULL && w->t[currentX + 1][currentY] != 0) {
        moveX = currentX + 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }  

        //down and left
    if (peeked->direction == 6) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == NULL && w->t[currentX + 1][currentY - 1] != 0) {
        moveX = currentX + 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left
    if (peeked->direction == 7) {           //no character                                        3 = #                                     0 = ^
      if (currentY > 1 && characterTable[currentX][currentY - 1] == NULL && w->t[currentX][currentY - 1] != 0) {
        moveX = currentX;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left and up
    if (peeked->direction == 8) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == NULL && w->t[currentX - 1][currentY - 1] != 0) {
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

  free(characterTable[currentX][currentY]);
  characterTable[currentX][currentY] = NULL;
  Character * character = newCharacterForCharacterMap(moveX, moveY, 'e', 0);
  characterTable[moveX][moveY] = character;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int direction = peeked->direction;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'e', direction, 0);

}

void movePacer(map_t * w, Character * characterTable[21][80], Character** characterQ) {

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
      if (currentX > 1 && characterTable[currentX - 1][currentY] == NULL && w->t[currentX -1][currentY] != 0) {
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
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == NULL && w->t[currentX -1][currentY + 1] != 0) {
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
      if (currentY < 78 && characterTable[currentX][currentY + 1] == NULL && w->t[currentX][currentY + 1] != 0) {
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
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == NULL && w->t[currentX + 1][currentY + 1] != 0) {
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
      if (currentX < 19 && characterTable[currentX + 1][currentY] == NULL && w->t[currentX + 1][currentY] != 0) {
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
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == NULL && w->t[currentX + 1][currentY - 1] != 0) {
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
      if (currentY > 1 && characterTable[currentX][currentY - 1] == NULL && w->t[currentX][currentY - 1] != 0) {
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
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == NULL && w->t[currentX - 1][currentY - 1] != 0) {
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


  free(characterTable[currentX][currentY]);
  characterTable[currentX][currentY] = NULL;
  Character * character = newCharacterForCharacterMap(moveX, moveY, 'p', 0);
  characterTable[moveX][moveY] = character;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int newDirection = peeked->direction;

  popCharQ(characterQ);
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'p', newDirection, 0);
}

void moveWanderer(map_t * w, Character * characterTable[21][80], Character** characterQ) {
    
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
      if (currentX > 1 && characterTable[currentX - 1][currentY] == NULL && w->t[currentX -1][currentY] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY]) {
        moveX = currentX - 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //up right
    if (peeked->direction == 2) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY < 78 && characterTable[currentX - 1][currentY + 1] == NULL && w->t[currentX -1][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY + 1]) {
        moveX = currentX - 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right
    if (peeked->direction == 3) {           //no character                                        3 = #                                     0 = ^
      if (currentY < 78 && characterTable[currentX][currentY + 1] == NULL && w->t[currentX][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX][currentY + 1]) {
        moveX = currentX;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

    //right and down
    if (peeked->direction == 4) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY < 78 && characterTable[currentX + 1][currentY + 1] == NULL && w->t[currentX + 1][currentY + 1] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY + 1]) {
        moveX = currentX + 1;
        moveY = currentY + 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //down
    if (peeked->direction == 5) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && characterTable[currentX + 1][currentY] == NULL && w->t[currentX + 1][currentY] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY]) {
        moveX = currentX + 1;
        moveY = currentY;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }  

        //down and left
    if (peeked->direction == 6) {           //no character                                        3 = #                                     0 = ^
      if (currentX < 19 && currentY > 1 && characterTable[currentX + 1][currentY - 1] == NULL && w->t[currentX + 1][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX + 1][currentY - 1]) {
        moveX = currentX + 1;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left
    if (peeked->direction == 7) {           //no character                                        3 = #                                     0 = ^
      if (currentY > 1 && characterTable[currentX][currentY - 1] == NULL && w->t[currentX][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX][currentY - 1]) {
        moveX = currentX;
        moveY = currentY - 1;
        proceed = 0;
      } else {
        peeked->direction = -1;
      }
    }

        //left and up
    if (peeked->direction == 8) {           //no character                                        3 = #                                     0 = ^
      if (currentX > 1 && currentY > 1 && characterTable[currentX - 1][currentY - 1] == NULL && w->t[currentX - 1][currentY - 1] != 0 && w->t[currentX][currentY] == w->t[currentX - 1][currentY - 1]) {
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

  free(characterTable[currentX][currentY]);
  characterTable[currentX][currentY] = NULL;
  Character * character = newCharacterForCharacterMap(moveX, moveY, 'w', 0);
  characterTable[moveX][moveY] = character;

  int timeToAdd = costOfTerrainOther(moveX, moveY, w); 
  int time = peeked->nextTurn + timeToAdd;
  int direction = peeked->direction;

  popCharQ(characterQ);
  //NEED TO FIX THIS!!!
  pushCharQ(characterQ, 0, 1, time, 0, moveX, moveY, 'w', direction, 0);

}

void io_init_terminal() {
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
}

void io_display(int table[21][80], Character * characterTable[21][80]) {

  int r, c;

  for (r = 0; r < 21; r++) {
    for (c = 0; c < 80; c++) {
      //hiker
      if (characterTable[r][c]) {
        char character = characterTable[r][c]->charValue;
        mvaddch(r + 1, c, character);
        // printf("h");
      // } else if (characterTable[r][c] == 12) {
      //   mvaddch(r + 1, c, 'r');
      //   // printf("r");
      // } else if (characterTable[r][c] == 13) {
      //   mvaddch(r + 1, c, 'p');
      //   // printf("p");
      // } else if (characterTable[r][c] == 14) {
      //   mvaddch(r + 1, c, 'w');
      //   // printf("w");
      // } else if (characterTable[r][c] == 15) {
      //   mvaddch(r + 1, c, 's');
      //   // printf("s");
      // } else if (characterTable[r][c] == 16) {
      //   mvaddch(r + 1, c, 'e');
      //   // printf("e");
      // } else if (characterTable[r][c] == 10) {
      //   mvaddch(r + 1, c, '@');
      }//boarder or boulder = -1 -> %
       else if (table[r][c] == -1) {
        mvaddch(r + 1, c, '%');
        // printf("%%");
        //tall grass = : -> 1
      } else if (table[r][c] == 1) {
        mvaddch(r + 1, c, ':');
        // printf(":");
        //clearings = . -> 2
      } else if (table[r][c] == 2) {
        mvaddch(r + 1, c, '.');
        // printf(".");
        //roads = # -> 3
      } else if (table[r][c] == 3) {
        mvaddch(r + 1, c, '#');
        // printf("#");
        //pokemart = 4 -> M
      } else if (table[r][c] == 4) {
        mvaddch(r + 1, c, 'M');
        // printf("M");
        //pokecenter = 5 -> C
      } else if (table[r][c] == 5) {
        mvaddch(r + 1, c, 'C');
        // printf("C");
        //player character
      // } else if (table[r][c] == 10) {
      //   mvaddch(r + 1, c, '@');
        // printf("@");
      } else {
        //printf("%d ", table[r][c]);
        mvaddch(r + 1, c, '^');
        // printf("^");
      }
    }
    mvaddch(r + 2, c, '\n');
    // printf("\n");
  }
  // printf("\n");
  // mvaddch(r + 2, c, '\n');

  //get rid of error message about moving
  // mvprintw(22, 0, "");


}

int validMove(int xCoord, int yCoord, map_t * w, int xChange, int yChange) {
  
  //inbounds
  if (xCoord + xChange > 0 && xCoord + xChange < 20) {
    if (yCoord + yChange > 0 && yCoord + yChange < 79) {
      //could you just check the cost of terrain???
      //not % -> -1
      if (w->t[xCoord + xChange][yCoord + yChange] != -1 &&
          //not ^ -> 0
          w->t[xCoord + xChange][yCoord + yChange] != 0) {
            return 1;
          }
    }
  }

  return 0;
}

int movingMaps(int xCoordPC, int yCoordPC, map_t * w, int xChange, int yChange) {
  //if we are at the edge of the map
  if (xCoordPC == 1 || xCoordPC == 19 || yCoordPC == 1 || yCoordPC == 78) {
    //if we are headed towards an exit  roads = #->3
    if (w->t[xCoordPC + xChange][yCoordPC + yChange] == 3) {
      return 1;
    }
  }

  return 0;
}

void movePC(Character* pc, map_t * w, Character * characterTable[21][80], int hikerDistance[21][80], int rivalDistance[21][80], int xChange, int yChange, Character** characterQ) {

  // int currX = pc->xCoord;
  // int currY = pc->yCoord;

  int currX;
  int currY;

  for (int i = 0; i < 21; i++) {
    for (int j = 0; j < 79; j++) {
      if (characterTable[i][j] && characterTable[i][j]->charValue == '@') {
        currX = i;
        currY = j;
      }
    }
  }

  int moveX = currX + xChange;
  int moveY = currY + yChange;

  char in = 'w';

  //if there is a character in the space and it has not been battled
  //but don't move
  if (characterTable[moveX][moveY] && characterTable[moveX][moveY]->isBattled == 0 && characterTable[moveX][moveY]->charValue != '@') {
    //mark the character as battled
    characterTable[moveX][moveY]->isBattled = 1;
    //open a new window
    WINDOW *newWindow = newwin(100, 100, 1, 0);
    refresh();
    wprintw(newWindow, "You have entered a Battle");
    wrefresh(newWindow);
    //wait for esc
    while (in != 27) {
      char c = getch();
      in = c;
    }
    //close the window
    delwin(newWindow);
    //if we are running into a character that has already been battled
  } else if (characterTable[moveX][moveY] && characterTable[moveX][moveY]->isBattled == 1) {
    mvprintw(22, 0, "You have already battled this character and can't move there.");
    int x = currX;
    int y = currY;
    int nextTurn = pc->nextTurn;
    popCharQ(characterQ);
    pushCharQ(characterQ, 1, 0, nextTurn, 0, x, y, '@', -1, 0);
  } else {
    
  

  //I CAN PROBABLY REMOVE THIS IF CHECK NOW
  //if there isn't a character in the direction we are moving
  // if (characterTable[moveX][moveY] == NULL) {
    //move the pc
    free(characterTable[currX][currY]);
    characterTable[currX][currY] = NULL;
    Character * character = newCharacterForCharacterMap(moveX, moveY, '@', 0);
    characterTable[moveX][moveY] = character;

    //find the time for next turn
    int timeToAdd = costOfTerrainPC(moveX, moveY, w);
    int nextTurn = pc->nextTurn + timeToAdd;

    //put the pc back in the queue
    int x = moveX;
    int y = moveY;
    //pop from the Q
    popCharQ(characterQ);
    //push back into the Q
    pushCharQ(characterQ, 1, 0, nextTurn, 0, x, y, '@', -1, 0);

    //update the world
    // w->playerCharX = moveX;
    // w->playerCharY = moveY;
    //I only need to do this the first time
    // w->t[currX][currY] = 3;

    //update the distance maps
    createDistanceMaps(w, hikerDistance, rivalDistance, characterTable);
  // } else {
  //   //there is a character in that spot

  // }

  mvprintw(22, 0, "                                                              ");
  }

  hasMovedMapsOnLastMove = 0;
}

// void restPC(Character* pc, map_t * w, int characterTable[21][80], int hikerDistance[21][80], int rivalDistance[21][80], int xChange, int yChange, Character** characterQ) {

// }
// Character* table[21][80], map_t *w, int c, Character* characterQ, int direction
void placeNPCs(int numCharactersFromInput, map_t* w){

  int numCharactersAdded = 0;

    switch (numCharactersFromInput) {

  //10	
  case 10 :
      //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(w->characterTable, w, 11, w->characterQ, -1);

    //place one Rival
      //Rival = 12 -> r
    placeNPC(w->characterTable, w, 12, w->characterQ, -1);

    // //place two Pacers
    //   //Pacer -> 13 = p
    placeNPC(w->characterTable, w, 13, w->characterQ, -1);
    placeNPC(w->characterTable, w, 13, w->characterQ, -1);

    // //place two Wanderers
    //   //Wanderer -> 14 = w
    placeNPC(w->characterTable, w, 14, w->characterQ, -1);
    placeNPC(w->characterTable, w, 14, w->characterQ, -1);

    // //place two Sentries
    //   //Sentry -> 15 = "s"
    placeNPC(w->characterTable, w, 15, w->characterQ, -1);
    placeNPC(w->characterTable, w, 15, w->characterQ, -1);
    
    // //place two Explorers
    //   //Explorer -> 16 = "e"
    placeNPC(w->characterTable, w, 16, w->characterQ, -1);
    placeNPC(w->characterTable, w, 16, w->characterQ, -1);
    break;
  //1  
  case 1 :
    //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(w->characterTable, w, 11, w->characterQ, -1);
    break;
  //2  
  case 2 :
    //do something
    //place one Hikers
    //Hiker = 11 -> h
    placeNPC(w->characterTable, w, 11, w->characterQ, -1);
    //place one Rival
    //Rival = 12 -> r
    placeNPC(w->characterTable, w, 12, w->characterQ, -1);
    break;
  default : 
    //do something
    while (numCharactersAdded < numCharactersFromInput) {
      if (numCharactersAdded < numCharactersFromInput) {
        //place one Hikers
        //Hiker = 11 -> h
        placeNPC(w->characterTable, w, 11, w->characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //place one Rival
        //Rival = 12 -> r
        placeNPC(w->characterTable, w, 12, w->characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Pacer -> 13 = p
        placeNPC(w->characterTable, w, 13, w->characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Wanderer -> 14 = w
        placeNPC(w->characterTable, w, 14, w->characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Sentry -> 15 = "s"
        placeNPC(w->characterTable, w, 15, w->characterQ, -1);
        numCharactersAdded++;
      }

      if (numCharactersAdded < numCharactersFromInput) {
        //   //Explorer -> 16 = "e"
        placeNPC(w->characterTable, w, 16, w->characterQ, -1);
        numCharactersAdded++;
      }
    }
}
}

//    std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str) {
//     std::vector<std::string>   result;
//     std::string                line;
//     std::getline(str,line);

//     std::stringstream          lineStream(line);
//     std::string                cell;

//     while(std::getline(lineStream,cell, ','))
//     {
//         result.push_back(cell);
//     }
//     // This checks for a trailing comma with no data after it.
//     if (!lineStream && cell.empty())
//     {
//         // If there was a trailing comma then add an empty element.
//         result.push_back("");
//     }
//     return result;
// }


// class CSVRow
// {
//     public:
//         std::string_view operator[](std::size_t index) const
//         {
//             return std::string_view(&m_line[m_data[index] + 1], m_data[index + 1] -  (m_data[index] + 1));
//         }
//         std::size_t size() const
//         {
//             return m_data.size() - 1;
//         }
//         void readNextRow(std::istream& str)
//         {
//             std::getline(str, m_line);

//             m_data.clear();
//             m_data.emplace_back(-1);
//             std::string::size_type pos = 0;
//             while((pos = m_line.find(',', pos)) != std::string::npos)
//             {
//                 m_data.emplace_back(pos);
//                 ++pos;
//             }
//             // This checks for a trailing comma with no data after it.
//             pos   = m_line.size();
//             m_data.emplace_back(pos);
//         }
//     private:
//         std::string         m_line;
//         std::vector<int>    m_data;
// };

// std::istream& operator>>(std::istream& str, CSVRow& data)
// {
//     data.readNextRow(str);
//     return str;
// }  

void parseFile(string filesToParse) {

  int success = 0;
  
  if (filesToParse == "type_names") {
    success = 1;
    ifstream inputFile;
     inputFile.open("/share/cs327/pokedex/pokedex/data/csv/type_names.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/type_names.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/type_names.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<type_names> structs;

      while(getline(inputFile, line)) {
        type_names tn;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter
        //check to see if there is something there
        if (temp != "") {
          tn.type_id = stoi(temp);
        } else {
          tn.type_id = INT_MAX;
        }
        temp = "";

        //second parameter
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          tn.local_language_id = stoi(temp);
        } else {
          tn.local_language_id = INT_MAX;
        }
        temp = "";

        //third parameter
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          tn.name = temp;
        } else {
          tn.name = "";
        }
        temp = "";

        if (tn.local_language_id == 9) {
          structs.push_back(tn);
        }
        
        line = "";
      }

      for (type_names entry : structs) {
        printf("%d %d %s\n", entry.type_id == INT_MAX ? -99 : entry.type_id, entry.local_language_id == INT_MAX ? -99 : entry.local_language_id, entry.name.c_str());
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

    if (filesToParse == "pokemon") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/pokemon.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/pokemon.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/pokemon.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<pokemon> structs;

      while(getline(inputFile, line)) {
        pokemon p;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = id int
        //check to see if there is something there
        if (temp != "") {
          p.id = stoi(temp);
        } else {
          p.id = INT_MAX;
        }
        temp = "";

        //second parameter = identifier string
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.identifier = temp;
        } else {
          p.identifier = "";
        }
        temp = "";

        //third parameter = species int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.species_id = stoi(temp);
        } else {
          p.species_id = INT_MAX;
        }
        temp = "";

        //fourth parameter = height int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.height = stoi(temp);
        } else {
          p.height = INT_MAX;
        }
        temp = "";

        //fifth parameter = weight int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.weight = stoi(temp);
        } else {
          p.weight = INT_MAX;
        }
        temp = "";

        //sixth parameter = base_experience int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.base_experience = stoi(temp);
        } else {
          p.base_experience = INT_MAX;
        }
        temp = "";

        //seventh parameter = order int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.order = stoi(temp);
        } else {
          p.order = INT_MAX;
        }
        temp = "";

        //eigth parameter = is_default int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          p.is_default = stoi(temp);
        } else {
          p.is_default = INT_MAX;
        }
        temp = "";

          
        structs.push_back(p);
        
        line = "";
      }

      for (pokemon entry : structs) {
        printf("%d %s %d %d %d %d %d %d\n", entry.id == INT_MAX ? -99 : entry.id, entry.identifier.c_str(), entry.species_id == INT_MAX ? -99 : entry.species_id, entry.height ==  INT_MAX ? -99 : entry.height, entry.weight == INT_MAX ? -99 : entry.weight, entry.base_experience == INT_MAX ? -99 : entry.base_experience, entry.order == INT_MAX ? -99 : entry.order, entry.is_default == INT_MAX ? -99 : entry.is_default);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "moves") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/moves.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/moves.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/moves.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<moves> structs;

      while(getline(inputFile, line)) {
        moves m;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = id int
        //check to see if there is something there
        if (temp != "") {
          m.id = stoi(temp);
        } else {
          m.id = INT_MAX;
        }
        temp = "";

        //second parameter = identifier string
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.identifier = temp;
        } else {
          m.identifier = "";
        }
        temp = "";

        //third parameter = generation_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.generation_id = stoi(temp);
        } else {
          m.generation_id = INT_MAX;
        }
        temp = "";

        //fourth parameter = type_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.type_id = stoi(temp);
        } else {
          m.type_id = INT_MAX;
        }
        temp = "";

        //fifth parameter = power int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.power = stoi(temp);
        } else {
          m.power = INT_MAX;
        }
        temp = "";

        //sixth parameter = pp int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.pp = stoi(temp);
        } else {
          m.pp = INT_MAX;
        }
        temp = "";

        //seventh parameter = accuracy int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.accuracy = stoi(temp);
        } else {
          m.accuracy = INT_MAX;
        }
        temp = "";

        //eigth parameter = priority int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.priority = stoi(temp);
        } else {
          m.priority = INT_MAX;
        }
        temp = "";

        //ninth parameter = target_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.target_id = stoi(temp);
        } else {
          m.target_id = INT_MAX;
        }
        temp = "";

        //tenth parameter = damage_class_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.damage_class_id = stoi(temp);
        } else {
          m.damage_class_id = INT_MAX;
        }
        temp = "";

        //eleventh parameter = effect_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.effect_id = stoi(temp);
        } else {
          m.effect_id = INT_MAX;
        }
        temp = "";

        //twelth parameter = effect_chance int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.effect_chance = stoi(temp);
        } else {
          m.effect_chance = INT_MAX;
        }
        temp = "";

        //thirtieen parameter = contest_type_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.contest_type_id = stoi(temp);
        } else {
          m.contest_type_id = INT_MAX;
        }
        temp = "";

        //fourteenth parameter = contest_effect_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.contest_effect_id = stoi(temp);
        } else {
          m.contest_effect_id = INT_MAX;
        }
        temp = "";

        //fifteenth parameter = super_contest_effect_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          m.super_contest_effect_id = stoi(temp);
        } else {
          m.super_contest_effect_id = INT_MAX;
        }
        temp = "";

          
        structs.push_back(m);
        
        line = "";
      }

      for (moves entry : structs) {
        printf("%d %s %d %d %d %d %d %d %d %d %d %d %d %d %d\n", entry.id == INT_MAX ? -99 : entry.id, entry.identifier.c_str(), entry.generation_id == INT_MAX ? -99 : entry.generation_id, entry.type_id == INT_MAX ? -99 : entry.type_id, entry.power == INT_MAX ? -99 : entry.power, entry.pp == INT_MAX ? -99 : entry.pp, entry.accuracy == INT_MAX ? -99 : entry.accuracy, entry.priority == INT_MAX ? -99 : entry.priority, entry.target_id == INT_MAX ? -99 : entry.target_id, entry.damage_class_id == INT_MAX ? -99 : entry.damage_class_id, entry.effect_id == INT_MAX ? -99 : entry.effect_id, entry.effect_chance == INT_MAX ? -99 : entry.effect_chance, entry.contest_type_id == INT_MAX ? -99 : entry.contest_type_id, entry.contest_effect_id == INT_MAX ? -99 : entry.contest_effect_id, entry.super_contest_effect_id == INT_MAX ? -99 : entry.super_contest_effect_id);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

    if (filesToParse == "pokemon_moves") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_moves.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/pokemon_moves.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/pokemon_moves.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<pokemon_moves> structs;

      while(getline(inputFile, line)) {
        pokemon_moves pm;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = pokemon_id int
        //check to see if there is something there
        if (temp != "") {
          pm.pokemon_id = stoi(temp);
        } else {
          pm.pokemon_id = INT_MAX;
        }
        temp = "";

        //second parameter = version_group_id
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pm.version_group_id = stoi(temp);
        } else {
          pm.version_group_id = INT_MAX;
        }
        temp = "";

        //third parameter = move_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pm.move_id = stoi(temp);
        } else {
          pm.move_id = INT_MAX;
        }
        temp = "";

        //fourth parameter = pokemon_move_method_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pm.pokemon_move_method_id = stoi(temp);
        } else {
          pm.pokemon_move_method_id = INT_MAX;
        }
        temp = "";

        //fifth parameter = level int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pm.level = stoi(temp);
        } else {
          pm.level = INT_MAX;
        }
        temp = "";

        //sixth parameter = order int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pm.order = stoi(temp);
        } else {
          pm.order = INT_MAX;
        }
        temp = "";

        structs.push_back(pm);
        
        line = "";
      }

      for (pokemon_moves entry : structs) {
        printf("%d %d %d %d %d %d\n", entry.pokemon_id == INT_MAX ? -99 : entry.pokemon_id, entry.version_group_id == INT_MAX ? -99 : entry.version_group_id, entry.move_id == INT_MAX ? -99 : entry.move_id, entry.pokemon_move_method_id == INT_MAX ? -99 : entry.pokemon_move_method_id, entry.level == INT_MAX ? -99 : entry.level, entry.order == INT_MAX ? -99 : entry.order);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "pokemon_species") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_species.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/pokemon_species.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/pokemon_species.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<pokemon_species> structs;

      while(getline(inputFile, line)) {
        pokemon_species ps;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = id int
        //check to see if there is something there
        if (temp != "") {
          ps.id = stoi(temp);
        } else {
          ps.id = INT_MAX;
        }
        temp = "";

        //second parameter = identifier string
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.identifier = temp;
        } else {
          ps.identifier = "";
        }
        temp = "";

        //third parameter = generation_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.generation_id = stoi(temp);
        } else {
          ps.generation_id = INT_MAX;
        }
        temp = "";

        //fourth parameter = evolves_from_species_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.evolves_from_species_id = stoi(temp);
        } else {
          ps.evolves_from_species_id = INT_MAX;
        }
        temp = "";

        //fifth parameter = evolution_chain_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.evolution_chain_id = stoi(temp);
        } else {
          ps.evolution_chain_id = INT_MAX;
        }
        temp = "";

        //sixth parameter = color id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.color_id = stoi(temp);
        } else {
          ps.color_id = INT_MAX;
        }
        temp = "";

        //seventh parameter = shape_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.shape_id = stoi(temp);
        } else {
          ps.shape_id = INT_MAX;
        }
        temp = "";

        //eigth parameter = habitat_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.habitat_id = stoi(temp);
        } else {
          ps.habitat_id = INT_MAX;
        }
        temp = "";

        //ninth parameter = gender_rate int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.gender_rate = stoi(temp);
        } else {
          ps.gender_rate = INT_MAX;
        }
        temp = "";

        //tenth parameter = capture_rate int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.capture_rate = stoi(temp);
        } else {
          ps.capture_rate = INT_MAX;
        }
        temp = "";

        //eleventh parameter = base_happiness int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.base_happiness = stoi(temp);
        } else {
          ps.base_happiness = INT_MAX;
        }
        temp = "";

        //twelth parameter = is_baby int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.is_baby = stoi(temp);
        } else {
          ps.is_baby = INT_MAX;
        }
        temp = "";

        //thirtieen parameter = hatch_counter int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.hatch_counter = stoi(temp);
        } else {
          ps.hatch_counter = INT_MAX;
        }
        temp = "";

        //fourteenth parameter = has_gender_differences int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.has_gender_differences = stoi(temp);
        } else {
          ps.has_gender_differences = INT_MAX;
        }
        temp = "";

        //fifteenth parameter = growth_rate_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.growth_rate_id = stoi(temp);
        } else {
          ps.growth_rate_id = INT_MAX;
        }
        temp = "";

        //sixteenth parameter = forms_switchable int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.forms_switchable = stoi(temp);
        } else {
          ps.forms_switchable = INT_MAX;
        }
        temp = "";

        //seventeenth = is_legendary int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.is_legendary = stoi(temp);
        } else {
          ps.is_legendary = INT_MAX;
        }
        temp = "";

        //eighteenth parameter = is_mythical int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.is_mythical = stoi(temp);
        } else {
          ps.is_mythical = INT_MAX;
        }
        temp = "";

        //nineteenth parameter = order int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.order = stoi(temp);
        } else {
          ps.order = INT_MAX;
        }
        temp = "";

        //twentieth parameter = conquest_order int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.conquest_order = stoi(temp);
        } else {
          ps.conquest_order = INT_MAX;
        }
        temp = "";

          
        structs.push_back(ps);
        
        line = "";
      }

      for (pokemon_species entry : structs) {
        printf("%d %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", entry.id == INT_MAX ? -99 : entry.id, entry.identifier.c_str(), entry.generation_id == INT_MAX ? -99 : entry.generation_id, entry.evolves_from_species_id == INT_MAX ? -99 : entry.evolves_from_species_id, entry.evolution_chain_id == INT_MAX ? -99 : entry.evolution_chain_id, entry.color_id == INT_MAX ? -99 : entry.color_id, entry.shape_id == INT_MAX ? -99 : entry.shape_id, entry.habitat_id == INT_MAX ? -99 : entry.habitat_id, entry.gender_rate == INT_MAX ? -99 : entry.gender_rate, entry.capture_rate == INT_MAX ? -99 : entry.capture_rate, entry.base_happiness == INT_MAX ? -99 : entry.base_happiness, entry.is_baby == INT_MAX ? -99 : entry.is_baby, entry.hatch_counter == INT_MAX ? -99 : entry.hatch_counter, entry.has_gender_differences == INT_MAX ? -99 : entry.has_gender_differences, entry.growth_rate_id == INT_MAX ? -99 : entry.growth_rate_id, entry.forms_switchable == INT_MAX ? -99 : entry.forms_switchable, entry.is_legendary == INT_MAX ? -99 : entry.is_legendary, entry.is_mythical == INT_MAX ? -99 : entry.is_mythical, entry.order == INT_MAX ? -99 : entry.order, entry.conquest_order == INT_MAX ? -99 : entry.conquest_order);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "experience") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/experience.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/experience.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/experience.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<experience> structs;

      while(getline(inputFile, line)) {
        experience e;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = growth_rate_id int
        //check to see if there is something there
        if (temp != "") {
          e.growth_rate_id = stoi(temp);
        } else {
          e.growth_rate_id = INT_MAX;
        }
        temp = "";

        //second parameter = level int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          e.level = stoi(temp);
        } else {
          e.level = INT_MAX;
        }
        temp = "";

        //third parameter = experience int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          e.experience = stoi(temp);
        } else {
          e.experience = INT_MAX;
        }
        temp = "";

        structs.push_back(e);
        
        line = "";
      }

    for (experience entry : structs) {
        printf("%d %d %d\n", entry.growth_rate_id == INT_MAX ? -99 : entry.growth_rate_id, entry.level == INT_MAX ? -99 : entry.level, entry.experience == INT_MAX ? -99 : entry.experience);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "pokemon_stats") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_stats.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/pokemon_stats.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/pokemon_stats.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<pokemon_stats> structs;

      while(getline(inputFile, line)) {
        pokemon_stats ps;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = pokemon_id int
        //check to see if there is something there
        if (temp != "") {
          ps.pokemon_id = stoi(temp);
        } else {
          ps.pokemon_id = INT_MAX;
        }
        temp = "";

        //second parameter = stat_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.stat_id = stoi(temp);
        } else {
          ps.stat_id = INT_MAX;
        }
        temp = "";

        //third parameter = base_stat int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.base_stat = stoi(temp);
        } else {
          ps.base_stat = INT_MAX;
        }
        temp = "";

        //fourth parameter = effort int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          ps.effort = stoi(temp);
        } else {
          ps.effort = INT_MAX;
        }
        temp = "";

        structs.push_back(ps);
        
        line = "";
      }

    for (pokemon_stats entry : structs) {
        printf("%d %d %d %d\n", entry.pokemon_id == INT_MAX ? -99 : entry.pokemon_id, entry.stat_id == INT_MAX ? -99 : entry.pokemon_id, entry.base_stat == INT_MAX ? -99 : entry.base_stat, entry.effort == INT_MAX ? -99 : entry.effort);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "stats") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/stat.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/stats.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/stats.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<stats> structs;

      while(getline(inputFile, line)) {
        stats s;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = id int
        //check to see if there is something there
        if (temp != "") {
          s.id = stoi(temp);
        } else {
          s.id = INT_MAX;
        }
        temp = "";

        //second parameter = damage_class_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          s.damage_class_id = stoi(temp);
        } else {
          s.damage_class_id = INT_MAX;
        }
        temp = "";

        //third parameter = identifier string
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          s.identifier = temp;
        } else {
          s.identifier = "";
        }
        temp = "";

        //fourth parameter = is_battle_only int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          s.is_battle_only = stoi(temp);
        } else {
          s.is_battle_only = INT_MAX;
        }
        temp = "";

        //fifth parameter = game_index int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          s.game_index = stoi(temp);
        } else {
          s.game_index = INT_MAX;
        }
        temp = "";

        structs.push_back(s);
        
        line = "";
      }

      for (stats entry : structs) {
        printf("%d %d %s %d %d\n", entry.id == INT_MAX ? -99 : entry.id, entry.damage_class_id == INT_MAX ? -99 : entry.damage_class_id, entry.identifier.c_str(), entry.is_battle_only == INT_MAX ? -99 : entry.is_battle_only, entry.game_index == INT_MAX ? -99 : entry.game_index);
      }
    }

    // } else {
    //     // printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (filesToParse == "pokemon_types") {
    success = 1;
    ifstream inputFile;
    inputFile.open("/share/cs327/pokedex/pokedex/data/csv/pokemon_types.csv");
    if (!inputFile.good()) {
      int i = (strlen(getenv("HOME")) + strlen("/.poke327/pokedex/pokedex/data/csv/pokemon_types.csv") + 1);
      char* prefix;
      prefix = (char*) malloc(i);
      strcpy(prefix, getenv("HOME"));
      strcat(prefix, "/.poke327/pokedex/pokedex/data/csv/pokemon_types.csv");
      inputFile.open(prefix);
    }

    //check to see if the file is found
    if (inputFile.good()) {
      // std::cout << "You have found the file" << std::endl;
      string line = "";
      getline(inputFile, line);

      vector<pokemon_types> structs;

      while(getline(inputFile, line)) {
        pokemon_types pt;
        string temp = "";
        stringstream stream(line);
        getline(stream, temp, ',');

        //first parameter = pokemon_id int
        //check to see if there is something there
        if (temp != "") {
          pt.pokemon_id = stoi(temp);
        } else {
          pt.pokemon_id = INT_MAX;
        }
        temp = "";

        //second parameter = type_id int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pt.type_id = stoi(temp);
        } else {
          pt.type_id = INT_MAX;
        }
        temp = "";

        //third parameter = slot int
        getline(stream, temp, ',');
        //check to see if there is something there
        if (temp != "") {
          pt.slot = stoi(temp);
        } else {
          pt.slot = INT_MAX;
        }
        temp = "";

        structs.push_back(pt);
        
        line = "";
      }

    for (pokemon_types entry : structs) {
        printf("%d %d %d\n", entry.pokemon_id == INT_MAX ? -99 : entry.pokemon_id, entry.type_id == INT_MAX ? -99 : entry.type_id, entry.slot == INT_MAX ? -99 : entry.slot);
      }
    }
    // } else {
    //     printf("File Not Found");
    //   // cout << "File Not Found" << endl;
    // }

  }

  if (success == 0) {
    printf("File Not Found\n");
  }

  
}

int main(int argc, char *argv[]) {

  // //find the file
  //  std::ifstream file("/share/cs327/pokedex/pokedex/data/csv/pokemon_moves.csv");

  //  if (file.good()) {
  //   std::cout << "You have found the file" << std::endl;
  //  }

  // // vector<vector<string>> content;
  // // vector<string> row;
  // // string line, word;

  // //  line = getNextLineAndSplitIntoTokens(file);

  // //  std::cout << line << std::endl;

  //   CSVRow row;
  //   int counter = 0;
  //   int i = 0;

  //   file >> row;

  //   // for (i = 0; i < 6; i++) {
  //   while(file >> row && i < 5) {
  //     for (int j = 0; j < row.size(); j++) {
  //       std::cout << row[j] << " | ";
  //     }
  //     // std::cout << row[row.size()];
  //     std::cout << std::endl;
  //       // std::cout << row[0] << " | " << row[1] << " | "  << row[2] << " | "  << row[3] << " | "  << row[4] << std::endl;
  //       // counter++;
  //       // i++;
  //       counter++;
  //       i++;
  //   }

  //   std::cout << counter << std::endl;

  string input = argv[1];

  // string input = "type_names";

  parseFile(input);

  // ifstream inputFile;
  // inputFile.open("/share/cs327/pokedex/pokedex/data/csv/type_names.csv");



  
//   //seed randomizer
//   // srand(time(NULL));
//   time_t seconds;
//     time(&seconds);
//     // seconds = 1666754381;
//   printf("Seed: %ld\n", seconds);
//     srand(seconds);

//   //we will have an array of pointers
//   //our world will measure 401x401
 
//   map_t *w[401][401];
//   int i;
//   int j;
//   // int inputX;
//   // int inputY;
//   //initialize world to null
//   for (i = 0; i < 401; i++) {
//     for (j = 0; j < 401; j++) {
//       w[i][j] = NULL;
//     }
//   }

//   //find random numbers for your roads
//   int xRoad = getRandomNumber(19);
//   int yRoad = getRandomNumber(78);

//   //make our initial map
//   if(w[200][200] == NULL) {
//     //w[200][200] = malloc(sizeof(*map_t));
//     w[200][200] = new map_t();
//     w[200][200]->x = xRoad;
//     w[200][200]->y = yRoad;
//     terrain_init(w[200][200], 200, 200);
//   }

//   //make a map to store location of characters
//   // Character * characterTable[21][80];
//   // int characterTable[21][80];
//   // setTableTo0(characterTable);

//   //Place my player Character
//   //Player Character is on the terrain map!!!
//   //player character = 10 -> @
//   placePlayerCharacter(w[200][200], xRoad, yRoad, w[200][200]->characterTable);
  
//   //initialize character queue and put pc in the queue
//   // Character* characterQ = newCharacter(1, 0, 0, 0, w[200][200]->playerCharX, w[200][200]->playerCharY, '@', -1, 0);
//   w[200][200]->characterQ = newCharacter(1, 0, 0, 0, w[200][200]->playerCharX, w[200][200]->playerCharY, '@', -1, 0);

//   //default the number of characters to 10
//   int numCharactersFromInput = 10;

//   // int numCharactersAdded = 0;

//   //if the number of characters is provided
//   // (!strcmp(argv[i], "--fps")
//   for (int i = 0; i < argc; i++) {
//     //update the number of characters
//     if (strcmp(argv[i], "--numtrainers") == 0) {
//       numCharactersFromInput = atoi(argv[i + 1]);
//       break;
//     }
//   }

//   placeNPCs(numCharactersFromInput, w[200][200]);

// //   switch (numCharactersFromInput) {

// //   //10	
// //   case 10 :
// //       //do something
// //     //place one Hikers
// //     //Hiker = 11 -> h
// //     placeNPC(w[200][200]->characterTable, w[200][200], 11, w[200][200]->characterQ, -1);

// //     //place one Rival
// //       //Rival = 12 -> r
// //     placeNPC(w[200][200]->characterTable, w[200][200], 12, w[200][200]->characterQ, -1);

// //     // //place two Pacers
// //     //   //Pacer -> 13 = p
// //     placeNPC(w[200][200]->characterTable, w[200][200], 13, w[200][200]->characterQ, -1);
// //     placeNPC(w[200][200]->characterTable, w[200][200], 13, w[200][200]->characterQ, -1);

// //     // //place two Wanderers
// //     //   //Wanderer -> 14 = w
// //     placeNPC(w[200][200]->characterTable, w[200][200], 14, w[200][200]->characterQ, -1);
// //     placeNPC(w[200][200]->characterTable, w[200][200], 14, w[200][200]->characterQ, -1);

// //     // //place two Sentries
// //     //   //Sentry -> 15 = "s"
// //     placeNPC(w[200][200]->characterTable, w[200][200], 15, w[200][200]->characterQ, -1);
// //     placeNPC(w[200][200]->characterTable, w[200][200], 15, w[200][200]->characterQ, -1);
    
// //     // //place two Explorers
// //     //   //Explorer -> 16 = "e"
// //     placeNPC(w[200][200]->characterTable, w[200][200], 16, w[200][200]->characterQ, -1);
// //     placeNPC(w[200][200]->characterTable, w[200][200], 16, w[200][200]->characterQ, -1);
// //     break;
// //   //1  
// //   case 1 :
// //     //do something
// //     //place one Hikers
// //     //Hiker = 11 -> h
// //     placeNPC(w[200][200]->characterTable, w[200][200], 11, w[200][200]->characterQ, -1);
// //     break;
// //   //2  
// //   case 2 :
// //     //do something
// //     //place one Hikers
// //     //Hiker = 11 -> h
// //     placeNPC(w[200][200]->characterTable, w[200][200], 11, w[200][200]->characterQ, -1);
// //     //place one Rival
// //     //Rival = 12 -> r
// //     placeNPC(w[200][200]->characterTable, w[200][200], 12, w[200][200]->characterQ, -1);
// //     break;
// //   default : 
// //     //do something
// //     while (numCharactersAdded < numCharactersFromInput) {
// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //place one Hikers
// //         //Hiker = 11 -> h
// //         placeNPC(w[200][200]->characterTable, w[200][200], 11, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }

// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //place one Rival
// //         //Rival = 12 -> r
// //         placeNPC(w[200][200]->characterTable, w[200][200], 12, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }

// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //   //Pacer -> 13 = p
// //         placeNPC(w[200][200]->characterTable, w[200][200], 13, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }

// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //   //Wanderer -> 14 = w
// //         placeNPC(w[200][200]->characterTable, w[200][200], 14, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }

// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //   //Sentry -> 15 = "s"
// //         placeNPC(w[200][200]->characterTable, w[200][200], 15, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }

// //       if (numCharactersAdded < numCharactersFromInput) {
// //         //   //Explorer -> 16 = "e"
// //         placeNPC(w[200][200]->characterTable, w[200][200], 16, w[200][200]->characterQ, -1);
// //         numCharactersAdded++;
// //       }
// //     }
// // }

//   //print the initial map
//   // printTable(w[200][200]->t, characterTable);
//   worldX = 200;
//   worldY = 200;
//   // printLocation(xCoord, yCoord);

//   int hikerDistance[21][80];
//   int rivalDistance[21][80];

//   createDistanceMaps(w[worldX][worldY], hikerDistance, rivalDistance, w[worldX][worldY]->characterTable);

//   // int cont = 1;
//   for (int i = 0; i < 401; i++) {
//     for (int j = 0; j < 401; j++) {
//       if (i == 200 && j == 200) {
//         continue;
//       } else {
//         w[i][j] = NULL;
//       }
//     }
//   }

//   io_init_terminal();

//   mvprintw(0, 0, "Where would you like to go?");
//   refresh();
//   // mvprintw(0,0, "Where would you like to go? e.g. 1, 2, 3, 4, ,6 ,7, 8, 9\n");
//   // mvprintw(0,0,"Hello world\n");
//   // char* s = printTable(w[200][200]->t, characterTable);
//   io_display(w[worldX][worldY]->t, w[worldX][worldY]->characterTable);

//   refresh(); //updates the terminal

//   char input = 'w';


//   while (input != 'Q' && counter < 1500) {

//     counter++;
    
//     Character* peeking = peekCharQ(&(w[worldX][worldY]->characterQ));
//     if (peeking->charValue == '@') {
//       io_display(w[worldX][worldY]->t, w[worldX][worldY]->characterTable);
//       // mvprintw(22, 0, "");
//       refresh();

//       input = getch();
//         //up
//        if (input == '8'  || input == 'k') {
//           // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, 0)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, -1, 0, &(w[worldX][worldY]->characterQ));
//             // } 

//           //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, 0)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, -1, 0 );
            
//           }
//            else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //down
//        } else if (input == '2' || input == 'j') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, 0)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 1, 0, &(w[worldX][worldY]->characterQ));
//             // } 
//             //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, 0)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, 1, 0 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //up and left
//        } else if (input == '7' || input == 'y') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, -1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, -1, -1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, -1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, -1, -1 );
            
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //up and right
//        } else if (input == '9' || input == 'u') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, 1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, -1, 1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], -1, 1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, -1, 1 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //right
//        } else if (input == '6' || input == 'l') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 0, 1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 0, 1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 0, 1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, 0, 1 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //right and down
//        } else if (input == '3' || input == 'n') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, 1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 1, 1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, 1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, 1, 1 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //down and left
//        } else if (input == '1' || input == 'b') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, -1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 1, -1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 1, -1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, 1, -1 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //left
//        } else if (input == '4' || input == 'h') {
//                   // check to see if we are in bounds and not hitting % or ^
//           if (validMove(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 0, -1)) {
//             //if it is not an NPC
//             // if (characterTable[peeking->xCoord - 1][peeking->yCoord] == 0) {
//               //move
//               movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 0, -1, &(w[worldX][worldY]->characterQ));
//             // } 
//                     //CHECK TO SEE IF YOU ARE MOVING TO ANOTHER MAP
//           } else if (movingMaps(peeking->xCoord, peeking->yCoord, w[worldX][worldY], 0, -1)) {
//             //we need to fly
//             flyOne(w, numCharactersFromInput, xRoad, yRoad, 0, -1 );
            
          
//           } else {
//             //can't move that direction
//             //print message
//             mvprintw(22, 0, "You can't go that direction");

//           }
//           //rest for a move
//        } else if (input == '5' || input == '.' || input == ' ') {
//           movePC(peeking, w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, rivalDistance, 0, 0, &(w[worldX][worldY]->characterQ));
//        } else if (input == 'Q') {
//         continue;
//        } else if (input == 'f') {
//           int inputFlyX;
//           int inputFlyY;
//           //we are flying
//           clear();
//           refresh();
//           mvprintw(0, 0, "Enter two integers separated by a space and hit ENTER");
//           mvscanw(0, 0, "%d %d", &inputFlyX, &inputFlyY);
//           //check for valid input
//           if (inputFlyX < -200 || inputFlyX > 200 || inputFlyY < -200 || inputFlyY > 200) {
//             // printTable(w[xCoord][yCoord]->t);
//             // printf("You can't go that direction\n");
//             // skipWhiteSpace();
//             mvprintw(22, 0, "You can't go that direction");
//             continue;
//           }
//           //otherwise we know are in bounds
//           //convert the input values
//           int worldXMove = 200 + inputFlyY;
//           int worldYMove = 200 + inputFlyX;
//           // xCoord = 200 + inputY;
//           // yCoord = 200 + inputX;
//           // fly(w, xRoad, yRoad, xCoord, yCoord);
//           fly(w, xRoad, yRoad, worldXMove, worldYMove, numCharactersFromInput);
//           // printTable(w[xCoord][yCoord]->t);
//           // printLocation(xCoord, yCoord);
//           // skipWhiteSpace();
//           // continue;
//        } else if (input == 't') {
//           //open a new window
//           WINDOW *newWindow = newwin(100, 100, 1, 0);
//           refresh();
//           wprintw(newWindow, "Here is a list of the NPC's\n");
//           wrefresh(newWindow);
//           int pcX;
//           int pcY;
//           for (int r = 0; r < 21; r++) {
//             for (int c = 0; c < 80; c++) {
//               if (w[worldX][worldY]->characterTable[r][c] && w[worldX][worldY]->characterTable[r][c]->charValue == '@') {
//                 pcX = r;
//                 pcY = c;
//               }
//             }
//           }
//           int counter = 0;
//           int downPress = 0;



//           //wait for esc
//           while (input != 27) {
//             int c = getch();
//             input = c;
//             if (counter > 0) {
//                           if (c == KEY_DOWN) {
//               downPress++;
//               counter = 0;
//               wclear(newWindow);
//               wrefresh(newWindow);
//           } else if (c == KEY_UP) {
//             downPress = 0;
//             counter = 0;
//             wclear(newWindow);
//             wrefresh(newWindow);
//           }
//             }

//             for (int r = 0; r < 21; r++) {
//             for (int c = 0; c < 80; c++) {

              
//               if (w[worldX][worldY]->characterTable[r][c] && w[worldX][worldY]->characterTable[r][c]->charValue != '@') {
//                 if (counter <= 20 + downPress && counter >= downPress) {
//                   int distX = pcX - w[worldX][worldY]->characterTable[r][c]->xCoord;
//                   int distY = pcY - w[worldX][worldY]->characterTable[r][c]->yCoord;
//                   // char c = characterTable[r][c]->charValue;
//                   wprintw(newWindow, "There is a %c with a distance of (%d , %d)\n", w[worldX][worldY]->characterTable[r][c]->charValue, distX, distY);
                  
//                   wrefresh(newWindow);
//                 }
//                 counter++;
//               }
              
//             }
//           }

//           }
//           //close the window
//           delwin(newWindow);
//        } else if (input == '>') {
//           //check to see if we are standing on a pokemart
//           if (w[worldX][worldY]->t[peeking->xCoord][peeking->yCoord] == 4) {
//             WINDOW *newWindow = newwin(100, 100, 1, 0);
//             refresh();
//             wprintw(newWindow, "You have entered a pokemart\n");
//             wrefresh(newWindow);

//             //wait for esc
//             while (input != '<') {
//               char c = getch();
//               input = c;
//             }
//             //close the window
//             delwin(newWindow);

//           } //check to see if we are standing on a pokecenter
//             else if (w[worldX][worldY]->t[peeking->xCoord][peeking->yCoord] == 5) {
//               WINDOW *newWindow = newwin(100, 100, 1, 0);
//               refresh();
//               wprintw(newWindow, "You have entered a pokecenter\n");
//               wrefresh(newWindow);

//               //wait for esc
//               while (input != '<') {
//                 char c = getch();
//                 input = c;
//               }
//               //close the window
//               delwin(newWindow);
//             }
//        }
      
//     } else if (peeking->charValue == 'h') {
//       int x = peeking->xCoord;
//       int y = peeking->yCoord;
//       if (w[worldX][worldY]->characterTable[x][y]->isBattled == 0) {
//         moveHiker(w[worldX][worldY], w[worldX][worldY]->characterTable, hikerDistance, &(w[worldX][worldY]->characterQ));
//       } else {
//         popCharQ(&(w[worldX][worldY]->characterQ));
//       }
      
//     } else if (peeking->charValue == 'r') {
//       int x = peeking->xCoord;
//       int y = peeking->yCoord;
//       if (w[worldX][worldY]->characterTable[x][y]->isBattled == 0) {
//         moveRival(w[worldX][worldY], w[worldX][worldY]->characterTable, rivalDistance, &(w[worldX][worldY]->characterQ));
//       } else {
//         popCharQ(&(w[worldX][worldY]->characterQ));
//       }
      
//     } else if (peeking->charValue == 's') {
//       moveSentry(w[worldX][worldY], w[worldX][worldY]->characterTable, &(w[worldX][worldY]->characterQ));
//     } else if (peeking->charValue == 'e') {
//       moveExplorer(w[worldX][worldY], w[worldX][worldY]->characterTable, &(w[worldX][worldY]->characterQ));
//     } else if (peeking->charValue == 'p') {
//       movePacer(w[worldX][worldY], w[worldX][worldY]->characterTable, &(w[worldX][worldY]->characterQ));
//     } else if (peeking->charValue == 'w') {
//       moveWanderer(w[worldX][worldY], w[worldX][worldY]->characterTable, &(w[worldX][worldY]->characterQ));
//     }
//   }

//   // int cont = 1;

//   // //run our program
//   // while (cont == 1) {
//   //   char chr;
//   //   printf("Enter a value: ");
//   //   scanf("%c",&chr);     
//   //   // printf("You entered %c.\n", chr);

//   //   if (chr == 'q') {
//   //     cont = 0;
//   //     printf("The game has ended");
//   //     skipWhiteSpace();
//   //     continue;
//   //   }
//   //   if (chr == 'f') {
//   //     scanf(" %d %d", &inputX, &inputY);
//   //     //check for valid input
//   //     if (inputX < -200 || inputX > 200 || inputY < -200 || inputY > 200) {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("You can't go that direction\n");
//   //       skipWhiteSpace();
//   //       continue;
//   //     }
//   //     //otherwise we know are in bounds
//   //     //convert the input values
//   //     xCoord = 200 + inputY;
//   //     yCoord = 200 + inputX;
//   //     fly(w, xRoad, yRoad, xCoord, yCoord);
//   //     printTable(w[xCoord][yCoord]->t);
//   //     printLocation(xCoord, yCoord);
//   //     skipWhiteSpace();
//   //     continue;
//   //   }
//   //   if (chr == 'n') {
//   //     //go up
//   //     if (xCoord == 0) {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("You can't go that direction\n");
//   //       skipWhiteSpace();
//   //       continue;
//   //     } else {
//   //       xCoord = xCoord - 1;
//   //       fly(w, xRoad, yRoad, xCoord, yCoord);
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printLocation(xCoord, yCoord);
//   //       //create our other maps
//   //       createDistanceMaps(w[xCoord][yCoord]);
//   //       skipWhiteSpace();
//   //       continue;
//   //     }
//   //   }
//   //   if (chr == 's') {
//   //     //go down
//   //     if (xCoord == 400) {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("You can't go that direction\n");
//   //       skipWhiteSpace();
//   //       continue;
//   //     } else {
//   //       xCoord = xCoord + 1;
//   //       fly(w, xRoad, yRoad, xCoord, yCoord);
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printLocation(xCoord, yCoord);
//   //       skipWhiteSpace();
//   //       continue;
//   //     }
//   //   }
//   //   if (chr == 'e') {
//   //     //go right
//   //     if (yCoord == 400) {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("You can't go that direction\n");
//   //       skipWhiteSpace();
//   //       continue;
//   //     } else {
//   //       yCoord = yCoord + 1;
//   //       fly(w, xRoad, yRoad, xCoord, yCoord);
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printLocation(xCoord, yCoord);
//   //       skipWhiteSpace();
//   //       continue;
//   //     }
//   //   }
//   //   if (chr == 'w') {
//   //     //go right
//   //     if (yCoord == 0) {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("You can't go that direction\n");
//   //       skipWhiteSpace();
//   //       continue;
//   //     } else {
//   //       yCoord = yCoord - 1;
//   //       fly(w, xRoad, yRoad, xCoord, yCoord);
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printLocation(xCoord, yCoord);
//   //       skipWhiteSpace();
//   //       continue;
//   //     }
//   //   } else {
//   //       printTable(w[xCoord][yCoord]->t);
//   //       printf("Incorrect Input\n");
//   //       printLocation(xCoord, yCoord);
//   //       skipWhiteSpace();
//   //       continue;
//   //   }

//   //   // int z = 1;
//   //   // while(z == 1) {
//   //   //   scanf("%c",&chr);
//   //   //   if (chr == '\n') {
//   //   //     z = 0;
//   //   //   }
//   //   // }
//   // } 

//   	endwin(); 
    return 0;


}

