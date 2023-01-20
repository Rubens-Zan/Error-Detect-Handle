#include "binary-tree.h"
#include "error-handle.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void copyPathAggregatedMessage(bit *prevPathMess, bit *levelMessage, bit *pathAggMess, unsigned int level, unsigned int packetSize){
    for (int i=0;i < (packetSize * level-1);++i){
        pathAggMess[i] = prevPathMess[i];
    }
    for (int i=packetSize * level-1;i < packetSize * level;++i){
        pathAggMess[i] = levelMessage[i - packetSize* level];
    }
};

tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState, unsigned int level, unsigned int packetSize, tNode *parentNode)
{
    tNode *n = (tNode *)malloc(sizeof(tNode));

    n->shouldContinue = true;
    n->pathError = curPathError; 
    n->left = NULL;
    n->right = NULL;
    n->receivedBit = inputBit;
    getNextState(curState, inputBit, n); // get next state according to the trellice diagram
    n->parent = parentNode; 
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

void getNextStep(tNode* root, unsigned int packetSize)
{
    int h = height(root);
    int i;
    getNextLeafOnLevel(root, h, packetSize, h);
}

void getNextLeafOnLevel(tNode* root, int level,unsigned int packetSize, unsigned int height)
{
    if (root == NULL)
        return;
    if (level == 0){
        root->left =  startNode(root->pathError, 0, root->curState, height,packetSize, root); 
        root->right = startNode(root->pathError, 1, root->curState, height,packetSize, root); 
    }
    else if (level > 0) {
        getNextLeafOnLevel(root->left, level - 1,packetSize,height);
        getNextLeafOnLevel(root->right, level - 1,packetSize,height);
    }
}

void getListLeafsHannigPathDistance(tNode* root, int level,unsigned int packetSize, unsigned int height, tNode** minHanningDistPathNode)
{
    if (root == NULL)
        return;
    if (level == 0){
        if ((*minHanningDistPathNode) != NULL){
            if (root->pathError < (*minHanningDistPathNode)->pathError )
                (*minHanningDistPathNode) = root;  
        }else {
            (*minHanningDistPathNode) = root; 
        }
        
    }
    else if (level > 0) {
        getListLeafsHannigPathDistance(root->left, level - 1,packetSize,height, minHanningDistPathNode);
        getListLeafsHannigPathDistance(root->right, level - 1,packetSize,height,minHanningDistPathNode);
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

        printf("(%s, %d)  |%d| ", root->correctedBits, root->receivedBit,root->pathError);
    }
    else if (level > 0) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
/****/



void getFullMessageDecoded(tNode* leaf){
    if (leaf->parent == NULL)
        return; 
    else {
        printf("%s ",leaf->parent->correctedBits); 
        getFullMessageDecoded(leaf->parent); 
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
