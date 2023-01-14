typedef unsigned char bit;    

typedef enum {
    A = 00,
    B = 01,
    C = 10,
    D = 11
} typesState;

bit * trellisEncode(bit *originalMessage, unsigned int size); 
void getNextState(typesState curState,unsigned int receivedBit,typesState nextState, bit *correctedReceivedBits);