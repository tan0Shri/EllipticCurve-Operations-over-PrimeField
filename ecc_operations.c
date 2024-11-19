#include"utilities.h"
#include<string.h>

uint32_t a[10] = {0x3, 0};

// Function to calculate point doubling
void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x3, uint32_t* y3) {
    uint32_t lambda[10] = {0}, temp[10] = {0};
    uint32_t two[10] = {0x2, 0};
    // Calculate λ = (3*x1^2 + a) / (2*y1) mod p
    FieldMult(x1, x1, temp);           // temp = x1^2
    // FieldMult(temp, three, temp);      // temp = 3*x1^2
    Field_ConstMult(temp, 3, temp);
    FieldAddition(temp, a, temp);      // temp = 3*x1^2 + a
    FieldAddition(y1, y1, lambda);        // lambda = 2*y1
    FieldDivision(temp, lambda, lambda); // lambda = (3*x1^2 + a) / (2*y1)

    // Calculate x3 = λ^2 - 2*x1 mod p
    FieldMult(lambda, lambda, x3);    // x3 = λ^2
    FieldAddition(x1, x1, temp);      // temp = 2*x1
    FieldSubtraction(x3, temp, x3);   // x3 = λ^2 - 2*x1

    // Calculate y3 = λ*(x1 - x3) - y1 mod p
    FieldSubtraction(x1, x3, temp);                // temp = x1 - x3
    FieldMult(lambda, temp, y3);      // y3 = λ*(x1 - x3)
    FieldSubtraction(y3, y1, y3);                  // y3 = λ*(x1 - x3) - y1
}

// Function to calculate point addition
void add(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t* x3, uint32_t* y3) {
    uint32_t lambda[10] = {0}, temp1[10] = {0}, temp2[10] = {0};

    // Calculate λ = (y2 - y1) / (x2 - x1) mod p
    FieldSubtraction(y2, y1, temp1);               // temp1 = y2 - y1
    FieldSubtraction(x2, x1, temp2);               // temp2 = x2 - x1
    FieldDivision(temp1, temp2, lambda); // lambda = (y2 - y1) / (x2 - x1)

    // Calculate x3 = λ^2 - x1 - x2 mod p
    FieldMult(lambda, lambda, x3);   // x3 = λ^2
    FieldSubtraction(x3, x1, x3);                 // x3 = λ^2 - x1
    FieldSubtraction(x3, x2, x3);                 // x3 = λ^2 - x1 - x2

    // Calculate y3 = λ*(x1 - x3) - y1 mod p
    FieldSubtraction(x1, x3, temp1);              // temp1 = x1 - x3
    FieldMult(lambda, temp1, y3);    // y3 = λ*(x1 - x3)
    FieldSubtraction(y3, y1, y3);                 // y3 = λ*(x1 - x3) - y1
}


void ScalarMult_left2right(uint32_t* x, uint32_t* y, uint32_t* scalar, uint32_t* xR, uint32_t* yR) {
    // Initialize result as the point at infinity (null point)
    memset(xR, 0, sizeof(uint32_t) * 10);
    memset(yR, 0, sizeof(uint32_t) * 10);

    // Temporary variables for intermediate computations
    uint32_t xTemp[10] = {0}, yTemp[10] = {0};

    // Get the bit length of the scalar
    int scalarBitLength = BitLength(scalar);

    // Loop through each bit of the scalar from the most significant to the least
    for (int i = scalarBitLength - 1; i >= 0; i--) {
        // Point doubling step: R = 2*R
        if (xR[0] != 0 || yR[0] != 0) {  // Skip if R is the point at infinity
            dbl(xR, yR, xTemp, yTemp);
            memcpy(xR, xTemp, sizeof(uint32_t) * 10);
            memcpy(yR, yTemp, sizeof(uint32_t) * 10);
        }

        // Point addition step if the current bit is 1: R = R + P
        int flag = (scalar[i / 29] >> (i % 29)) & 1;
        if (flag) {
            if (xR[0] == 0 && yR[0] == 0) {
                // If R is the point at infinity, set R = P
                memcpy(xR, x, sizeof(uint32_t) * 10);
                memcpy(yR, y, sizeof(uint32_t) * 10);
            } else {
                add(xR, yR, x, y, xTemp, yTemp);
                memcpy(xR, xTemp, sizeof(uint32_t) * 10);
                memcpy(yR, yTemp, sizeof(uint32_t) * 10);
            }
        }
    }
}

