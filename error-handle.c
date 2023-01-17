#include "error-handle.h"
#include "binary-tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <search.h>


#define BITTOINT(bitRepresentation)  (bitRepresentation - '0')
#define INTTOBIT(intBit)  (intBit + '0')
#define HANNINGDISTANCE(receivedBit,testedBit,packageSize) (return strncmp(receivedBit,testedBit, packageSize))

unsigned int checksum(bit *received,unsigned int nbits){
    unsigned int sum = 0;

    // Main summing loop
    while(nbits > 1)
    {
        // sum += (unsigned short) received++;
        nbits -= 2;
    }

    // Add left-over bit, if any
    if (nbits > 0)
        sum += *((bit *) received);

    // Fold 32-bit sum to 16 bits
    while (sum>>16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return(~sum);
}

/** TRELLIS ENCODING **/

void trellisShift(bit *trellis, bit newBit){
    trellis[2] = trellis[1]; 
    trellis[1] = trellis[0]; 
    trellis[0] = newBit; 
}

bit encodedX1(bit *trellis){
    bit x1; 
    x1 = INTTOBIT(( BITTOINT(trellis[0]) +BITTOINT(trellis[1]) +BITTOINT(trellis[2])) % 2);  // x1 = m xor m1 xor m2 
    return x1; 
}

bit encodedX2(bit *trellis){
    bit x2; 
    x2 = INTTOBIT((BITTOINT(trellis[0]) + BITTOINT(trellis[2]) ) % 2);  // x2 = m xor m2 
    return x2; 
}

bit * trellisEncode(bit *originalMessage, unsigned int size){
    bit trellis[4] = "000"; 
    trellis[3] = '\0';

    bit *encodedMessage = (bit *) malloc(sizeof(char) * (size * 2)); // since message will be encoded to x1 and x2, it will be double the message
    
    unsigned int encodCounter = 0;
    for (unsigned int i=0;i < size;++i){
        bit x1,x2; 
        trellisShift(trellis, originalMessage[i]);
        encodedMessage[encodCounter] = encodedX1(trellis); 
        encodedMessage[encodCounter+1]= encodedX2(trellis);
        encodCounter+=2; 
    }
    encodedMessage[encodCounter] = '\0';

    return encodedMessage; 
}

bit * trellis_decode(bit *originalMessage, unsigned int size){

}

/****/

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

void updatePathError(tNode *node, bit *receivedStepMessage, unsigned int packetSize){
     
    if (node->left != NULL && node->right != NULL)
    {   
        updatePathError(node->left,receivedStepMessage,packetSize); 
        updatePathError(node->right,receivedStepMessage,packetSize);
    }else {
        node->pathError += calcHanningDistance(receivedStepMessage,node->correctedBits, packetSize);
    }

}


bit * viterbiAlgorithm(bit *receivedMessage, unsigned int packetSize){
    /**
     1. PACKETS OF n BITS, WRITE PACKETS OVER EACH TIME STEP OF TRELLIS IN SEQUENCE
     2.FIND THE HAMMING DISTANCE BETWEEN: 
        a) the n bit packet of the received code and the
        b) output of the encoder shown on the traces
        Add the Hamming Distance + Path distance earlier
     3. Discard the path with higher path metric
     4. Repeat step 2 and 3 
     5. Select the Path with lowest Path metric and decode
    */
    tNode *pathRoot = startNode(0, 0, A, 0);
    pathRoot->correctedBits[0] =  '0';
    pathRoot->correctedBits[1] = '0';
    unsigned int curPacket = 0;

    unsigned int totalPackages = strlen(receivedMessage) / packetSize; 
    for(unsigned int i = 0; i < totalPackages;++i){
        char receivedStepMessage[packetSize+1];
        strncpy(receivedStepMessage, &receivedMessage[i * packetSize], packetSize);
        getNextStep(pathRoot); 
        updatePathError(pathRoot, receivedStepMessage, packetSize); 
    }
    unsigned int possibleCombinationsCount = pow(2,height(pathRoot));
    // generateCombinationsPaths(); 
    printLevelOrder(pathRoot);
}