#include "structs.h"

#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

unsigned int countNodes(tNode *n);
tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState, unsigned int index );
unsigned int height(tNode *p); 
void beginLeafs(tNode *n, unsigned int curPathError, typesState curState, unsigned int index);

#endif