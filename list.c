#include "list.h"
#include "error-handle.h"
#include "generate-message.h"
#include <stdlib.h>
#include <stdio.h>


void insertfirst(tNode *element, tListNode **head) 
{
    tListNode *New;
    New=(tListNode*)malloc(sizeof(tListNode));
    New->value=element;       
    New->next=(*head);     
    (*head) = New;        
}

bit * getDecodedMessage(tListNode *head, unsigned int decodedMsgSize){
    bit *decodedMsg = (bit *) malloc(sizeof(char) * (decodedMsgSize + 1)); // since message will be encoded to x1 and x2, it will be double the message

    tListNode *aux = head;
    unsigned int i = 0; 
    while (aux != NULL)
    {
        decodedMsg[i] = INTTOBIT(aux->value->receivedBit);
        aux = aux->next;
        ++i; 
    }
    return decodedMsg; 
}

void prnList(tListNode *head){
    tListNode *aux = head; 
    while (aux != NULL)
    {
        printf("(%s, %d)", aux->value->correctedBits, aux->value->receivedBit);
        aux = aux->next; 
    }

    printf("\n");
}