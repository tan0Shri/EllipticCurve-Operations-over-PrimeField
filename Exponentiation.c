#include"utilities.h"
#include<string.h>

// Initialize base as g = 2
uint32_t g[10] = {0x2, 0};

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

    uint32_t base[10] = {0};
    *base = *g;

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
    //copy base from g
    uint32_t base[10] = {0};
    *base = *g;

    // Initialize result to 1 in packed base-29 format
    uint32_t tempResult[10] = {0x1, 0};

    // Get the bit length of the exponent
    int expBitLength = BitLength(exp);

    //Loop through each bit of the exponent from the least significant to the most
    for (int i = 0; i < expBitLength; i++) 
    {
        // Multiply step if the i-th bit of exp is set 
        ((exp[i / 29] >> (i % 29)) & 1)? FieldMult(tempResult, base, tempResult) : NULL;

        // Square step
        FieldMult(base, base, base);
    }

    // Convert the result to base 16 for output
    ToBase16(tempResult, result);
}

void FieldExp_Montgomery(uint32_t* exp, uint8_t* result) { 
    // Initialize S to 1 and R to base in packed base-29 format
    uint32_t S[10] = {0};
    *S = *g;  // S represents the current result, initialized to base
    uint32_t R[10] = {0};       // R represents the "next" result 
    FieldMult(S, S, R);   // initialized to the base^2

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

void FieldExp_Montgomery_noBranching(uint32_t* exp, uint8_t* result) { 
    uint32_t S[10] = {0};
    *S = *g; // S is initialized to base
    uint32_t R[10] = {0}; // R initialized to base^2
    FieldMult(S, S, R);

    int expBitLength = BitLength(exp);

    for (int i = expBitLength - 2; i >= 0; i--) {
        // Get the bit value of exp at position i
        int bit = (exp[i / 29] >> (i % 29)) & 1;

        // Temporary variables to hold potential new values for S and R
        uint32_t tempSR[10] = {0};
        uint32_t tempR[10] = {0};

        if (bit == 0) {
                // Swap S and R by copying elements
                for (int j = 0; j < 10; j++) {
                    uint32_t temp = S[j];
                    S[j] = R[j];
                    R[j] = temp;
                }
            }

        // Compute S * R and R * R
        FieldMult(S, R, tempSR);  // tempSR = S * R
        FieldMult(R, R, tempR);  // tempR = R * R

        // Select the new values of S and R without branching
        for (int j = 0; j < 10; j++) {
            S[j] = (bit * tempSR[j]) + ((1 - bit) * tempR[j]);
            R[j] = (bit * tempR[j]) + ((1 - bit) * tempSR[j]);
        }
    }
    // Convert S to base 16 for output
    ToBase16(S, result);
}


