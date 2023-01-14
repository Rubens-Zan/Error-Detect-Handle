#include "error-handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITTOINT(bitRepresentation)  (bitRepresentation - '0')
#define INTTOBIT(intBit)  (intBit + '0')

unsigned int checksum(bit *received,unsigned int nbits){
    unsigned int sum = 0;

    // Main summing loop
    while(nbits > 1)
    {
        // sum += (unsigned short) received++;
        nbits -= 2;
    }

    // Add left-over bit, if any
    if (nbits > 0)
        sum += *((bit *) received);

    // Fold 32-bit sum to 16 bits
    while (sum>>16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return(~sum);
}


void trellice_shift(bit *trellice, bit newBit){
    trellice[2] = trellice[1]; 
    trellice[1] = trellice[0]; 
    trellice[0] = newBit; 
}


bit encoded_x1(bit *trellice){
    bit x1; 
    x1 = INTTOBIT(( BITTOINT(trellice[0]) +BITTOINT(trellice[1]) +BITTOINT(trellice[2])) % 2);  // x1 = m xor m1 xor m2 
    return x1; 
}

bit encoded_x2(bit *trellice){
    bit x2; 
    x2 = INTTOBIT((BITTOINT(trellice[0]) + BITTOINT(trellice[2]) ) % 2);  // x2 = m xor m2 
    return x2; 
}

bit * trelice_encode(bit *originalMessage, unsigned int size){
    bit trellice[4] = "000"; 
    trellice[3] = '\0';

    bit *encodedMessage = (bit *) malloc(sizeof(char) * (size+ size)); // since message will be encoded to x1 and x2, it will be double the message
    unsigned int encodCounter = 0;
    for (unsigned int i=0;i < size;++i){
        bit x1,x2; 
        trellice_shift(trellice, originalMessage[i]);
        encodedMessage[encodCounter] = encoded_x1(trellice); 
        encodedMessage[encodCounter+1]= encoded_x2(trellice);
        encodCounter+=2; 
    }
    encodedMessage[encodCounter] = '\0';

    return encodedMessage; 
}