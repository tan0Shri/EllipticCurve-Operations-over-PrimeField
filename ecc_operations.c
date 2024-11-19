#include"utilities.h"

// Function to calculate point doubling
void dbl(uint32_t* x1, uint32_t* y1, uint32_t* x3, uint32_t* y3) {
    uint32_t lambda[10] = {0}, temp[10] = {0};
    uint32_t three[10] = {0x3, 0};
    uint32_t a[10] = {0x3, 0};
    uint32_t two[10] = {0x2, 0};
    // Calculate λ = (3*x1^2 + a) / (2*y1) mod p
    FieldMult(x1, x1, temp);           // temp = x1^2
    FieldMult(temp, three, temp);      // temp = 3*x1^2
    FieldAddition(temp, a, temp);      // temp = 3*x1^2 + a
    FieldMult(y1, two, lambda);        // lambda = 2*y1
    Barrett_Red(temp, lambda, lambda); // lambda = (3*x1^2 + a) / (2*y1)

    // Calculate x3 = λ^2 - 2*x1 mod p
    FieldMult(lambda, lambda, x3);    // x3 = λ^2
    FieldAddition(x1, x1, temp);      // temp = 2*x1
    FieldSubtraction(x3, temp, x3);                // x3 = λ^2 - 2*x1

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
    Barrett_Red(temp1, temp2, lambda); // lambda = (y2 - y1) / (x2 - x1)

    // Calculate x3 = λ^2 - x1 - x2 mod p
    FieldMult(lambda, lambda, x3);   // x3 = λ^2
    FieldSubtraction(x3, x1, x3);                 // x3 = λ^2 - x1
    FieldSubtraction(x3, x2, x3);                 // x3 = λ^2 - x1 - x2

    // Calculate y3 = λ*(x1 - x3) - y1 mod p
    FieldSubtraction(x1, x3, temp1);              // temp1 = x1 - x3
    FieldMult(lambda, temp1, y3);    // y3 = λ*(x1 - x3)
    FieldSubtraction(y3, y1, y3);                 // y3 = λ*(x1 - x3) - y1
}
