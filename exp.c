#include"utilities.h"

int BitLength(uint32_t* num) {
    int b = 0;
    int bit_position = 0;

    // Loop through each 32-bit integer in reverse order
    for (int i = 8; i >= 0; i--) {
        // Check if there are any bits set in the current 32-bit integer
        bit_position = __builtin_clz(num[i]) ^ 31; // Finds the highest bit position set in num[i]
        
        // Accumulate bit length based on the current index and the bit position found
        while(num[i] != 0){
            return i*29 + bit_position +1;
            break;
        }
    }
    return 0;
}

void ModExp_left2right(uint32_t *exp, uint8_t *res){
    uint32_t temp[10] = {0x1, 0};
    uint32_t base[10] = {0x2, 0};

    int expBitLength = BitLength(exp);
    for(int i=8;i>=0;i--){
            printf("%08x ",temp[i]);
        }
        printf("\n");
    for(int i = expBitLength - 1; i >= 0; i--){
        printf("i = %d\n",i);
        FieldMult(temp, temp, temp);
        for(int i=8;i>=0;i--){
            printf("%08x ",temp[i]);
        }
        printf("\n");
        if((exp[i/29] >> (i%29)) & 1){
            FieldMult(temp, base, temp);
        }
        for(int i=8;i>=0;i--){
            printf("%08x ",temp[i]);
        }
        printf("\n");
    } 
    ToBase16(temp, res);
}
