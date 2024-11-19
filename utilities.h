#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdint.h>

extern uint32_t mask; //mask for lower 29-bits

//declaration of global arrays
extern uint8_t prime[32];
extern uint8_t mu[34];
extern uint32_t p[10];
extern uint32_t T[10];

extern uint32_t g[10];


// Function prototypes
void PrimeInputs();   //scans the inputes related to prime-Field from file
void StringToArray(const char *hexstring, uint8_t *dest);
void printBytes(uint8_t* num, int bytes);     // Prints byte array
void ToBase29(uint8_t* src, uint32_t* dest, int bytes); // Converts data to base 29
void ToBase16(uint32_t* src, uint8_t* dest); // Converts data to base 16 (hexadecimal)
void ADD(uint32_t* num1, uint32_t* num2, uint32_t* sum, int ACTIVE_COUNT); // Performs addition on uint32_t arrays, packed addition in base 29
void SUB(uint32_t* num1, uint32_t* num2, uint32_t* result, int ACTIVE_COUNT); //Perfoms subtraction on uint32_t arrays, packed subtraction in base 29
void Mult(uint32_t* num1, uint32_t* num2, uint32_t* result, int ACTIVE_COUNT); //performs multiplication of two given numbers in base 29 (without reduction)
int IsGreater(uint32_t* num1, uint32_t* num2); //Checks if num1 is greater than num2 or not, if yes, return 1 else 0
void FieldAddition(uint32_t* num1, uint32_t* num2, uint32_t* result);    //Performs field addition
void FieldSubtraction(uint32_t* num1, uint32_t* num2, uint32_t* result);
void Barrett_Red(uint32_t* num, uint32_t* p, uint32_t* result); //reduction algorithm for reducing larger elements into field elements
void FieldMult(uint32_t* num1, uint32_t* num2, uint32_t* result); //performs field multiplication (with reduction)
void FieldInverse(uint32_t* num, uint32_t* result);
void FieldDivision(uint32_t* num1, uint32_t* num2, uint32_t* result);



int BitLength(uint32_t* exp);
void FieldExp_left2right(uint32_t* base, uint32_t* exponent, uint8_t* result);
void FieldExp_right2left(uint32_t* base, uint32_t* exponent, uint8_t* result);
void FieldExp_Montgomery(uint32_t* base, uint32_t* exp, uint8_t* result);
void FieldExp_Montgomery_noBranching(uint32_t* base, uint32_t* exp, uint32_t* result);



#endif // End of header guard
