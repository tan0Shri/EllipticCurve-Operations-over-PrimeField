#include<stdio.h>
#include<stdint.h>

int main()
{
    uint64_t a = (uint64_t)0x1fffffff ;
    uint64_t b = (uint64_t)0x1fffffff ;
    printf("%016llx", (uint64_t)(a*b));
}