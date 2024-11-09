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
    // uint8_t num1[32] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    //                     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    //                     0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    //                     0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x0f};  
    
    // uint8_t num2[32] = {0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff, 
    //                     0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff,
    //                     0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff, 
    //                     0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff};  

    // uint8_t num1[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    //                     0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    //                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    //                    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x00};
        
    uint8_t num1[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num1[i]);
    }

    uint8_t num2[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&num2[i]);
    }


    // uint8_t num2[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    //                    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    //                    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    //                    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x00};
    
    // uint8_t num2[32] = {0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    // uint8_t b[32] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89,
    //                  0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89};

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
    
    //Adding num1 and num2
    uint8_t sum[32];
    FieldAddition(n1, n2, sum);  
    printf("\nSum :\n");  
    printBytes(sum, 32);

    //Multiplying num1 and num2
    uint32_t mult_base29[10];
    FieldMult(n1, n2, mult_base29);
    printf("\nMultiplication :\n");   
    uint8_t mult[32];
    ToBase16(mult_base29, mult);
    printBytes(mult, 32);



    //Exponentiation of primitive element g=2
    initializeBase(); // consider primitive element g as base
    uint8_t exponent[32];
    for (int i = 31; i >= 0; i--){
        fscanf(in, "%02hhx",&exponent[i]);
    }
    printf("\nGiven exponent:\n");
    printBytes(exponent, 32);

    //computation of g^exponent (left 2 right)
    uint32_t exp1[10] = {0};
    ToBase29(exponent, exp1, 32);
    uint8_t res1[32] = {0};
    FieldExp_left2right(exp1, res1);
    printf("\nRequired result (using left-to-right square and multiply algprithm):\n");
    printBytes(res1, 32);

    //computation of g^exponent (right 2 left)
    uint32_t exp2[10] = {0};
    ToBase29(exponent, exp2, 32);
    uint8_t res2[32] = {0};
    FieldExp_right2left(exp2, res2);
    printf("\nRequired result (using right-to_left square and multiply algprithm):\n");
    printBytes(res2, 32);

    fclose(in);
    return 0;
}





