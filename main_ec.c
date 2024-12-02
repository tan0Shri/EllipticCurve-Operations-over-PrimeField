//bash to run the code
//compile-- "gcc -o main main_ec . c FieldArithmetic . c Exponentiation . c ec_operations . c"
//run-- "./main"

#include<stdio.h>
#include "utilities.h"
#include "ec_utilities.h"

int main()
{
    //Taking prime related inputs for defining the Field
    PrimeInputs();

    // Opening input file
    FILE *in = fopen("ec_inputs1.txt", "r");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }
    //opning output file
    out = fopen("ec_outputs.txt", "w");
    if (out == NULL) {
        perror("Error opening file");
        return 1;
    }

    //  Taking inputs for curve parameters from the file
    uint8_t a_16[32], b_16[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&a_16[i]);
    }
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&b_16[i]);
    }
    //printing the given curve
    fprintf(out, "Given elliptic curve: y^2 = x^3 + ax + b (mod p) where \na = ");
    printBytes(a_16, 32);
    fprintf(out, "b = ");
    printBytes(b_16, 32);
    // convert a and b to base 29
    ToBase29(a_16, a, 32);
    ToBase29(b_16, b, 32);
        
    // copying the 1st pair of point on the curve from Input file
    uint8_t x1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&x1[i]);
    }
    uint8_t y1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&y1[i]);
    }
    fprintf(out, "\nGiven first point (x1,y1):\n");
    fprintf(out, "x1 : ");
    printBytes(x1,32);
    fprintf(out, "y1 : ");
    printBytes(y1,32);

    // copying the 2nd pair of point on the curve from Input file
    uint8_t x2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&x2[i]);
    }
    uint8_t y2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&y2[i]);
    }
    fprintf(out, "Given 2nd point (x2,y2):\n");
    fprintf(out, "x2 : ");
    printBytes(x2,32);
    fprintf(out, "y2 : ");
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
    fprintf(out, "Point (x1, y1) is not on the curve!\n");
    return 1;
    }
    if (!IsPointOnCurve(x2_29, y2_29)) {
        fprintf(out, "Point (x2, y2) is not on the curve!\n");
        return 1;
    }

    fprintf(out, "Given points lies on curve.\n");

    //point addition : (x1,y1) + (x2,y2)
    uint32_t x3_29[10], y3_29[10];
    add(x1_29, y1_29, x2_29, y2_29, x3_29, y3_29);
    uint8_t x3[32], y3[32];
    ToBase16(x3_29, x3);
    ToBase16(y3_29, y3);
    fprintf(out, "\naddition results (x1,y1) + (x2,y2) = (x3,y3):\n");
    fprintf(out, "x3 : ");
    printBytes(x3, 32);
    fprintf(out, "y3 : ");
    printBytes(y3, 32);

    // dbl of (x1, y1)
    uint32_t x4_29[10], y4_29[10];
    dbl(x1_29, y1_29, x4_29, y4_29);
    uint8_t x4[32], y4[32];
    ToBase16(x4_29, x4);
    ToBase16(y4_29, y4);
    fprintf(out, "\ndoubling results (x1,y1)^2 = (x4,y4):\n");
    fprintf(out, "x4 : ");
    printBytes(x4, 32);
    fprintf(out, "y4 : ");
    printBytes(y4, 32);

    //scalar multiplication
    fprintf(out, "\n----------------------------------------");
    fprintf(out, "\nscalar multiplication of (x1,y1) :\n");
    fprintf(out, "------------------------------------------\n");
    uint8_t scalar[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&scalar[i]);
    }
    fprintf(out, "scalar: ");
    printBytes(scalar, 32);
    uint32_t scalar_29[10];
    ToBase29(scalar, scalar_29, 32);

    fprintf(out, "\n(x5,y5) (using double-and-add method (left to right))-\n");
    uint32_t x5_29[10], y5_29[10];
    ScalarMult_left2right(x1_29, y1_29, scalar_29, x5_29, y5_29);
    uint8_t x5[32], y5[32];
    ToBase16(x5_29, x5);
    ToBase16(y5_29, y5);
    fprintf(out, "x5 : ");
    printBytes(x5, 32);
    fprintf(out, "y5 : ");
    printBytes(y5, 32);

    fprintf(out, "\n(x6,y6) (using double-and-add method (right to left))-\n");
    uint32_t x6_29[10], y6_29[10];
    ScalarMult_right2left(x1_29, y1_29, scalar_29, x6_29, y6_29);
    uint8_t x6[32], y6[32];
    ToBase16(x6_29, x6);
    ToBase16(y6_29, y6);
    fprintf(out, "x6 : ");
    printBytes(x6, 32);
    fprintf(out, "y6 : ");
    printBytes(y6, 32);


    
    fclose(in);
    fclose(out);
    return 0;
}