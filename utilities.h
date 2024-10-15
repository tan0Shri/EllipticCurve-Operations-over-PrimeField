#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdint.h>

//declaration of global array for prime 
extern uint8_t prime[32];

// Function prototypes
void printBytes(uint8_t*, int);     // Prints byte array
void ToBase29(uint8_t*, uint32_t*); // Converts data to base 29
int ToBase16(uint32_t*, uint8_t*); // Converts data to base 16 (hexadecimal)
void ADD(uint32_t*, uint32_t*, uint8_t*); // Performs addition on uint32_t arrays

#endif // End of header guard
