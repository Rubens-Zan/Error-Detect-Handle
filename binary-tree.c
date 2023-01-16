#include "binary-tree.h"
#include "error-handle.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState, unsigned int index )
{
    tNode *n = (tNode *)malloc(sizeof(tNode));

    n->shouldContinue = true;
    n->pathError = curPathError; 
    n->left = NULL;
    n->right = NULL;
    n->receivedBit = inputBit;
    n->index = index; 
    getNextState(curState, inputBit, n); // get next state according to the trellice diagram

    printf("idx: %d %d->%d\n", n->index, curState, n->curState); 
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

void beginLeafs(tNode *n, unsigned int curPathError, typesState curState, unsigned int index)
{

    if (n->left != NULL && n->right != NULL)
    {   
        beginLeafs(n->left, n->pathError, n->curState,++index); 
        beginLeafs(n->right,n->pathError,n->curState,++index);
    }else {
        n->left = startNode(curPathError,0,curState,++index);
        n->right = startNode(curPathError,1,curState,++index);
    }
}

void emordem(tNode *no)
{
    if (no != NULL)
    {
        emordem(no->left);
        printf("%s  ", no->correctedBits);
        emordem(no->right);
    }
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
