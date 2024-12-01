#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdio.h>
#include<stdint.h>

extern uint32_t mask; //mask for lower 29-bits
extern FILE* out;
//declaration of global arrays
extern uint8_t prime[32];   //prime in base 16
extern uint8_t mu[34];      // mu=(2^(2*29*9))/prime in base 16
extern uint32_t p[10];      // prime in base 29
extern uint32_t T[10];      // mu in base 29

extern uint32_t g[10];  // base for exponentiation in base 29


// Function prototypes
void PrimeInputs();   //scans the inputes related to prime-Field from file
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
void FieldInverse(uint32_t* num, uint32_t* result);     // compute modular inverse of num in prime field using Fermat's Little Theorem
void FieldDivision(uint32_t* num1, uint32_t* num2, uint32_t* result); // divide num1 by num2 in prime field (i.e., (num1 * num2^-1) mod p)
void Field_ConstMult(uint32_t* num, uint32_t constant, uint32_t* result);    // multiply 256 bit in packed form (base 29) by a small constant 

int IsZero(uint32_t* num, int length); //   checks num in base 29 is zero or not
int BitLength(uint32_t* exp);   // computes no of bits
int IsCompatible(uint32_t* exp);    // check 2 <= exp <= p-2
void FieldExp_left2right(uint32_t* base, uint32_t* exponent, uint32_t* result);     // perform modular exponentiation in a prime field (left to right square and multiply)
void FieldExp_right2left(uint32_t* base, uint32_t* exponent, uint32_t* result);     // perform modular exponentiation in a prime field (right to left square and multiply)
void FieldExp_Montgomery(uint32_t* base, uint32_t* exp, uint32_t* result);          // perform modular exponentiation in a prime field (using Montgomery Ladder)
void FieldExp_Montgomery_noBranching(uint32_t* base, uint32_t* exp, uint32_t* result);// WITHOUT BRANCHING: perform modular exponentiation in a prime field (using Montgomery Ladder)



#endif // End of header guard
