#include "error-handle.h"
#include "binary-tree.h"
#include "generate-message.h"
#include "list.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Get the next state object
 * PATH DIAGRAM ACCORDING IF RECEIVED 0 OR 1
 * A -> A,C 
 * B -> A,C
 * C -> B,D
 * D -> B,D
 * 
 * @param curState{A,B,C,D} - Current state of the path
 * @param receivedBit{0,1} - Received bit  
 * @param nextState{A,B,C,D} - Next state of the path
 */
void getNextState(typesState curState,unsigned int receivedBit,tNode *nextNode){
    // CHECK WHAT IS THE CURRENT STATES
    // printf("anterior: %d receiv: %d ",curState, receivedBit); 
    
    if (curState == A){
        if (receivedBit == 0){
            nextNode->curState = A;
            strcpy(nextNode->correctedBits, "00\0");
            // printf("A -> A corrigido %s \n", nextNode->correctedBits);
        }else {
            nextNode->curState = C;
            strcpy(nextNode->correctedBits, "11\0");
            // printf("A -> C corrigido %s \n", nextNode->correctedBits);
        }
    }
    if (curState == B){
        if (receivedBit == 0){
            nextNode->curState = A;
            strcpy(nextNode->correctedBits, "11\0");
            // printf("B -> A corrigido %s \n", nextNode->correctedBits);
        } else {
            nextNode->curState = C;
            strcpy(nextNode->correctedBits, "00\0");
            // printf("B -> C corrigido %s \n", nextNode->correctedBits);
        }
    }
    if (curState == C){
         if (receivedBit == 0){
            nextNode->curState = B;
            strcpy(nextNode->correctedBits, "10\0");
            // printf("C -> B corrigido %s \n", nextNode->correctedBits);

        }else {
            nextNode->curState = D;
            strcpy(nextNode->correctedBits, "01\0");
            // printf("C -> D corrigido %s \n", nextNode->correctedBits);
        }
    }
    if (curState == D){
        if (receivedBit == 0){
            nextNode->curState = B;
            strcpy(nextNode->correctedBits, "01\0");
            // printf("D -> B corrigido %s \n", nextNode->correctedBits);
        }else {
            nextNode->curState = D;
            strcpy(nextNode->correctedBits, "10\0");
            // printf("D -> D corrigido %s \n", nextNode->correctedBits);
        }
    }

}

unsigned int calcHanningDistance(bit *receivedPacketMessage, bit *correctedPacketMessage, unsigned int packageSize){
    unsigned int hanningDist = 0;
    for (unsigned int i = 0;i < packageSize;++i)
        if (receivedPacketMessage[i] != correctedPacketMessage[i])
            ++hanningDist; 
    return (hanningDist); 
}


/** VITERBI ALGORITHM **/

void updatePathError(tNode *root, unsigned int level, tListNode **auxList, unsigned int height, bit *receivedStepMessage, unsigned int packetSize){
    if (root == NULL)
        return;
    if (level == 0)
    {
        insertfirst(root, auxList);
        root->pathError += calcHanningDistance(receivedStepMessage,root->correctedBits, packetSize);
    }
    else if (level > 0)
    {
        if (root->shouldContinue)
        {
            updatePathError(root->left, level - 1, auxList, height,receivedStepMessage,packetSize);
            updatePathError(root->right, level - 1, auxList, height,receivedStepMessage,packetSize);
        }
    }

}

tNode * getMinHanningDistancePathLeaf(tNode *root, unsigned int packetSize){
    tNode *minHanningDistancePathNode = NULL;
    getListLeafsHannigPathDistance(root, height(root), packetSize,height(root),&minHanningDistancePathNode);
    return minHanningDistancePathNode; 
} 

void cutLeafs(tListNode *head, unsigned int tam){
    tListNode *aux = head;
    for (int i=0;i < tam;++i){
        tListNode *tmp = aux->next;
        for (int k=i;k < tam-1;++k){
            if (k != i && tmp->value->curState == aux->value->curState && aux->value->pathError < tmp->value->pathError ){
                // printf("podando "); 
                tmp->value->shouldContinue=false; 
            }    
            tmp = tmp->next;
        }
        // printf("aux %d %d  ", aux->value->curState,aux->value->parent->curState);  
        aux = aux->next;
    }

}

bit * viterbiAlgorithm(bit *receivedMessage, unsigned int packetSize, unsigned int msgSize){
    tNode *pathRoot = startNode(0, 0, A, 0, packetSize, NULL);
    tNode *minHanningDistancePathAux;
    pathRoot->correctedBits[0] =  '0';
    pathRoot->correctedBits[1] = '0';

    unsigned int totalPackages = msgSize / packetSize; 
    tListNode *auxList = NULL;

    for(unsigned int i = 0; i < totalPackages;++i){
        bit receivedStepMessage[packetSize+1];
        strncpy(receivedStepMessage, &receivedMessage[i * packetSize], packetSize);
        getNextStep(pathRoot, packetSize); 
        updatePathError(pathRoot,height(pathRoot),&auxList,height(pathRoot),receivedStepMessage,packetSize); 
        
        cutLeafs(auxList,listSize(auxList)); // cutting leafs which collides in state and path error is bigger
        // printLevelOrder(pathRoot);
        deleteList(&auxList);
    }
  
    #ifdef DEBUG
    printLevelOrder(pathRoot);
    #endif
    minHanningDistancePathAux = getMinHanningDistancePathLeaf(pathRoot, packetSize); 
    tListNode *head = NULL;
    
    while( minHanningDistancePathAux->parent){
        insertfirst(minHanningDistancePathAux,&head);
        minHanningDistancePathAux = minHanningDistancePathAux->parent; 
    } 
    // prnList(head); 
    printf("\n\n");

    bit *decodedMessage = getDecodedMessage(head,msgSize);
    #ifdef DEBUG 
    prnList(head);
    #endif
    return decodedMessage; 
}
