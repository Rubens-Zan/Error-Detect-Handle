#include "structs.h"

#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

unsigned int countNodes(tNode *n);
tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState, unsigned int level,bit *pathMessage, unsigned int packetSize);
unsigned int height(tNode *p); 
void emordem(tNode *no);
void printLevelOrder(tNode* root);
void printCurrentLevel(tNode* root, int level); 
void getNextStep(tNode* root, unsigned int packetSize);
void getNextLeafOnLevel(tNode* root, int level,unsigned int packetSize, unsigned int height);

#endif