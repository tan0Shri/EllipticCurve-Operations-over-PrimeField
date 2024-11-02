#include<stdio.h>
#include "utilities.h"

uint32_t mask = 0x1FFFFFFF; // 29-bit mask: 0x1FFFFFFF

uint8_t prime[32] = {0xe9, 0x2e, 0x40, 0xad, 0x6f, 0x28, 0x1c, 0x8a,
                     0x08, 0x2a, 0xfd, 0xc4, 0x9e, 0x13, 0x72, 0x65,
                     0x94, 0x55, 0xbe, 0xc8, 0xce, 0xea, 0x04, 0x3a,
                     0x61, 0x4c, 0x83, 0x5b, 0x7f, 0xe9, 0xef, 0xf5};

uint8_t mu[34] = {0x04, 0x64,
                 0x35, 0xb5, 0xa4, 0x0b, 0xbb, 0x8b, 0x91, 0xa5,
                 0xac, 0x84, 0xa4, 0xa1, 0x18, 0x09, 0x15, 0xa5,
                 0xee, 0xac, 0x09, 0x5b, 0xe5, 0xdc, 0x75, 0xdd,
                 0xaf, 0xa7, 0x30, 0x29, 0x3a, 0xe0, 0x00, 0x18};

//Function to print bytes
void printBytes(uint8_t* num, int bytes){
    for(int i = bytes-1; i >= 0; i--){
        printf("%02x",num[i]);
    }
    printf("\n");
}

