#ifndef ECC_UTILITIES_H   // Header guard to avoid multiple inclusion
#define ECC_UTILITIES_H

#include<stdint.h>
#include<stdbool.h>

extern uint32_t a[10];
bool IsPointOnCurve(uint32_t* x, uint32_t* y);
void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x3, uint32_t* y3);
void add(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t* x3, uint32_t* y3);
void ScalarMult_left2right(uint32_t* xP, uint32_t* yP, uint32_t* scalar, uint32_t* xR, uint32_t* yR);
void ScalarMult_right2left(uint32_t* xP, uint32_t* yP, uint32_t* scalar, uint32_t* xR, uint32_t* yR);

#endif // End of header guard


