typedef struct character {
    int isPC;
    int isNPC;
    int nextTurn;
    int seqNum;
    int xCoord;
    int yCoord;
    char charValue;
    struct character* next;
    int direction;
} Character;

Character* newCharacter(int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction);
Character* peekCharQ(Character** head);
void popCharQ(Character** head);
void pushCharQ(Character** head, int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction);
int isEmptyCharQ(Character** head);