#include<stdio.h>
#include<stdint.h>

const int L = 10;
#include "utilities.h"



int main()
{
    uint8_t num1[32] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
                        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
                        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
                        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x0f};  
        
    /*uint8_t num1[32];
    for (int i=31;i>=0;i++){
        scanf("%02x",&num1[i]);
    }*/
   uint8_t num2[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                       0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
                       0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
                       0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    
    printf("Two numbers given:\n");
    printBytes(num1,32);
    printBytes(num2,32);

    //Convert num1 into base 29
    uint32_t n1[L];
    ToBase29(num1, n1, 32); 

    /*ToBase16(n1, num1);
    printf("\n");
    printBytes(num1, 32);*/

    //Convert num2 into base 29
    uint32_t n2[L];
    ToBase29(num2, n2, 32);

    //Adding num1 and num2
    uint8_t sum[32];
    FieldAddition(n1, n2, sum);  
    printf("Sum :\n");  
    printBytes(sum, 32);

    uint8_t result[32];
    FieldMult(n1, n2, result);
    printf("MUltiplication :\n");  
    printBytes(result, 32);
}



