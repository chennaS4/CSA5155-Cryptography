#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
uint64_t cbc_mac(uint64_t key, uint64_t message) {
    uint64_t mac = message ^ key;
    return mac;
}

int main() {
    uint64_t key = 0x1234567890abcdef;
    uint64_t message = 0x1111111111111111;
    uint64_t mac = cbc_mac(key, message);
    printf("MAC of one-block message: %llx\n", mac);
    uint64_t message2 = message ^ mac;
    uint64_t mac2 = cbc_mac(key, message2);
    printf("MAC of two-block message: %llx\n", mac2);
printf("Adversary knows the MAC of two-block message: %llx\n", mac);

    return 0;
}