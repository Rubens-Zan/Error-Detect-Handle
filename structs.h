#include <stdbool.h> 

#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef unsigned char bit;    

typedef enum {
    A, //= 00,
    B, //= 01,
    C, //= 10,
    D //= 11
} typesState;

typedef struct tNode tNode;
struct tNode
{
    bit receivedBit;     // {1,0}
    bit correctedBits[3];  // "XY"
    typesState curState; // {A,B,C,D}
    tNode *left, *right; // Next path, being left if input is 0 and right 1
    bool shouldContinue; // determine if this path should be continued or not
    unsigned int pathError;
    unsigned int index; 
};

typedef struct combinationAux combinationAux;
struct combinationAux
{
    bit *pathBits;  // "XY"
    unsigned int pathError;
    unsigned int index; 
};

#endif