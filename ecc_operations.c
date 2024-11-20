#include"utilities.h"
#include"ecc_utilities.h"
#include<string.h>

uint32_t a[10] = {0x3, 0};
uint32_t b[10] = {0};

bool IsPointOnCurve(uint32_t* x, uint32_t* y) {
    uint32_t y_squared[10] = {0};
    uint32_t x_cubed[10] = {0};
    uint32_t ax[10] = {0};
    uint32_t rhs[10] = {0};

    // Calculate y^2 mod p
    FieldMult(y, y, y_squared); // y_squared = y^2

    // Calculate x^3 mod p
    FieldMult(x, x, x_cubed);   // x_cubed = x^2
    FieldMult(x_cubed, x, x_cubed); // x_cubed = x^3

    // Calculate 3x mod p
    FieldMult(x, a, ax); // ax = 3 * x

    // Calculate RHS = x^3 + 3x mod p
    FieldAddition(x_cubed, ax, rhs);
    FieldAddition(rhs, b, rhs);

    // Check if y^2 == RHS mod p
    for (int i = 0; i < 10; i++) {
        if (y_squared[i] != rhs[i]) {
            return false; // If any chunk differs, the elements are not equal
        }
    }
    return true;
}

// Function to calculate point addition
void add(uint32_t* x1, uint32_t* y1, uint32_t* x2, uint32_t* y2, uint32_t* x3, uint32_t* y3) {
    uint32_t lambda[10] = {0}, temp1[10] = {0}, temp2[10] = {0}, temp3[10] = {0};

    // Calculate λ = (y2 - y1) / (x2 - x1) mod p
    FieldSubtraction(y2, y1, temp1);           // temp1 = y2 - y1
    FieldSubtraction(x2, x1, temp2);           // temp2 = x2 - x1
    FieldDivision(temp1, temp2, lambda);       // lambda = (y2 - y1) / (x2 - x1)

    // Calculate x3 = λ^2 - x1 - x2 mod p
    FieldMult(lambda, lambda, temp2);          // temp2 = λ^2
    FieldSubtraction(temp2, x1, temp2);        // temp2 = λ^2 - x1
    FieldSubtraction(temp2, x2, x3);           // x3 = λ^2 - x1 - x2

    // Calculate y3 = λ*(x1 - x3) - y1 mod p
    FieldSubtraction(x1, x3, temp1);           // temp1 = x1 - x3
    FieldMult(lambda, temp1, temp3);           // temp3 = λ*(x1 - x3)
    FieldSubtraction(temp3, y1, y3);           // y3 = λ*(x1 - x3) - y1
}

// Function to calculate point doubling
void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x4, uint32_t* y4) {
    uint32_t lambda[10] = {0}, temp1[10] = {0}, temp2[10] = {0};
    
    // Calculate λ = (3*x1^2 + a) / (2*y1) mod p
    FieldMult(x1, x1, temp1);           // temp1 = x1^2
    Field_ConstMult(temp1, 3, temp1);    // temp1 = 3*x1^2
    FieldAddition(temp1, a, temp1);      // temp1 = 3*x1^2 + a
    FieldAddition(y1, y1, lambda);     // lambda = 2*y1
    FieldDivision(temp1, lambda, lambda); // lambda = (3*x1^2 + a) / (2*y1)

    // Calculate x3 = λ^2 - 2*x1 mod p
    FieldMult(lambda, lambda, temp2);    // temp2 = λ^2
    FieldAddition(x1, x1, temp1);        // temp1 = 2*x1
    FieldSubtraction(temp2, temp1, x4);  // x4 = λ^2 - 2*x1

    // Calculate y3 = λ*(x1 - x4) - y1 mod p
    FieldSubtraction(x1, x4, temp1);      // temp1 = x1 - x3
    FieldMult(lambda, temp1, temp2);      // temp2 = λ*(x1 - x4)
    FieldSubtraction(temp2, y1, y4);      // y4 = λ*(x1 - x3) - y1
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

void ScalarMult_right2left(uint32_t* x, uint32_t* y, uint32_t* scalar, uint32_t* xR, uint32_t* yR) {
    // Initialize R = P and Q = point at infinity
    uint32_t xQ[10] = {0}, yQ[10] = {0};   // Q = point at infinity (0, 0)
    memcpy(xR, x, sizeof(uint32_t) * 10);  // R(xR,yR) = P(x,y)
    memcpy(yR, y, sizeof(uint32_t) * 10);

    // Get the bit length of the scalar
    int scalarBitLength = BitLength(scalar);

    // Loop through each bit of the scalar from the least significant to the most
    for (int i = 0; i < scalarBitLength; i++) {
        int flag = (scalar[i / 29] >> (i % 29)) & 1;
        
        if (flag) {
            // Q = Q + R
            if (xQ[0] == 0 && yQ[0] == 0) {
                memcpy(xQ, xR, sizeof(uint32_t) * 10);  // Q = R
                memcpy(yQ, yR, sizeof(uint32_t) * 10);
            } else {
                add(xQ, yQ, xR, yR, xQ, yQ);           // Q = Q + R
            }
        }
        // R = 2*R
        dbl(xR, yR, xR, yR);
    }

    // Result is stored in Q
    memcpy(xR, xQ, sizeof(uint32_t) * 10);
    memcpy(yR, yQ, sizeof(uint32_t) * 10);
}

