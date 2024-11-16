#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main() {
    const char *hexString = "046435b5a40bbb8b91a5ac84a4a1180915a5eeac095be5dc75ddafa730293ae00018";
    uint8_t array[34];
    size_t length = strlen(hexString);

    for (size_t i = 0; i < 34; i++) {
        sscanf(hexString + 2 * i, "%2hhx", &array[33-i]);
    }

    // Print the array for verification
    printf("Parsed uint8_t array:\n");
    for (size_t i = 34; i > 0; i--) {
        printf("%02x ", array[i-1]);
    }
    printf("\n");

    return 0;
}
