
#include <cstdio>
#include <cstdlib>
#include "characterQ.h"

Character* newCharacter(int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled){
    Character* temp = new Character();
    temp->isPC = isPC;
    temp->isNPC = isNPC;
    temp->nextTurn = nextTurn;
    temp->seqNum = seqNum;
    temp->xCoord = xCoord;
    temp->yCoord = yCoord;
    temp->charValue = charValue;
    temp->next = NULL;
    temp-> direction = direction;
    temp-> isBattled = isBattled;
 
    return temp;
}

Character* newCharacterForCharacterMap(int xCoord, int yCoord, char charValue, int isBattled) {
    Character* temp = new Character();
    temp->xCoord = xCoord;
    temp->yCoord = yCoord;
    temp->charValue = charValue;
    temp->isBattled = isBattled;

    return temp;
}

Character* peekCharQ(Character** head){
    return *head;
}

void popCharQ(Character** head){
    Character* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void pushCharQ(Character** head, int isPC, int isNPC, int nextTurn, int seqNum, int xCoord, int yCoord, char charValue, int direction, int isBattled){
    Character* start = (*head);
 
    // Create new Character
    Character* temp = newCharacter(isPC, isNPC, nextTurn, seqNum, xCoord, yCoord, charValue, direction, isBattled);
 
    // Special Case: The head of list has lesser
    // priority than new node. So insert new
    // node before head node and change head node.
    if ((*head)->nextTurn > nextTurn) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL &&
            start->next->nextTurn < nextTurn) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}

int isEmptyCharQ(Character** head)
{
    return (*head) == NULL;
}