#include "error-handle.h"

unsigned int checksum(byte *received,unsigned int nBytes){
    unsigned int sum = 0;

    // Main summing loop
    while(nBytes > 1)
    {
        sum += *(unsigned short) received++;
        nBytes -= 2;
    }

    // Add left-over byte, if any
    if (nBytes > 0)
        sum += *((byte *) received);

    // Fold 32-bit sum to 16 bits
    while (sum>>16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return(~sum);
}
