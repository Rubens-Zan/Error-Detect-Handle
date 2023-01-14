#include "binary-tree.h"
#include "error-handle.h"
#include <stdlib.h>

tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState )
{
    tNode *n = (tNode *)malloc(sizeof(tNode));

    n->shouldContinue = true;
    n->pathError = curPathError; 
    n->left = NULL;
    n->right = NULL;
    n->receivedBit = inputBit;
    getNextState(curState, inputBit, n->curState, n->correctedBits); // get next state according to the trellice diagram
   
    return n;
}
/****/
unsigned int countNodes(tNode *n)
{
    if (n != NULL)
    {
        return countNodes(n->left) + countNodes(n->right) + 1;
    }
    else
        return 0;
}
/****/
unsigned int height(tNode *p)
{
    int he, hd;
    if (p == NULL)
        return -1;
    he = height(p->left);
    hd = height(p->right);
    if (he > hd)
        return he + 1;
    else
        return hd + 1;
}
