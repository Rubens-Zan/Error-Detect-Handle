#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error-handle.h"
#include "binary-tree.h"


#define MSG_SIZE 3
#define PKT_SIZE 2


void main(void)
{
  // bit message[MSG_SIZE]; // message of packet bits
  bit message[] = "110"; 
  unsigned int check;            // 16-bit checksum value
  unsigned int i;                // Loop counter

  // check = checksum(message, MSG_SIZE);

  printf("INPUT MESSAGE %s \n", message); 
  bit *encodedMessage = trellisEncode(message, MSG_SIZE);

  printf("ENCODED MESSAGE  %s \n", encodedMessage); 
  
  // WITHOUT ERROR
  printf("\nRECEIVED MESSAGE %s", encodedMessage);
  bit * decodedMessageTest = viterbiAlgorithm(encodedMessage, PKT_SIZE,MSG_SIZE);
  printf("Mensagem decodificada %s \n",decodedMessageTest);
  // FLIPPING THE FIRST BIT
  encodedMessage[0] = '0'; 

  printf("\nRECEIVED MESSAGE %s", encodedMessage);
  bit * decodedMessageTestError = viterbiAlgorithm(encodedMessage, PKT_SIZE,MSG_SIZE);
  printf("Mensagem decodificada %s \n",decodedMessageTestError);

  free(decodedMessageTest);
  free(decodedMessageTestError);

}
