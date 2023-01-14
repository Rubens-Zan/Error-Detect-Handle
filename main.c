#include <stdio.h>
#include <string.h>
#include "error-handle.h"

#define MSG_SIZE 3

void main(void)
{
  bit message[MSG_SIZE]; // message of packet bits
  bit encodedMessage[MSG_SIZE+MSG_SIZE]; // message of packet bits

  unsigned int check;            // 16-bit checksum value
  unsigned int i;                // Loop counter

  // Compute the 16-bit checksum
  // check = checksum(message, MSG_SIZE);
  // message = "110"; 
  message[0] = '1';
  message[1] = '1';
  message[2] = '0';
  message[3] = '\0';

  printf("INPUT MESSAGE %s \n", message); 
  strcpy(encodedMessage,trellisEncode(message, MSG_SIZE)); 
  
  printf("ENCODED MESSAGE  %s \n", encodedMessage); 
}
