#include "structs.h"

#ifndef _ERROR_H_
#define _ERROR_H_

bit * trellisEncode(bit *originalMessage, unsigned int size); 
bit * viterbiAlgorithm(bit *receivedMessage, unsigned int packetSize);
void getNextState(typesState curState,unsigned int receivedBit,tNode *nextNode); 

#endif