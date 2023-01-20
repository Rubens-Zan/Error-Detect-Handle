#include <stdbool.h> 
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include "generate-message.h"

typedef struct tNode tNode;
struct tNode
{
    bit receivedBit;     // {1,0}
    bit correctedBits[3];  // "XY"
    typesState curState; // {A,B,C,D}
    tNode *parent; // Parent node
    tNode *left, *right; // Next path, being left if input is 0 and right 1
    bool shouldContinue; // determine if this path should be continued or not
    unsigned int pathError;
};

unsigned int countNodes(tNode *n);
tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState, unsigned int level, unsigned int packetSize, tNode *parentNode);
unsigned int height(tNode *p); 
void emordem(tNode *no);
void printLevelOrder(tNode* root);
void printCurrentLevel(tNode* root, int level); 
void getNextStep(tNode* root, unsigned int packetSize);
void getNextLeafOnLevel(tNode* root, int level,unsigned int packetSize, unsigned int height);
void getListLeafsHannigPathDistance(tNode* root, int level,unsigned int packetSize, unsigned int height, tNode** minHanningDistPathNode); 
void getFullMessageDecoded(tNode* leaf); 

#endif