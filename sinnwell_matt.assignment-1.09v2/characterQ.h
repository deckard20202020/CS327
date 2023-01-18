
// #ifndef CHARACTERQ_H
// #define CHARACTERQ_H

#include<vector>
#include "pm.h"

#ifndef CHARACTERQ_H
#define CHARACTERQ_H

class Character {
    public :
        int isPC;
        int isNPC;
        int nextTurn;
        int seqNum;
        int xCoord;
        int yCoord;
        char charValue;
        Character* next;
        int direction;
        int isBattled;
        vector<pokemon_class> pokemonVector;

        Character(){};

};

Character* newCharacter(int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled);
Character* newCharacterForCharacterMap(int xCoord, int yCoord, char charValue, int isBattled);
Character* peekCharQ(Character** head);
void popCharQ(Character** head);
void pushCharQ(Character** head, int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled);
int isEmptyCharQ(Character** head);
void pushInitialNPC(Character** head, int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled, int worldX, int worldY, Character * table[21][80]);

#endif