#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdint.h>

//declaration of global array for prime 
extern uint8_t prime[32];

// Function prototypes
void printBytes(uint8_t* num, int bytes);     // Prints byte array
void ToBase29(uint8_t* src, uint32_t* dest, int bytes); // Converts data to base 29
void ToBase16(uint32_t* src, uint8_t* dest); // Converts data to base 16 (hexadecimal)
void ADD(uint32_t* num1, uint32_t* num2, uint32_t* sum); // Performs addition on uint32_t arrays, packed addition in base 29
void SUB(uint32_t* num1, uint32_t* num2, uint32_t* result); //Perfoms subtraction on uint32_t arrays, packed subtraction in base 29
int IsGreater(uint32_t* num1, uint32_t* num2); //Checks if num1 is greater than num2 or not, if yes, return 1 else 0
void FieldAddition(uint32_t* num1, uint32_t* num2, uint8_t* result);    //Performs field addition
void Mult(uint32_t* num1, uint32_t* num2, uint32_t* result); //
void FieldMult(uint32_t* num1, uint32_t* num2, uint8_t* result);
#endif // End of header guard
