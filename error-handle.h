#include "binary-tree.h"
#include "generate-message.h"

#ifndef _ERROR_H_
#define _ERROR_H_

#define BITTOINT(bitRepresentation)  (bitRepresentation - '0')
#define INTTOBIT(intBit)  (intBit + '0')
#define HANNINGDISTANCE(receivedBit,testedBit,packageSize) (return strncmp(receivedBit,testedBit, packageSize))



bit * viterbiAlgorithm(bit *receivedMessage, unsigned int packetSize, unsigned int msgSize);
void getNextState(typesState curState,unsigned int receivedBit,tNode *nextNode); 

#endif