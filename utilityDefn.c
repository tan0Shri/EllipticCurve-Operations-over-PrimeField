#include<stdio.h>
#include "utilities.h"

uint8_t prime[32] = {0xe9, 0x2e, 0x40, 0xad, 0x6f, 0x28, 0x1c, 0x8a,
                     0x08, 0x2a, 0xfd, 0xc4, 0x9e, 0x13, 0x72, 0x65,
                     0x94, 0x55, 0xbe, 0xc8, 0xce, 0xea, 0x04, 0x3a,
                     0x61, 0x4c, 0x83, 0x5b, 0x7f, 0xe9, 0xef, 0xf5};

//Function to print bytes
void printBytes(uint8_t* a, int num){
    for(int i = 0; i < num; i++){
        printf("%02x ",a[i]);
    }
    printf("\n");
}

// Function to convert a number to base 29
void ToBase29(uint8_t* b, uint32_t* c){
    c[8] = ((uint32_t)b[31] | ((uint32_t)b[30] << 8) | ((uint32_t)b[29] << 16) | ((uint32_t)b[28] << 24)) & 0x1fffffff;
    c[7] = ((uint32_t)b[28] >> 5) | ((uint32_t)b[27] << 3) | ((uint32_t)b[26] << 11) | ((uint32_t)b[25] << 19) | ((uint32_t)b[24] << 27) & 0x1fffffff;
    c[6] = ((uint32_t)b[24] >> 2) | ((uint32_t)b[23] << 6) | ((uint32_t)b[22] << 14) | ((uint32_t)b[21] << 22) & 0x1fffffff;
    c[5] = ((uint32_t)b[21] >> 7) | ((uint32_t)b[20] << 1) | ((uint32_t)b[19] << 9) | ((uint32_t)b[18] << 17) | ((uint32_t)b[17] <<25) & 0x1fffffff;
    c[4] = ((uint32_t)b[17] >> 4) | ((uint32_t)b[16] << 4) | ((uint32_t)b[15] << 12) | ((uint32_t)b[14] << 20) | ((uint32_t)b[13] << 28) & 0x1fffffff; 
    c[3] = ((uint32_t)b[13] >> 1) | ((uint32_t)b[12] << 7) | ((uint32_t)b[11] << 15) | ((uint32_t)b[10] << 23) & 0x1fffffff;
    c[2] = ((uint32_t)b[10] >> 6) | ((uint32_t)b[9] << 2) | ((uint32_t)b[8] << 10) | ((uint32_t)b[7] << 18) | ((uint32_t)b[6] << 26) & 0x1fffffff;
    c[1] = ((uint32_t)b[6] >> 3) | ((uint32_t)b[5] << 5) | ((uint32_t)b[4] << 13) | ((uint32_t)b[3] << 21) & 0x1fffffff;
    c[0] = (uint32_t)b[2] | ((uint32_t)b[1] << 8) | ((uint32_t)b[0] << 16) & 0x0fffffff;
}

/*void ToBase29(uint8_t* b, uint32_t* c) {
    int byteIndex = 0;  // Tracks position in the 'b' array
    int bitRightShift[] = {0, 5, 2, 7, 4, 1, 6, 3};  // Different shifts for each 29-bit chunk
    int bitLeftShift[] = {0, 27, 0, 25, 28, 0, 26, 0};

    for (int i = 0; i < 7; i++) {
        c[i] = (uint32_t)b[byteIndex] |
               ((uint32_t)b[byteIndex + 1] << 8) |
               ((uint32_t)b[byteIndex + 2] << 16) |
               ((uint32_t)b[byteIndex + 3] << 24);
        c[i] = (bitRightShift[i] == 0 || bitRightShift[i] == 4) ? (c[i] >> bitRightShift[i]) | (((uint32_t)b[byteIndex + 4]) << bitLeftShift[i]) : (c[i] >> bitRightShift[i]) ;// Apply shifting 
        if (i==2)
        printf("\n%d\n",(bitRightShift[i] == 0 || bitRightShift[i] == 4));
        c[i] &= 0x1FFFFFFF;  //apply mask
        byteIndex += (bitRightShift[i] == 0 || bitRightShift[i] == 4) ? 3 : 4;  // Adjust based on shift
    }

    // Last element handles remaining 24 bits
    c[7] = (uint32_t)b[byteIndex] |
           ((uint32_t)b[byteIndex + 1] << 8) |
           ((uint32_t)b[byteIndex + 2] << 16);
    c[7] &= 0x00FFFFFF;  // Last element stores 24 bits

    for (int i = 0; i < 9; i++)
    {
        printf("\na[%d] = %08x", i, c[i]);
    }
    printf("\n");
}*/

