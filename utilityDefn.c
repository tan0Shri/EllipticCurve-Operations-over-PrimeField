#include<stdio.h>
#include "utilities.h"

//Function to print bytes
void printBytes(uint8_t* a, int num){
    for(int i = num-1; i >= 0; i--){
        printf("%02x ",a[i]);
    }
    printf("\n");
}

// Function to convert a number to base 29
void ToBase29(uint8_t* b, uint32_t* c){
    c[0] = ((uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24)) & 0x1fffffff;
    c[1] = ((uint32_t)b[3] >> 5) | ((uint32_t)b[4] << 3) | ((uint32_t)b[5] << 11) | ((uint32_t)b[6] << 19) | ((uint32_t)b[7] << 27) & 0x1fffffff;
    c[2] = ((uint32_t)b[7] >> 2) | ((uint32_t)b[8] << 6) | ((uint32_t)b[9] << 14) | ((uint32_t)b[10] << 22) & 0x1fffffff;
    c[3] = ((uint32_t)b[10] >> 7) | ((uint32_t)b[11] << 1) | ((uint32_t)b[12] << 9) | ((uint32_t)b[13] << 17) | ((uint32_t)b[14] <<25) & 0x1fffffff;
    c[4] = ((uint32_t)b[14] >> 4) | ((uint32_t)b[15] << 4) | ((uint32_t)b[16] << 12) | ((uint32_t)b[17] << 20) | ((uint32_t)b[18] << 28) & 0x1fffffff; 
    c[5] = ((uint32_t)b[18] >> 1) | ((uint32_t)b[19] << 7) | ((uint32_t)b[20] << 15) | ((uint32_t)b[21] << 23) & 0x1fffffff;
    c[6] = ((uint32_t)b[21] >> 6) | ((uint32_t)b[22] << 2) | ((uint32_t)b[23] << 10) | ((uint32_t)b[24] << 18) | ((uint32_t)b[25] << 26) & 0x1fffffff;
    c[7] = ((uint32_t)b[25] >> 3) | ((uint32_t)b[26] << 5) | ((uint32_t)b[27] << 13) | ((uint32_t)b[28] << 21) & 0x1fffffff;
    c[8] = (uint32_t)b[29] | ((uint32_t)b[30] << 8) | ((uint32_t)b[31] << 16) & 0x0fffffff;
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
void ToBase16(uint32_t* c, uint8_t* b){
    b[0] = (uint8_t)c[0];
    b[1] = (uint8_t)(c[0] >> 8);
    b[2] = (uint8_t)(c[0] >> 16);
    b[3] = ((uint8_t)(c[0] >> 24)) | ((uint8_t)(c[1] << 5));

    b[4] = ((uint8_t)(c[1] >> 3));
    b[5] = ((uint8_t)(c[1] >> 11));
    b[6] = ((uint8_t)(c[1] >> 19));
    b[7] = ((uint8_t)(c[1] >> 27)) | ((uint8_t)(c[2] << 2));

    b[8] = ((uint8_t)(c[2] >> 6));
    b[9] = ((uint8_t)(c[2] >> 14));
    b[10] = ((uint8_t)(c[2] >> 22)) | ((uint8_t)(c[3] << 7));

    b[11] = ((uint8_t)(c[3] >> 1));
    b[12] = ((uint8_t)(c[3] >> 9));
    b[13] = ((uint8_t)(c[3] >> 17));
    b[14] = ((uint8_t)(c[3] >> 25)) | ((uint8_t)c[4] << 4);
    
    b[15] = ((uint8_t)(c[4] >> 4));
    b[16] = ((uint8_t)(c[4] >> 12));
    b[17] = ((uint8_t)(c[4] >> 20));
    b[18] = ((uint8_t)(c[4] >> 28)) | ((uint8_t)(c[5] << 1)); 

    b[19] = ((uint8_t)(c[5] >> 7));
    b[20] = ((uint8_t)(c[5] >> 15));
    b[21] = ((uint8_t)(c[5] >> 23)) | ((uint8_t)(c[6] << 6));

    b[22] = ((uint8_t)(c[6] >> 2));
    b[23] = ((uint8_t)(c[6] >> 10));
    b[24] = ((uint8_t)(c[6] >> 18));
    b[25] = ((uint8_t)(c[6] >> 26)) | ((uint8_t)(c[7] << 3));

    b[26] = ((uint8_t)(c[7] >> 5));
    b[27] = ((uint8_t)(c[7] >> 13));
    b[28] = ((uint8_t)(c[7] >> 21)); 
    
    b[29] = (uint8_t)c[8];
    b[30] = ((uint8_t)(c[8] >> 8));
    b[31] = ((uint8_t)(c[8] >> 16));
}

//Function to add numbers in base 29
void ADD(uint32_t* a, uint32_t* b, uint32_t* sum){
    for (int i = 0 ;i < 9; i++){
        sum[i] = (a[i] + b[i]) % 2;
    }
}