#include "list.h"
#include "error-handle.h"
#include "generate-message.h"
#include <stdlib.h>
#include <stdio.h>
#include "binary-tree.h"

void insertfirst(tNode *element, tListNode **head)
{
    tListNode *New;
    New = (tListNode *)malloc(sizeof(tListNode));
    New->value = element;
    New->next = (*head);
    (*head) = New;
}

/* Function to delete the entire linked list */
void deleteList(tListNode **head_ref)
{
    /* deref head_ref to get the real head */
    tListNode *current = *head_ref;
    tListNode *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
       in the caller. */
    *head_ref = NULL;
}

bit *getDecodedMessage(tListNode *head, unsigned int decodedMsgSize)
{
    bit *decodedMsg = (bit *)malloc(sizeof(bit) * (decodedMsgSize + 1)); // since message will be encoded to x1 and x2, it will be double the message

    tListNode *aux = head;
    unsigned int i = 0;
    while (aux != NULL)
    {
        tNode *value = aux->value;
        decodedMsg[i] = INTTOBIT(value->receivedBit);
        aux = aux->next;
        ++i;
    }
    decodedMsg[i] = '\0';
    return decodedMsg;
}

unsigned int listSize(tListNode *head)
{
    tListNode *aux = head;
    unsigned int size = 0;
    while (aux != NULL)
    {
        ++size; 
        aux = aux->next;
    }

    return size; 
}

void prnList(tListNode *head)
{
    tListNode *aux = head;
    while (aux != NULL)
    {
        printf("(%s, %d, %d)", aux->value->correctedBits, aux->value->receivedBit, aux->value->shouldContinue);
        aux = aux->next;
    }

    printf("\n");
}