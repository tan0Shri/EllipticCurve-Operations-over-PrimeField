#include"utilities.h"
#include"ec_utilities.h"
#include<string.h>

// Initializing curve parameters a and b in base 29
uint32_t a[10] = {0};
uint32_t b[10] = {0};


// Function to check that input points lie on the curve or not
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

// Function to calculate scalar multiplication using double and mult (left to right) algorithm
void ScalarMult_left2right(uint32_t* x, uint32_t* y, uint32_t* scalar, uint32_t* xR, uint32_t* yR) {
    // Initialize result as the point at infinity
    uint32_t xQ[10] = {0}, yQ[10] = {0};  // Q = point at infinity
    uint32_t xTemp[10], yTemp[10];       // Temporary variables for computation

    // Get the bit length of the scalar
    int scalarBitLength = BitLength(scalar);

    // Loop through each bit of the scalar from most significant to least
    for (int i = scalarBitLength - 1; i >= 0; i--) {
        // R = 2*R (point doubling)
        if (xQ[0] != 0 || yQ[0] != 0) { // Skip doubling for the initial point at infinity
            dbl(xQ, yQ, xTemp, yTemp);
            memcpy(xQ, xTemp, sizeof(uint32_t) * 10);
            memcpy(yQ, yTemp, sizeof(uint32_t) * 10);
        }

        // Extract the current bit of the scalar
        int flag = (scalar[i / 29] >> (i % 29)) & 1;

        // If bit is 1, perform Q = Q + P
        if (flag) {
            if (xQ[0] == 0 && yQ[0] == 0) {
                // If Q is the point at infinity, set Q = P
                memcpy(xQ, x, sizeof(uint32_t) * 10);
                memcpy(yQ, y, sizeof(uint32_t) * 10);
            } else {
                // Q = Q + P using point addition
                add(xQ, yQ, x, y, xTemp, yTemp);
                memcpy(xQ, xTemp, sizeof(uint32_t) * 10);
                memcpy(yQ, yTemp, sizeof(uint32_t) * 10);
            }
        }
    }

    // Result is stored in Q
    memcpy(xR, xQ, sizeof(uint32_t) * 10);
    memcpy(yR, yQ, sizeof(uint32_t) * 10);
}

// Function to calculate scalar multiplication using double and mult (right to left) algorithm
void ScalarMult_right2left(uint32_t* x, uint32_t* y, uint32_t* scalar, uint32_t* xR, uint32_t* yR) {
    // Initialize Q = point at infinity and R = P
    uint32_t xQ[10] = {0}, yQ[10] = {0};   // Q = point at infinity (0, 0)
    uint32_t xTemp[10], yTemp[10];        // Temporary variables for computation
    memcpy(xR, x, sizeof(uint32_t) * 10); // R(xR, yR) = P(x, y)
    memcpy(yR, y, sizeof(uint32_t) * 10);

    // Get the bit length of the scalar
    int scalarBitLength = BitLength(scalar);

    // Loop through each bit of the scalar from least significant to most
    for (int i = 0; i < scalarBitLength; i++) {
        int flag = (scalar[i / 29] >> (i % 29)) & 1;
        
        if (flag) {
            //Q = Q + R
                
            if (xQ[0] == 0 && yQ[0] == 0) {
                // Q = R if Q is point at infinity
                memcpy(xQ, xR, sizeof(uint32_t) * 10);
                memcpy(yQ, yR, sizeof(uint32_t) * 10);
            } else {
                // Q = Q + R using point addition
                add(xQ, yQ, xR, yR, xTemp, yTemp); // Temporary variables for Q + R
                memcpy(xQ, xTemp, sizeof(uint32_t) * 10);
                memcpy(yQ, yTemp, sizeof(uint32_t) * 10);
            }
        }
        // R = 2*R using point doubling
        uint32_t tempX[10], tempY[10];
        dbl(xR, yR, tempX, tempY);
        memcpy(xR, tempX, sizeof(uint32_t) * 10);
        memcpy(yR, tempY, sizeof(uint32_t) * 10);
    }

    // Result is stored in Q
    memcpy(xR, xQ, sizeof(uint32_t) * 10);
    memcpy(yR, yQ, sizeof(uint32_t) * 10);
}




