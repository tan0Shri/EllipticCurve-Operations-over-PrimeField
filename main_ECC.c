#include<stdio.h>
#include "utilities.h"
#include "ecc_utilities.h"

int main()
{
    //Taking prime related inputs for defining the Field
    PrimeInputs();

    // Opening input file
    FILE *in = fopen("ecc_inputs.txt", "r");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }

    //printing the given curve
    uint8_t a_16[32], b_16[32];
    ToBase16(a, a_16);
    ToBase16(b, b_16);
    printf("Given elliptic curve: y^2 = x^3 + ax + b (mod p) where \na = ");
    printBytes(a_16, 32);
    printf("b = ");
    printBytes(b_16, 32);
        
    // copying the points from Input file
    uint8_t x1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&x1[i]);
    }
    uint8_t y1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&y1[i]);
    }
    printf("\nGiven first points:\n");
    printf("x1 : ");
    printBytes(x1,32);
    printf("y1 : ");
    printBytes(y1,32);

    uint8_t x2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&x2[i]);
    }
    uint8_t y2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&y2[i]);
    }
    printf("Given 2nd points:\n");
    printf("x2 : ");
    printBytes(x2,32);
    printf("y2 : ");
    printBytes(y2,32);

    

    //Convert x1, y1 into base 29
    uint32_t x1_29[10] ={0};
    ToBase29(x1, x1_29, 32); 
    uint32_t y1_29[10] ={0};
    ToBase29(y1, y1_29, 32);
    
    //Convert x2, y2 into base 29
    uint32_t x2_29[10] ={0};
    ToBase29(x2, x2_29, 32); 
    uint32_t y2_29[10] ={0};
    ToBase29(y2, y2_29, 32);

    // check given points lies on curve or not
    if (!IsPointOnCurve(x1_29, y1_29)) {
    printf("Point (x1, y1) is not on the curve!\n");
    return 1;
    }
    if (!IsPointOnCurve(x2_29, y2_29)) {
        printf("Point (x2, y2) is not on the curve!\n");
        return 1;
    }

    printf("Given points lies on curve.\n");

    //point addition : (x1,y1)+(x2,y2)
    uint32_t x3_29[10], y3_29[10];
    add(x1_29, y1_29, x2_29, y2_29, x3_29, y3_29);
    uint8_t x3[32], y3[32];
    ToBase16(x3_29, x3);
    ToBase16(y3_29, y3);
    printf("\naddition results (x1,y1) + (x2,y2) :\n");
    printf("x3 : ");
    printBytes(x3, 32);
    printf("y3 : ");
    printBytes(y3, 32);

    // dbl of (x1, y1)
    uint32_t x4_29[10], y4_29[10];
    dbl(x1_29, y1_29, x4_29, y4_29);
    uint8_t x4[32], y4[32];
    ToBase16(x4_29, x4);
    ToBase16(y4_29, y4);
    printf("\ndoubling results (x1,y1)^2 :\n");
    printf("x4 : ");
    printBytes(x4, 32);
    printf("y4 : ");
    printBytes(y4, 32);

    //scalar multiplication
    printf("\nscalar multiplication of (x1,y1) :\n");
    uint8_t scalar[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&scalar[i]);
    }
    printf("scalar: ");
    printBytes(scalar, 32);
    uint32_t scalar_29[10];
    ToBase29(scalar, scalar_29, 32);

    // Cheching compatibility of exponent for DH-KeyExchange
    if(!IsCompatible(scalar_29)) printf("Warning: Given scalar is not preferrable to use in KeyExchange\n");

    printf("\n(using doubling and addition algorithm (left to right))-\n");
    uint32_t x5_29[10], y5_29[10];
    ScalarMult_left2right(x1_29, y1_29, scalar_29, x5_29, y5_29);
    uint8_t x5[32], y5[32];
    ToBase16(x5_29, x5);
    ToBase16(y5_29, y5);
    printf("x5 : ");
    printBytes(x5, 32);
    printf("y5 : ");
    printBytes(y5, 32);

    printf("\n(using doubling and addition algorithm (right to left))-\n");
    uint32_t x6_29[10], y6_29[10];
    ScalarMult_right2left(x1_29, y1_29, scalar_29, x6_29, y6_29);
    uint8_t x6[32], y6[32];
    ToBase16(x6_29, x6);
    ToBase16(y6_29, y6);
    printf("x6 : ");
    printBytes(x6, 32);
    printf("y6 : ");
    printBytes(y6, 32);


    
    fclose(in);
    return 0;
}

