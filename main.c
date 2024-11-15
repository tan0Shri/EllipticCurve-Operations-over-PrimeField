#include<stdio.h>
#include<stdint.h>
#include "utilities.h"

int main()
{
    // Opening input file
    in = fopen("input.txt", "r");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }
        
    uint8_t num1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num1[i]);
    }

    uint8_t num2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num2[i]);
    }

    printf("Two numbers given:\n");
    printBytes(num1,32);
    printBytes(num2,32);

    //Convert num1 into base 29
    uint32_t n1[10] ={0};
    ToBase29(num1, n1, 32); 
    
    //Convert num2 into base 29
    uint32_t n2[10] ={0};
    ToBase29(num2, n2, 32);

    //copying the given prime from the file
    for (int i = 31; i >= 0; i--){
        fscanf(in,"%2hhx",&prime[i]);
    }    
    //convert given prime to base 29
    ToBase29(prime, p, 32);  

    //copying the pre computed 'mu' from file for Barrett reduction
    for (int i = 33; i >= 0; i--){
        fscanf(in,"%2hhx",&mu[i]);
    }  
    ToBase29(mu, T, 34);
    
    //Adding num1 and num2
    uint8_t sum[32];
    FieldAddition(n1, n2, sum);  
    printf("\nSum :\n");  
    printBytes(sum, 32);

    //subtracting num1 and num2
    uint8_t sub[32];
    FieldSubtraction(n1, n2, sub);  
    printf("\nSub :\n");  
    printBytes(sub, 32);

    //Multiplying num1 and num2
    uint32_t mult_base29[10];
    FieldMult(n1, n2, mult_base29);
    printf("\nMultiplication :\n");   
    uint8_t mult[32];
    ToBase16(mult_base29, mult);
    printBytes(mult, 32);

    //Exponentiation of primitive element g=2
    uint8_t exponent[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&exponent[i]);
    }
    printf("\nGiven exponent:\n");
    printBytes(exponent, 32);

    //computation of g^exponent (left 2 right)
    uint32_t exp1[10] = {0};
    ToBase29(exponent, exp1, 32);
    for (int i = 9; i >= 0; i--){
        printf("%08x ",exp1[i]);
    } 
    printf("\nBitlength = %d\n", BitLength(exp1));
    printf("\n");
    uint8_t res1[32] = {0};
    FieldExp_left2right(exp1, res1);
    printf("\nRequired result (using left-to-right square and multiply algorithm):\n");
    printBytes(res1, 32);

    //computation of g^exponent (right 2 left)
    uint32_t exp2[10] = {0};
    ToBase29(exponent, exp2, 32);
    uint8_t res2[32] = {0};
    FieldExp_right2left(exp2, res2);
    printf("\nRequired result (using right-to_left square and multiply algorithm):\n");
    printBytes(res2, 32);

    //computation of g^exponent (Montgomery Scalar multiplication)
    uint32_t exp3[10] = {0};
    ToBase29(exponent, exp3, 32);
    uint8_t res3[32] = {0};
    FieldExp_Montgomery(exp3, res3);
    printf("\nRequired result (using montgomery scalar multiplication):\n");
    printBytes(res3, 32);

    //computation of g^exponent (Montgomery Scalar multiplication without BRANCHING)
    uint32_t exp4[10] = {0};
    ToBase29(exponent, exp4, 32);
    uint8_t res4[32] = {0};
    FieldExp_Montgomery_noBranching(exp4, res4);
    printf("\nRequired result (using montgomery scalar multiplication WITHOUT BRANCHING):\n");
    printBytes(res4, 32);

    fclose(in);
    return 0;
}

