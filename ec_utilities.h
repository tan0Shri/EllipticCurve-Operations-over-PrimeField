#ifndef ECC_UTILITIES_H   // Header guard to avoid multiple inclusion
#define ECC_UTILITIES_H

#include<stdint.h>
#include<stdbool.h>

//global variables
extern uint32_t a[10]; // curve parameter
extern uint32_t b[10]; // curve parameter

// Function prototypes
bool IsPointOnCurve(uint32_t* x, uint32_t* y); // checks the given points lies on curve or not
void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x3, uint32_t* y3); // performs doubling of a point P, 2P
void add(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t* x3, uint32_t* y3); // performs addition of two points P1 and P2, P1+P2
void ScalarMult_left2right(uint32_t* xP, uint32_t* yP, uint32_t* scalar, uint32_t* xR, uint32_t* yR); //performs scalar multiplication of a point P (i.e., kP) using double-and-add (left to right)
void ScalarMult_right2left(uint32_t* xP, uint32_t* yP, uint32_t* scalar, uint32_t* xR, uint32_t* yR); //performs scalar multiplication of a point P (i.e., kP) using double-and-add (left to right)

#endif // End of header guard