// Function to convert a number to base 29
void ToBase29(uint8_t* src, uint32_t* dest, int bytes){
    dest[0] = ((uint32_t)src[0] | ((uint32_t)src[1] << 8) | ((uint32_t)src[2] << 16) | ((uint32_t)src[3] << 24)) & mask;
    dest[1] = ((uint32_t)src[3] >> 5) | ((uint32_t)src[4] << 3) | ((uint32_t)src[5] << 11) | ((uint32_t)src[6] << 19) | ((uint32_t)src[7] << 27) & mask;
    dest[2] = ((uint32_t)src[7] >> 2) | ((uint32_t)src[8] << 6) | ((uint32_t)src[9] << 14) | ((uint32_t)src[10] << 22) & mask;
    dest[3] = ((uint32_t)src[10] >> 7) | ((uint32_t)src[11] << 1) | ((uint32_t)src[12] << 9) | ((uint32_t)src[13] << 17) | ((uint32_t)src[14] <<25) & mask;
    dest[4] = ((uint32_t)src[14] >> 4) | ((uint32_t)src[15] << 4) | ((uint32_t)src[16] << 12) | ((uint32_t)src[17] << 20) | ((uint32_t)src[18] << 28) & mask; 
    dest[5] = ((uint32_t)src[18] >> 1) | ((uint32_t)src[19] << 7) | ((uint32_t)src[20] << 15) | ((uint32_t)src[21] << 23) & mask;
    dest[6] = ((uint32_t)src[21] >> 6) | ((uint32_t)src[22] << 2) | ((uint32_t)src[23] << 10) | ((uint32_t)src[24] << 18) | ((uint32_t)src[25] << 26) & mask;
    dest[7] = ((uint32_t)src[25] >> 3) | ((uint32_t)src[26] << 5) | ((uint32_t)src[27] << 13) | ((uint32_t)src[28] << 21) & mask;
    dest[8] = (uint32_t)src[29] | ((uint32_t)src[30] << 8) | ((uint32_t)src[31] << 16) & mask;
    if (bytes == 34){
        dest[8] = dest[8] | ((uint32_t)src[32] << 24) & mask;
        dest[9] = (((uint32_t)src[32] >> 5) | ((uint32_t)src[33] << 3)) & mask;
    }
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
void ToBase16(uint32_t* src, uint8_t* dest){
    dest[0] = (uint8_t)src[0];
    dest[1] = (uint8_t)(src[0] >> 8);
    dest[2] = (uint8_t)(src[0] >> 16);
    dest[3] = ((uint8_t)(src[0] >> 24)) | ((uint8_t)(src[1] << 5));

    dest[4] = ((uint8_t)(src[1] >> 3));
    dest[5] = ((uint8_t)(src[1] >> 11));
    dest[6] = ((uint8_t)(src[1] >> 19));
    dest[7] = ((uint8_t)(src[1] >> 27)) | ((uint8_t)(src[2] << 2));

    dest[8] = ((uint8_t)(src[2] >> 6));
    dest[9] = ((uint8_t)(src[2] >> 14));
    dest[10] = ((uint8_t)(src[2] >> 22)) | ((uint8_t)(src[3] << 7));

    dest[11] = ((uint8_t)(src[3] >> 1));
    dest[12] = ((uint8_t)(src[3] >> 9));
    dest[13] = ((uint8_t)(src[3] >> 17));
    dest[14] = ((uint8_t)(src[3] >> 25)) | ((uint8_t)src[4] << 4);
    
    dest[15] = ((uint8_t)(src[4] >> 4));
    dest[16] = ((uint8_t)(src[4] >> 12));
    dest[17] = ((uint8_t)(src[4] >> 20));
    dest[18] = ((uint8_t)(src[4] >> 28)) | ((uint8_t)(src[5] << 1)); 

    dest[19] = ((uint8_t)(src[5] >> 7));
    dest[20] = ((uint8_t)(src[5] >> 15));
    dest[21] = ((uint8_t)(src[5] >> 23)) | ((uint8_t)(src[6] << 6));

    dest[22] = ((uint8_t)(src[6] >> 2));
    dest[23] = ((uint8_t)(src[6] >> 10));
    dest[24] = ((uint8_t)(src[6] >> 18));
    dest[25] = ((uint8_t)(src[6] >> 26)) | ((uint8_t)(src[7] << 3));

    dest[26] = ((uint8_t)(src[7] >> 5));
    dest[27] = ((uint8_t)(src[7] >> 13));
    dest[28] = ((uint8_t)(src[7] >> 21)); 
    
    dest[29] = (uint8_t)src[8];
    dest[30] = ((uint8_t)(src[8] >> 8));
    dest[31] = ((uint8_t)(src[8] >> 16));
    //dest[32] = ((uint8_t)(src[8] >> 24)) | ((uint8_t)(src[9] << 5));
    //dest[33] = ((uint8_t)(src[9] >> 3));
}

//Function to add packed numbers in base 29
void ADD(uint32_t* num1, uint32_t* num2, uint32_t* sum){ 
    uint32_t carry = 0;   
    for (int i = 0; i < 9; i++){
        sum[i] = num1[i] + num2[i] + carry;
        carry = (i == 8)? (sum[i] >> 24) : (sum[i] >> 29);
        sum[i] &= mask; //keep elements with least significant 29 bits
    }
}

//Function to subtract packed numbers in base 29 using 2's complement
void SUB(uint32_t* num1, uint32_t* num2, uint32_t* result){
	uint32_t carry = 1;
	for (int i=0; i < 10; i++){
		result[i] = num1[i] + (num2[i] ^ mask) + carry;
		carry = result[i] >> 29;
		result[i] &= mask;
	}
}

//To check if num1 is greater than num2 or not
int IsGreater(uint32_t* num1, uint32_t* num2){
    int IsGreater = 0;
    for(int i = 9; i >= 0; i-- ){
        if(num1[i] > num2[i]){
            IsGreater = 1;
            break;
        }
        else if (num1[i] == num2[i]){
            continue;
        }
        else break;
    }
    return IsGreater;
}

//Function to add numbers in prime field
void FieldAddition(uint32_t* num1, uint32_t* num2, uint8_t* result){
    uint32_t* sum;
    ADD(num1, num2, sum);

    //Pack the prime to base 29
    uint32_t* p;
    ToBase29(prime, p, 34);
    
    //reduction for to make sum a field element, i.e., if sum if greater than p, return sum-p; else return sum    
    (IsGreater(sum, p) == 1)? SUB(sum,p,sum) : NULL;   //subtraction 'sum-p' is done using 2's complement
    
    //Convert packed number back to base 16 for output
    ToBase16(sum, result);
}

void Mult(uint32_t* num1, uint32_t* num2, uint32_t* result){
    uint64_t mult[20];
    
    // Perform multiplication  
    for (int i=19; i>=0; i--){
        for (int j=9; j>=0; j--){
            if(i-j >= 0 && i-j < 9){
                mult[i] += (uint64_t)num1[j] * (uint64_t)num2[i-j];
            }
        }
    }
    // Convert to 29-bit representation and handle carry
    uint64_t carry = 0;
    for (int i=0; i<=19; i++){
        mult[i] += carry;
        carry = mult[i] >> 29;
        result[i] = (uint32_t)(mult[i] & mask);
    }
    /*for(int i=19; i>=0; i--){
        printf("%08x ",result[i]);
    }*/
}

void Barrett_Red(uint32_t* num, uint32_t* p, uint32_t* result){
    
    uint32_t T[10];
    ToBase29(mu, T, 34);

    uint32_t Q[20];
    Mult(num +9, T, Q);
    
    uint32_t* r1 = num + 11;
    uint32_t temp[10];
    Mult(Q + 11, p, temp);
    uint32_t* r2 = temp + 11;
    //uint32_t r[10];
    SUB(r1, r2, result);

    /*while(IsGreater(r,p) == 1){
        SUB(result, p, result);
    }*/
    int IsGreater = 0;
    for(int i = 9; i >= 0; i-- ){
        if(result[i] > p[i]){
            IsGreater = 1;
            break;
        }
        else if (result[i] == p[i]){
            continue;
        }
        else break;
    }
	(IsGreater == 1)? SUB(result, p, result) : NULL;

}

void FieldMult(uint32_t* num1, uint32_t* num2, uint8_t* result){
    uint32_t temp[2*L];
    // Multiply num1 and num2
    Mult(num1, num2, temp);

    //Pack the prime to base 29
    uint32_t p[L];
    // Convert prime to base 29
    ToBase29(prime, p, 34);

    uint32_t temp1[L];
    // Reduce with Barrett
    Barrett_Red(temp, p, temp1);
    // Convert to base 16 and store in result
    ToBase16(temp1, result);
}