#ifndef UTILITIES_H   // Header guard to avoid multiple inclusion
#define UTILITIES_H

#include<stdio.h>
#include<stdint.h>

extern FILE* in;
extern uint32_t mask; //mask for lower 29-bits

//declaration of global array for prime and mu(for Barrett)
extern uint8_t prime[32];
extern uint8_t mu[34];
extern uint32_t p[10];
extern uint32_t base[10];


// Function prototypes
void printBytes(uint8_t* num, int bytes);     // Prints byte array
void ToBase29(uint8_t* src, uint32_t* dest, int bytes); // Converts data to base 29
void ToBase16(uint32_t* src, uint8_t* dest); // Converts data to base 16 (hexadecimal)
void ADD(uint32_t* num1, uint32_t* num2, uint32_t* sum); // Performs addition on uint32_t arrays, packed addition in base 29
void SUB(uint32_t* num1, uint32_t* num2, uint32_t* result); //Perfoms subtraction on uint32_t arrays, packed subtraction in base 29
int IsGreater(uint32_t* num1, uint32_t* num2); //Checks if num1 is greater than num2 or not, if yes, return 1 else 0
void FieldAddition(uint32_t* num1, uint32_t* num2, uint8_t* result);    //Performs field addition
void Mult(uint32_t* num1, uint32_t* num2, uint32_t* result); //performs multiplication of two given numbers in base 29 (without reduction)
void Mult4Barrett(uint32_t* num1, uint32_t* num2, uint32_t* result);//performs multiplication for numbers which are necessary within Barrett reduction
void Barrett_Red(uint32_t* num, uint32_t* p, uint32_t* result); //reduction algorithm for reducing larger elements into field elements
void FieldMult(uint32_t* num1, uint32_t* num2, uint32_t* result); //performs field multiplication (with reduction)


int BitLength(uint32_t* exp);
void FieldExp_left2right(uint32_t* exponent, uint8_t* result);
void FieldExp_right2left(uint32_t* exponent, uint8_t* result);
void FieldExp_Montgomery(uint32_t* exp, uint8_t* result);



#endif // End of header guard
