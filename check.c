#include <stdio.h>
#include <stdint.h>

#define BASE 29
#define MASK ((1UL << BASE) - 1)
#define ARRAY_SIZE 9

// Function to perform binary subtraction with borrow handling
void subtractBase29(uint32_t result[ARRAY_SIZE], const uint32_t a[ARRAY_SIZE], const uint32_t b[ARRAY_SIZE]) {
    int64_t borrow = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        // Perform subtraction with borrow
        int64_t temp = (int64_t)a[i] - b[i] - borrow;
        
        if (temp < 0) {
            borrow = 1;
            temp += (1UL << BASE);
        } else {
            borrow = 0;
        }

        result[i] = (uint32_t)(temp & MASK); // Store the result with masking
    }

    // If there's a final borrow left, handle it as necessary
    if (borrow) {
        printf("Warning: Underflow occurred during subtraction.\n");
    }
}

int main() {
    // Example input arrays (base 29 representation)
    // uint32_t a[ARRAY_SIZE] = {0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF, 0x1FFFFFFF};
    // uint32_t b[ARRAY_SIZE] = {0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009};
    uint32_t a[ARRAY_SIZE] = {0x000f1e1d, 0x03836343, 0x04605c58, 0x0a8a0989, 0x011101f1, 0x1c3a3836, 0x06864605, 0x18b0a8a0, 0x13121110};
    uint32_t b[ARRAY_SIZE] = {0x00ffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff, 0x1fffffff};
    uint32_t result[ARRAY_SIZE] = {0};

    subtractBase29(result, a, b);

    // Print the result
    printf("Result: \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%08X ", result[i]);
    }
    printf("\n");

    return 0;
}
