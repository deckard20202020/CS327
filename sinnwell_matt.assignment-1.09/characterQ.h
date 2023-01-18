// typedef struct character {
//     int isPC;
//     int isNPC;
//     int nextTurn;
//     int seqNum;
//     int xCoord;
//     int yCoord;
//     char charValue;
//     struct character* next;
//     int direction;
//     int isBattled;
// } Character;

#include "pm.h"
#include <vector>

#ifndef PM_H
#define PM_H

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
        vector<pokemon_class> pokemon;

        Character(){};

};

Character* newCharacter(int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled);
Character* newCharacterForCharacterMap(int xCoord, int yCoord, char charValue, int isBattled);
Character* peekCharQ(Character** head);
void popCharQ(Character** head);
void pushCharQ(Character** head, int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled);
int isEmptyCharQ(Character** head);

#endif
