#include "binary-tree.h"

#ifndef _ERROR_H_
#define _ERROR_H_

bit * trellisEncode(bit *originalMessage, unsigned int size); 
bit * viterbiAlgorithm(bit *receivedMessage, unsigned int packetSize);
void getNextState(typesState curState,unsigned int receivedBit,tNode *nextNode); 
tNode * getMinHanningDistance(tNode *root, unsigned int packetSize);
#endif