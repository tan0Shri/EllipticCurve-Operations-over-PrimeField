#ifndef ECC_UTILITIES_H   // Header guard to avoid multiple inclusion
#define ECC_UTILITIES_H

#include<stdint.h>

void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x3, uint32_t* y3);
void add(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t* x3, uint32_t* y3);

#endif // End of header guard


