#include<stdio.h>
#include "utilities.h"

int main()
{
    //Taking prime related inputs for defining the Field
    PrimeInputs();

    // Opening input file
    FILE *in = fopen("input.txt", "r");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("Default Argument for Exponentiation is fixed here at primitive element of the group, i.e, g = 2");

    //Exponentiation of primitive element g=2
    uint8_t exponent[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&exponent[i]);
    }
    printf("\nGiven exponent for exponentiation:\n");
    printBytes(exponent, 32);

    // Converting the exponent to base 29
    uint32_t exp[10] = {0};
    ToBase29(exponent, exp, 32);

    // Cheching compatibility of exponent for DH-KeyExchange
    if(!IsCompatible(exp)) printf("Warning: Given exponent is not preferrable to use in KeyExchange\n"); 

    //computation of g^exponent (left 2 right)
    uint32_t res1_29[10] = {0};
    FieldExp_left2right(g, exp, res1_29);
    uint8_t res1[32];
    ToBase16(res1_29, res1);
    printf("\nRequired result (using left-to-right square and multiply algorithm):\n");
    printBytes(res1, 32);

    //computation of g^exponent (right 2 left)
    uint32_t res2_29[10] = {0};
    FieldExp_right2left(g, exp, res2_29);
    uint8_t res2[32];
    ToBase16(res2_29, res2);
    printf("\nRequired result (using right-to_left square and multiply algorithm):\n");
    printBytes(res2, 32);

    //computation of g^exponent (Montgomery Scalar multiplication)
    uint32_t res3_29[10] = {0};
    FieldExp_Montgomery(g, exp, res3_29);
    uint8_t res3[32];
    ToBase16(res3_29, res3);
    printf("\nRequired result (using montgomery scalar multiplication):\n");
    printBytes(res3, 32);

    //computation of g^exponent (Montgomery Scalar multiplication without BRANCHING)
    uint32_t res4_29[10] = {0};
    FieldExp_Montgomery_noBranching(g, exp, res4_29);
    uint8_t res4[32];
    ToBase16(res4_29, res4);
    printf("\nRequired result (using montgomery scalar multiplication WITHOUT BRANCHING):\n");
    printBytes(res4, 32);

    fclose(in);
    return 0;
}

