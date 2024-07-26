#include <stdio.h>
#include <stdint.h>
#include <string.h>

void generate_subkeys(uint64_t *k1, uint64_t *k2, uint64_t initial_block, int block_size) {
    uint64_t constant;
    switch(block_size) {
        case 64:
            constant = 0x0000000000000001;
            break;
        case 128:
            constant = 0x00000000000000000000000000000001;
            break;
        default:
            printf("Invalid block size\n");
            return;
    }
    *k1 = (initial_block << 1);
    if((*k1 & (1ULL << (block_size - 1)))) { 
        *k1 ^= constant;
    }
    *k2 = (*k1 << 1);
    if((*k2 & (1ULL << (block_size - 1)))) { 
        *k2 ^= constant;
    }
}
int main() {
    uint64_t initial_block = 0; 
    uint64_t k1, k2;

    printf("Subkeys for 64-bit block size:\n");
    generate_subkeys(&k1, &k2, initial_block, 64);
    printf("K1: 0x%016llx\n", k1);
    printf("K2: 0x%016llx\n", k2);

    printf("\nSubkeys for 128-bit block size:\n");
    generate_subkeys(&k1, &k2, initial_block, 128);
    printf("K1: 0x%032llx\n", k1);
    printf("K2: 0x%032llx\n", k2);

    return 0;
}
