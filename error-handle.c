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

/** TRELLIS ENCODING **/

void trellisShift(bit *trellis, bit newBit){
    trellis[2] = trellis[1]; 
    trellis[1] = trellis[0]; 
    trellis[0] = newBit; 
}

bit encodedX1(bit *trellis){
    bit x1; 
    x1 = INTTOBIT(( BITTOINT(trellis[0]) +BITTOINT(trellis[1]) +BITTOINT(trellis[2])) % 2);  // x1 = m xor m1 xor m2 
    return x1; 
}

bit encodedX2(bit *trellis){
    bit x2; 
    x2 = INTTOBIT((BITTOINT(trellis[0]) + BITTOINT(trellis[2]) ) % 2);  // x2 = m xor m2 
    return x2; 
}

bit * trellisEncode(bit *originalMessage, unsigned int size){
    bit trellis[4] = "000"; 
    trellis[3] = '\0';

    bit *encodedMessage = (bit *) malloc(sizeof(char) * (size+ size)); // since message will be encoded to x1 and x2, it will be double the message
    unsigned int encodCounter = 0;
    for (unsigned int i=0;i < size;++i){
        bit x1,x2; 
        trellisShift(trellis, originalMessage[i]);
        encodedMessage[encodCounter] = encodedX1(trellis); 
        encodedMessage[encodCounter+1]= encodedX2(trellis);
        encodCounter+=2; 
    }
    encodedMessage[encodCounter] = '\0';

    return encodedMessage; 
}

bit * trellis_decode(bit *originalMessage, unsigned int size){

}

/****/

/**
 * @brief Get the next state object
 * PATH DIAGRAM ACCORDING IF RECEIVED 0 OR 1
 * A -> A,C 
 * B -> A,C
 * C -> B,D
 * D -> B,D
 * 
 * @param curState{A,B,C,D} - Current state of the path
 * @param receivedBit{0,1} - Received bit  
 * @param nextState{A,B,C,D} - Next state of the path
 */
void getNextState(typesState curState,unsigned int receivedBit,typesState nextState, bit *correctedReceivedBits){
    // CHECK WHAT IS THE CURRENT STATES
    
    if (curState == A){
        if (receivedBit == 0){
            nextState = A;
            correctedReceivedBits = "00"; 
            
        }else {
            nextState = C;
            correctedReceivedBits = "11"; 
        }
    }
    if (curState == B){
        if (receivedBit == 0){
            nextState = A;
            correctedReceivedBits = "11"; 
        } else {
            nextState = C;
            correctedReceivedBits = "00"; 
        }
    }
    if (curState == C){
         if (receivedBit == 0){
            nextState = B;
            correctedReceivedBits = "10"; 
        }else {
            nextState = D;
            correctedReceivedBits = "01"; 
        }
    }
    if (curState == D){
        if (receivedBit == 0){
            nextState = B;
            correctedReceivedBits = "01"; 
        }else {
            nextState = D;
            correctedReceivedBits = "10"; 
        }
    }

}


/** VITERBI ALGORITHM **/

bit * viterbiAlgotithm(bit *receivedMessage, unsigned int packetSize){
    /**
     1. PACKETS OF n BITS, WRITE PACKETS OVER EACH TIME STEP OF TRELLIS IN SEQUENCE
     2.FIND THE HAMMING DISTANCE BETWEEN: 
        a) the n bit packet of the received code and the
        b) output of the encoder shown on the traces
        Add the Hamming Distance + Path distance earlier
     3. Discard the path with higer path metric
     4. Repeat step 2 and 3 
     5. Select the Path with lowest Path metric and decode
    */

}