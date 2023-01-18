#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "terrain.h"

int getRandomNumber(int n){

  int r = rand() % n + 1;
  return r;
}

void printTable(int table[21][80]){

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
  printf("You are at (");
  printf("%d", y - 200);
  printf(" , ");
  printf("%d", x - 200);
  printf(") where would you like to go?\n");
}

void fly(map_t *w[401][401], int xRoad, int yRoad, int xCoord, int yCoord) {
  if(w[xCoord][yCoord] == NULL) {
    w[xCoord][yCoord] = malloc(sizeof(map_t));
    w[xCoord][yCoord]->x = xRoad;
    w[xCoord][yCoord]->y = yRoad;
    // terrain_init(w[xCoord][yCoord]);
    terrain_init(w[xCoord][yCoord], xCoord, yCoord); 
  }
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

int main(int argc, char *argv[]){
  
  //seed randomizer
  srand(time(NULL));

  //we will have an array of pointers
  //our world will measure 401x401
 
  map_t *w[401][401];
  int i;
  int j;
  int inputX;
  int inputY;
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
    // terrain_init(w[200][200], 200, 200); 
  }

  //print the initial map
  printTable(w[200][200]->t);
  int xCoord = 200;
  int yCoord = 200;
  printLocation(xCoord, yCoord);

  int cont = 1;

  //run our program
  while (cont == 1) {
    char chr;
    printf("Enter a value: ");
    scanf("%c",&chr);     
    // printf("You entered %c.\n", chr);

    if (chr == 'q') {
      cont = 0;
      printf("The game has ended");
      skipWhiteSpace();
      continue;
    }
    if (chr == 'f') {
      scanf(" %d %d", &inputX, &inputY);
      //check for valid input
      if (inputX < -200 || inputX > 200 || inputY < -200 || inputY > 200) {
        printTable(w[xCoord][yCoord]->t);
        printf("You can't go that direction\n");
        skipWhiteSpace();
        continue;
      }
      //otherwise we know are in bounds
      //convert the input values
      xCoord = 200 + inputY;
      yCoord = 200 + inputX;
      fly(w, xRoad, yRoad, xCoord, yCoord);
      printTable(w[xCoord][yCoord]->t);
      printLocation(xCoord, yCoord);
      skipWhiteSpace();
      continue;
    }
    if (chr == 'n') {
      //go up
      if (xCoord == 0) {
        printTable(w[xCoord][yCoord]->t);
        printf("You can't go that direction\n");
        skipWhiteSpace();
        continue;
      } else {
        xCoord = xCoord - 1;
        fly(w, xRoad, yRoad, xCoord, yCoord);
        printTable(w[xCoord][yCoord]->t);
        printLocation(xCoord, yCoord);
        skipWhiteSpace();
        continue;
      }
    }
    if (chr == 's') {
      //go down
      if (xCoord == 400) {
        printTable(w[xCoord][yCoord]->t);
        printf("You can't go that direction\n");
        skipWhiteSpace();
        continue;
      } else {
        xCoord = xCoord + 1;
        fly(w, xRoad, yRoad, xCoord, yCoord);
        printTable(w[xCoord][yCoord]->t);
        printLocation(xCoord, yCoord);
        skipWhiteSpace();
        continue;
      }
    }
    if (chr == 'e') {
      //go right
      if (yCoord == 400) {
        printTable(w[xCoord][yCoord]->t);
        printf("You can't go that direction\n");
        skipWhiteSpace();
        continue;
      } else {
        yCoord = yCoord + 1;
        fly(w, xRoad, yRoad, xCoord, yCoord);
        printTable(w[xCoord][yCoord]->t);
        printLocation(xCoord, yCoord);
        skipWhiteSpace();
        continue;
      }
    }
    if (chr == 'w') {
      //go right
      if (yCoord == 0) {
        printTable(w[xCoord][yCoord]->t);
        printf("You can't go that direction\n");
        skipWhiteSpace();
        continue;
      } else {
        yCoord = yCoord - 1;
        fly(w, xRoad, yRoad, xCoord, yCoord);
        printTable(w[xCoord][yCoord]->t);
        printLocation(xCoord, yCoord);
        skipWhiteSpace();
        continue;
      }
    } else {
        printTable(w[xCoord][yCoord]->t);
        printf("Incorrect Input\n");
        printLocation(xCoord, yCoord);
        skipWhiteSpace();
        continue;
    }

    // int z = 1;
    // while(z == 1) {
    //   scanf("%c",&chr);
    //   if (chr == '\n') {
    //     z = 0;
    //   }
    // }
  } 
    return 0;

    //TODO
    //are roads always the same when I move? - yes
    //handle "f" input
    //handle roads on boarders
    //handle pokemarts and pokecenters
    //fix display coordinates

}
