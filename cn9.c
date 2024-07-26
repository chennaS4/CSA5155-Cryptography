#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define ALPHABET_SIZE 25

char playfair_matrix[SIZE][SIZE];

void generate_playfair_matrix(const char* keyword) {
    int used[26] = {0};
    int row = 0, col = 0;
    for (int i = 0; i < strlen(keyword); i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            playfair_matrix[row][col++] = ch;
            if (col == SIZE) { row++; col = 0; }
            used[ch - 'A'] = 1;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            playfair_matrix[row][col++] = ch;
            if (col == SIZE) { row++; col = 0; }
            used[ch - 'A'] = 1;
        }
    }
}

void find_position(char ch, int* row, int* col) {
    if (ch == 'J') ch = 'I'; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfair_matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decrypt_pair(char* pair) {
    int row1, col1, row2, col2;
    find_position(pair[0], &row1, &col1);
    find_position(pair[1], &row2, &col2);

    if (row1 == row2) {
        pair[0] = playfair_matrix[row1][(col1 + SIZE - 1) % SIZE];
        pair[1] = playfair_matrix[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        pair[0] = playfair_matrix[(row1 + SIZE - 1) % SIZE][col1];
        pair[1] = playfair_matrix[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        pair[0] = playfair_matrix[row1][col2];
        pair[1] = playfair_matrix[row2][col1];
    }
}

void decrypt_message(const char* ciphertext, char* plaintext) {
    for (int i = 0; i < strlen(ciphertext); i += 2) {
        char pair[3] = {ciphertext[i], ciphertext[i + 1], '\0'};
        decrypt_pair(pair);
        plaintext[i] = pair[0];
        plaintext[i + 1] = pair[1];
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    const char* keyword = "KEYWORD"; // Replace with your keyword
    const char* ciphertext = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONCONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[256];

    generate_playfair_matrix(keyword);

    printf("Playfair matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", playfair_matrix[i][j]);
        }
        printf("\n");
    }

    decrypt_message(ciphertext, plaintext);
    printf("Decrypted message: %s\n", plaintext);

    return 0;
}
