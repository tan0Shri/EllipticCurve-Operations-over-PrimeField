#include"utilities.h"
#include<string.h>

// Initialize base as g = 2
uint32_t base[10] = {0x2, 0};

// Function to get the bit length of the exponent
int BitLength(uint32_t* exp) {
    for (int i = 8; i >= 0; i--) {  // Traverse from the most significant chunk
        if (exp[i] != 0) {
            for (int j = 28; j >= 0; j--) {  // Check each bit in the 29-bit chunk
                if ((exp[i] >> j) & 1) {
                    return i * 29 + j + 1;  // Return the bit position + 1 as the length
                }
            }
        }
    }
    return 0;  // If exp is zero, bit length is 0
}

// Function to perform modular exponentiation in a prime field (left to right square and multiply)
void FieldExp_left2right(uint32_t* exp, uint8_t* result) {  
    // Initialize result to 1 in packed base-29 format
    uint32_t tempResult[10] = {0};
    tempResult[0] = 0x1;

    // Get the bit length of the exponent
    int expBitLength = BitLength(exp);

    //Loop through each bit of the exponent from the most significant to the least
    for (int i = expBitLength - 1; i >= 0; i--) {
        // Square step
        FieldMult(tempResult, tempResult, tempResult);  // tempResult = tempResult^2 (mod p)
    
        // Multiply step if the i-th bit of exp is set 
        ((exp[i / 29] >> (i % 29)) & 1)? FieldMult(tempResult, base, tempResult) : NULL;
    }

    // Convert the result to base 16 for output
    ToBase16(tempResult, result);
}

// Function to perform modular exponentiation in a prime field (right to left square and multiply)
void FieldExp_right2left(uint32_t* exp, uint8_t* result) { 
    //copy base to some other variable 
    uint32_t base_copy[10];
    memcpy(base_copy, base, sizeof(base_copy));

    // Initialize result to 1 in packed base-29 format
    uint32_t tempResult[10] = {0};
    tempResult[0] = 0x1;

    // Get the bit length of the exponent
    int expBitLength = BitLength(exp);

    //Loop through each bit of the exponent from the least significant to the most
    for (int i = 0; i < expBitLength; i++) 
    {
        // Multiply step if the i-th bit of exp is set 
        ((exp[i / 29] >> (i % 29)) & 1)? FieldMult(tempResult, base_copy, tempResult) : NULL;

        // Square step
        FieldMult(base_copy, base_copy, base_copy);
    }

    // Convert the result to base 16 for output
    ToBase16(tempResult, result);
}

void FieldExp_Montgomery(uint32_t* exp, uint8_t* result) { 
    // Initialize S to 1 and R to base in packed base-29 format
    uint32_t *S = base;  // S represents the current result, initialized to base
    
    uint32_t R[10] = {0};       // R represents the "next" result 
    FieldMult(base, base, R);   // initialized to the base^2

    // Get the bit length of the exponent
    int expBitLength = BitLength(exp);
    // Loop through each bit of the exponent from the most significant to the least
    for (int i = expBitLength - 2; i >= 0; i--) 
    {
        // Determine the bit value of exp at position i
        int bit = (exp[i / 29] >> (i % 29)) & 1;

        if (bit == 1) {
            // If bit is 1: S = S * R (mod p), R = R * R (mod p)
            FieldMult(S, R, S); // Multiply S by R
            FieldMult(R, R, R); // Square R
        } else {
            // If bit is 0: R = S * R (mod p), S = S * S (mod p)
            FieldMult(R, S, R); // Multiply R by S
            FieldMult(S, S, S); // Square S
        }
    }
    // Convert S to base 16 for output
    ToBase16(S, result);
}


