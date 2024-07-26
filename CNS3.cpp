#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int alphabet[26] = {0};
    int i, j, k = 0;
    
    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'j') key[i] = 'i';
        if (!alphabet[key[i] - 'a']) {
            keyMatrix[k / SIZE][k % SIZE] = key[i];
            alphabet[key[i] - 'a'] = 1;
            k++;
        }
    }
    
    for (i = 0; i < 26; i++) {
        if (i == ('j' - 'a')) continue;
        if (!alphabet[i]) {
            keyMatrix[k / SIZE][k % SIZE] = i + 'a';
            k++;
        }
    }
}

void preprocessMessage(char message[], char processedMessage[]) {
    int i, j = 0;
    for (i = 0; message[i] != '\0'; i++) {
        if (message[i] == 'j') message[i] = 'i';
        if (isalpha(message[i])) {
            processedMessage[j++] = tolower(message[i]);
            if (isalpha(message[i + 1]) && tolower(message[i]) == tolower(message[i + 1])) {
                processedMessage[j++] = 'x';
            }
        }
    }
    if (j % 2 != 0) processedMessage[j++] = 'x';
    processedMessage[j] = '\0';
}

void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char keyMatrix[SIZE][SIZE], char ch1, char ch2, char *encryptedPair) {
    int row1, col1, row2, col2;
    findPosition(keyMatrix, ch1, &row1, &col1);
    findPosition(keyMatrix, ch2, &row2, &col2);

    if (row1 == row2) {
        encryptedPair[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        encryptedPair[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encryptedPair[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        encryptedPair[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        encryptedPair[0] = keyMatrix[row1][col2];
        encryptedPair[1] = keyMatrix[row2][col1];
    }
}

void encryptMessage(char message[], char keyMatrix[SIZE][SIZE], char encryptedMessage[]) {
    char processedMessage[200];
    preprocessMessage(message, processedMessage);

    for (int i = 0; processedMessage[i] != '\0'; i += 2) {
        encryptPair(keyMatrix, processedMessage[i], processedMessage[i + 1], &encryptedMessage[i]);
    }
    encryptedMessage[strlen(processedMessage)] = '\0';
}
int main() {
    char key[] = "keyword";
    char keyMatrix[SIZE][SIZE];
    char message[100], encryptedMessage[200];
    generateKeyMatrix(key, keyMatrix);
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';
    encryptMessage(message, keyMatrix, encryptedMessage);
    printf("Encrypted message: %s\n", encryptedMessage);
    return 0;
}
