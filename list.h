#include "binary-tree.h"
#include "generate-message.h"

#ifndef _LIST_H_
#define _LIST_H_

typedef struct tListNode tListNode;
struct tListNode
{
    tNode *value;       
    tListNode *next; 
};
void insertfirst(tNode *element, tListNode **head);
void prnList(tListNode *head);
bit * getDecodedMessage(tListNode *head, unsigned int decodedMsgSize);

#endif
