#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
void countLetterFrequencies(char *ciphertext, int frequencies[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequencies[index]++;
        }
    }
}
void findMostFrequentLetter(int frequencies[], int *maxFreqIndex) {
    int maxFreq = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequencies[i] > maxFreq) {
            maxFreq = frequencies[i];
            *maxFreqIndex = i;
        }
    }
}
void breakAffineCipher(char *ciphertext) {
    int frequencies[ALPHABET_SIZE] = {0};
    int maxFreqIndex = 0, secondFreqIndex = 0;
    countLetterFrequencies(ciphertext, frequencies);
    findMostFrequentLetter(frequencies, &maxFreqIndex);
    int a_guess = (maxFreqIndex - ('e' - 'a')) % ALPHABET_SIZE;
    if (a_guess < 0) {
        a_guess += ALPHABET_SIZE;
    }
    int a_inverse = modInverse(a_guess, ALPHABET_SIZE);
    int b_guess = ((secondFreqIndex - maxFreqIndex) * a_inverse) % ALPHABET_SIZE;
    if (b_guess < 0) {
        b_guess += ALPHABET_SIZE;
    }

    printf("Possible values:\n");
    printf("a = %d, b = %d\n", a_guess, b_guess);
}

int main() {
    char ciphertext[] = "Chenna";
    printf("Ciphertext: %s\n", ciphertext);
    breakAffineCipher(ciphertext);

    return 0;
}
