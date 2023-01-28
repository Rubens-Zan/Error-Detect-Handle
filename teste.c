#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generate-message.h"
#include "error-handle.h"
#include "binary-tree.h"
#include "generate-message.h"



#define MSG_SIZE 10
#define PKT_SIZE 2


void main(void)
{
  bit message[] = "1101111010"; 

  printf("INPUT MESSAGE %s \n", message); 
  msgT *encodedMessage = initMessage(message, MSG_SIZE);
  printf("ENCODED MESSAGE  %s \n", encodedMessage->dados); 
  
  // WITHOUT ERROR
  printf("\nRECEIVED MESSAGE %s", encodedMessage->dados);
  bit * decodedMessageTest = viterbiAlgorithm(encodedMessage->dados, PKT_SIZE,MSG_SIZE*2);
  printf("\n Mensagem decodificada %s \n",decodedMessageTest);
  // FLIPPING THE FIRST BIT
  encodedMessage->dados[0] = '0'; 

  printf("\nRECEIVED MESSAGE %s", encodedMessage->dados);
  bit * decodedMessageTestError; 
  if (calculaParidade(encodedMessage->dados, MSG_SIZE) != encodedMessage->paridade){
    decodedMessageTestError = viterbiAlgorithm(encodedMessage->dados, PKT_SIZE,MSG_SIZE*2);
    printf("Mensagem decodificada %s \n",decodedMessageTestError);

  }
  
  free(encodedMessage); 
  free(decodedMessageTest);
  free(decodedMessageTestError);
}
