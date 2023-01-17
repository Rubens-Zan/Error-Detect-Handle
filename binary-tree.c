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


/* Function to print level order traversal a tree*/
void printLevelOrder(tNode* root)
{
    int h = height(root);
    printf("\n");
    int i;
    for (i = 0; i <= h; i++){
        printCurrentLevel(root, i);
        printf("\n");
    }
}

void getNextStep(tNode* root)
{
    int h = height(root);
    int i;
    getNextLeafOnLevel(root, h);

}

void getNextLeafOnLevel(tNode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 0 && root->left == NULL && root->right == NULL){
        root->left =  startNode(root->pathError, 0, root->curState, level); 
        root->right = startNode(root->pathError, 1, root->curState, level); 
    }
    else if (level > 0) {
        getNextLeafOnLevel(root->left, level - 1);
        getNextLeafOnLevel(root->right, level - 1);
    }
}


/* Print nodes at a current level */
void printCurrentLevel(tNode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 0 ){
        if (root->curState == A)
            printf("A"); 
        if (root->curState == B)
            printf("B"); 
        if (root->curState == C)
            printf("C"); 
        if (root->curState == D)
            printf("D"); 
    }
    else if (level > 0) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
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
