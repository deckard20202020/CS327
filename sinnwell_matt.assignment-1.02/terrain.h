typedef struct map {

  int t[21][80];
  int x;
  int y;
} map_t;

typedef struct world {
  //need an array 401x401 that holds a bunch of pointers
  map_t *w[401][401];

} world_t;

void initializeTable(int table[21][80]);
    //void addBoarder(int table[21][80])
    //int getRandomNum(int n)
    //void growSeed(int table[21][80], int x, int y, int op)
    //void growSeeds(int table[21][80], int tallGrassX1, int tallGrassY1, int tallGrassX2, int tallGrassY2, int clearingX1, int clearingY1, int clearingX2, int clearingY2)
    //void pokeLocations(int table[21][80], int roadR, int roadC)
    // void terrain_init(map_t *p);

    void terrain_init(map_t *p, int, int);

    void make_Map(int x, int y, int t[21][80], int xc, int yc);
