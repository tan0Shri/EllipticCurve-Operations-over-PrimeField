#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdint.h>
// Function prototypes
void printBytes(uint8_t*, int);     // Prints byte array
void ToBase29(uint8_t*, uint32_t*); // Converts data to base 29
void ToBase16(uint32_t*, uint8_t*); // Converts data to base 16 (hexadecimal)
void ADD(uint32_t*, uint32_t*, uint32_t*); // Performs addition on uint32_t arrays

#endif // End of header guard
