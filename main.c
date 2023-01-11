#include <stdio.h>
#include "error-handle.h"

#define MSG_SIZE 20

void main(void)
{
  byte message[MSG_SIZE]; // message of packet bytes
  unsigned int check;            // 16-bit checksum value
  unsigned int i;                // Loop counter

  // Compute the 16-bit checksum
  check = checksum(message, MSG_SIZE);

  printf("checksum test %04X \n", check);
}
