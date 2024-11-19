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

    //Adding num1 and num2
    uint8_t sum[32];
    FieldAddition(n1, n2, sum);  
    printf("\nSum : ");  
    printBytes(sum, 32);

    //subtracting num1 and num2
    uint8_t sub[32];
    FieldSubtraction(n1, n2, sub);  
    printf("Sub : ");  
    printBytes(sub, 32);

    //Multiplying num1 and num2
    uint32_t mult_base29[10];
    FieldMult(n1, n2, mult_base29);
    printf("Mult: ");   
    uint8_t mult[32];
    ToBase16(mult_base29, mult);
    printBytes(mult, 32);

    fclose(in);
    return 0;
}

