#include "error-handle.h"
#include <stdbool.h>

typedef struct tNode tNode;
struct tNode
{
    bit receivedBit;     // {1,0}
    bit correctedBits[3];  // "XY"
    typesState curState; // {A,B,C,D}
    tNode *left, *right; // Next path, being left if input is 0 and right 1
    bool shouldContinue; // determine if this path should be continued or not
    unsigned int pathError;
};

unsigned int countNodes(tNode *n);
tNode *startNode(unsigned int curPathError,unsigned int inputBit, typesState curState );
unsigned int height(tNode *p); 