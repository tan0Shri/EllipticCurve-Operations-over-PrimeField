//bash to run this main--
//compile-- "gcc -o main main_FieldArithmetic.c FieldArithmetic.c Exponentiation.c"
//run-- "./main"
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
    //Opening output file
    out = fopen("output_Field.txt", "w");
    if (out == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // copy num1 from the file
    uint8_t num1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num1[i]);
    }
    //copy num2 from the file
    uint8_t num2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num2[i]);
    }

    fprintf(out, "-----------------------------------------------------------------------------");
    fprintf(out, "\nFIELD ARITHMETIC OUTPUTS:\n");
    fprintf(out, "-----------------------------------------------------------------------------\n");

    fprintf(out, "Two numbers given-\n");
    fprintf(out, "a: ");
    printBytes(num1,32);
    fprintf(out, "b: ");
    printBytes(num2,32);

    //Convert num1 into base 29
    uint32_t n1[10] ={0};
    ToBase29(num1, n1, 32); 
    
    //Convert num2 into base 29
    uint32_t n2[10] ={0};
    ToBase29(num2, n2, 32);

    //Adding num1 and num2
    uint32_t sum_29[10];
    FieldAddition(n1, n2, sum_29);
    uint8_t sum[32];
    ToBase16(sum_29, sum);  
    fprintf(out, "\nSum a+b mod p: ");  
    printBytes(sum, 32);

    //subtracting num1 and num2: num1 - num2
    uint32_t sub_29[10];
    FieldSubtraction(n1, n2, sub_29);
    uint8_t sub[32];
    ToBase16(sub_29, sub);  
    fprintf(out, "Sub a-b mod p: ");  
    printBytes(sub, 32);

    //Multiplying num1 and num2
    uint32_t mult_base29[10];
    FieldMult(n1, n2, mult_base29);
    fprintf(out, "Mult a*b mod p: ");   
    uint8_t mult[32];
    ToBase16(mult_base29, mult);
    printBytes(mult, 32);

    //Inverse of num1
    uint32_t inv_29[10];
    FieldInverse(n1, inv_29);
    uint8_t inv1[32];
    ToBase16(inv_29, inv1);
    fprintf(out, "Inv a^{-1} mod p: ");
    printBytes(inv1, 32);

    // Dividing num1 by num2 in primeField
    uint32_t div_29[10];
    FieldDivision(n1, n2, div_29);
    uint8_t div[32];
    ToBase16(div_29, div);
    fprintf(out, "Div a/b mod p: ");
    printBytes(div, 32);

    fprintf(out, "\n-----------------------------------------------------------------------------");
    fprintf(out, "\nEXPONENTIATION OUTPUTS:\n");
    fprintf(out, "-----------------------------------------------------------------------------\n");
    fprintf(out, "Default Argument for Exponentiation is fixed here at primitive element of the group, i.e, g = 2");

    //Exponentiation of primitive element g=2
    uint8_t exponent[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&exponent[i]);
    }
    fprintf(out, "\nGiven exponent for exponentiation:\ne = ");
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
    fprintf(out, "\nRequired result (using left-to-right square and multiply algorithm):\n");
    fprintf(out, "g^e mod p: ");
    printBytes(res1, 32);

    //computation of g^exponent (right 2 left)
    uint32_t res2_29[10] = {0};
    FieldExp_right2left(g, exp, res2_29);
    uint8_t res2[32];
    ToBase16(res2_29, res2);
    fprintf(out, "\nRequired result (using right-to_left square and multiply algorithm):\n");
    fprintf(out, "g^e mod p: ");
    printBytes(res2, 32);

    //computation of g^exponent (Montgomery Scalar multiplication)
    uint32_t res3_29[10] = {0};
    FieldExp_Montgomery(g, exp, res3_29);
    uint8_t res3[32];
    ToBase16(res3_29, res3);
    fprintf(out, "\nRequired result (using montgomery scalar multiplication):\n");
    fprintf(out, "g^e mod p: ");
    printBytes(res3, 32);

    //computation of g^exponent (Montgomery Scalar multiplication without BRANCHING)
    uint32_t res4_29[10] = {0};
    FieldExp_Montgomery_noBranching(g, exp, res4_29);
    uint8_t res4[32];
    ToBase16(res4_29, res4);
    fprintf(out, "\nRequired result (using montgomery scalar multiplication WITHOUT BRANCHING):\n");
    fprintf(out, "g^e mod p: ");
    printBytes(res4, 32);

    fclose(in);
    fclose(out);
    return 0;
}

