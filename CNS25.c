#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
uint64_t decrypt_block(uint64_t ciphertext, uint64_t n, uint64_t factor) {
    uint64_t e_inv = 1;
    uint64_t mod = n / factor;
    uint64_t e = 65537;
    while ((e_inv * e) % mod != 1)
        e_inv++;
    uint64_t plaintext = 1;
    int i;
	for (i = 0; i < e_inv; i++)
plaintext = (plaintext * ciphertext) % mod;
    return plaintext;
}

int main() {
    uint64_t n = 3233; 
    uint64_t factor = 101; 
    uint64_t ciphertext[] = {2221, 2551, 2781}; 

    int i;
	for (i = 0; i < 3; i++) {
        uint64_t plaintext = decrypt_block(ciphertext[i], n, factor);
        printf("Plaintext block %d: %llu\n", i, plaintext);
    }

    return 0;
}