
// #ifndef TERRAIN_H
// #define TERRAIN_H

#include "characterQ.h"

#ifndef TERRAIN_H
#define TERRAIN_H

class map_t {
  public :
    int t[21][80];
    int x;
    int y;
    int playerCharX;
    int playerCharY;
    int pcX;
    int pcY;
    Character* characterQ;
    Character* characterTable[21][80];

    map_t(){}

    //Don't think we need this
    // map_t(int t[21][80], int x, int y, int playerCharX, int playerCharY, int pcX, int pcY) {
    //   // this.t = t;
    //   this->x = x;
    //   this->y = y;
    //   this->playerCharX = playerCharX;
    //   this->playerCharY = playerCharY;
    //   this->pcX = pcX;
    //   this->pcY = pcY;
    // }
};

// typedef struct world {
//   //need an array 401x401 that holds a bunch of pointers
//   map_t *w[401][401];

// } world_t;

void initializeTable(int table[21][80]);
    //void addBoarder(int table[21][80])
    //int getRandomNum(int n)
    //void growSeed(int table[21][80], int x, int y, int op)
    //void growSeeds(int table[21][80], int tallGrassX1, int tallGrassY1, int tallGrassX2, int tallGrassY2, int clearingX1, int clearingY1, int clearingX2, int clearingY2)
    //void pokeLocations(int table[21][80], int roadR, int roadC)
    // void terrain_init(map_t *p);

    void terrain_init(map_t *p, int xCoord, int yCoord);

    void make_Map(int x, int y, int t[21][80], int xc, int yc);
    // void make_Map(int x, int y, int t[21][80], int xc, int yc, map_t *p);

#endif