//Function to convert a number to base 16
int ToBase16(uint32_t* c, uint8_t* b){
    b[31] = (uint8_t)c[8];
    b[30] = (uint8_t)(c[8] >> 8);
    b[29] = (uint8_t)(c[8] >> 16);
    b[28] = ((uint8_t)(c[8] >> 24)) | ((uint8_t)(c[7] << 5));

    b[27] = ((uint8_t)(c[7] >> 3));
    b[26] = ((uint8_t)(c[7] >> 11));
    b[25] = ((uint8_t)(c[7] >> 19));
    b[24] = ((uint8_t)(c[7] >> 27)) | ((uint8_t)(c[6] << 2));

    b[23] = ((uint8_t)(c[6] >> 6));
    b[22] = ((uint8_t)(c[6] >> 14));
    b[21] = ((uint8_t)(c[6] >> 22)) | ((uint8_t)(c[5] << 7));

    b[20] = ((uint8_t)(c[5] >> 1));
    b[19] = ((uint8_t)(c[5] >> 9));
    b[18] = ((uint8_t)(c[5] >> 17));
    b[17] = ((uint8_t)(c[5] >> 25)) | ((uint8_t)c[4] << 4);
    
    b[16] = ((uint8_t)(c[4] >> 4));
    b[15] = ((uint8_t)(c[4] >> 12));
    b[14] = ((uint8_t)(c[4] >> 20));
    b[13] = ((uint8_t)(c[4] >> 28)) | ((uint8_t)(c[3] << 1)); 

    b[12] = ((uint8_t)(c[3] >> 7));
    b[11] = ((uint8_t)(c[3] >> 15));
    b[10] = ((uint8_t)(c[3] >> 23)) | ((uint8_t)(c[2] << 6));

    b[9] = ((uint8_t)(c[2] >> 2));
    b[8] = ((uint8_t)(c[2] >> 10));
    b[7] = ((uint8_t)(c[2] >> 18));
    b[6] = ((uint8_t)(c[2] >> 26)) | ((uint8_t)(c[1] << 3));

    b[5] = ((uint8_t)(c[1] >> 5));
    b[4] = ((uint8_t)(c[1] >> 13));
    b[3] = ((uint8_t)(c[1] >> 21)); 
    
    b[2] = (uint8_t)c[0];
    b[1] = ((uint8_t)(c[0] >> 8));
    b[0] = ((uint8_t)(c[0] >> 16));

    int carry = ((c[0] >> 24) != 0)? 1 : 0; 
}

//Function to add packed numbers in base 29
void ADD(uint32_t* num1, uint32_t* num2, uint32_t* sum, uint32_t carry){
    uint32_t mask = 0x1FFFFFFF; // 29-bit mask: 0x1FFFFFFF
    
    for (int i = 8; i >= 0; i--){
        sum[i] = num1[i] + num2[i] + carry;
        carry = (i == 0)? (sum[i] >> 24) : (sum[i] >> 29);
        sum[i] &= mask; //keep elements with least significant 29 bits
    }
}

//Function to add numbers in prime field
void FieldAddition(uint32_t* num1, uint32_t* num2, uint8_t* res){
    uint32_t sum[9];
    ADD(num1, num2, sum, 0);

    //Pack the prime to base 29
    uint32_t p[9];
    ToBase29(prime, p);

    //computing Complement of the prime
    uint8_t prime_comp[32]; 
    for(int i = 31; i>= 0; i--){
        prime_comp[i] = ~prime[i];
    }
    //Pack complement of the prime to base 29
    uint32_t p_comp[9];
    ToBase29(prime_comp, p_comp);

    //To check if sum is greater than prime or not
    int IsGreater = 0;
    for(int i = 0; i < 9; i++ ){
        if(sum[i] > p[i]){
            IsGreater = 1;
            break;
        }
        else if (sum[i] == p[i]){
            continue;
        }
        else break;
    }
    
    //reduction for to make sum a field element, i.e., if sum if greater than p, return sum-p; else return sum    
    (IsGreater == 1)? ADD(sum,p,sum,1) : NULL;   //subtraction 'sum-p' is done using 2's complement
    
    //Convert packed number back to base 16 for output
    ToBase16(sum, res);
}

