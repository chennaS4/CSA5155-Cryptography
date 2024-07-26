#include <stdio.h>
#include <ctype.h>
void caesarCipher(char* message, int shift) {
    for (int i = 0; message[i] != '\0'; ++i) {
        if (isupper(message[i])) {
            message[i] = ((message[i] - 'A' + shift) % 26) + 'A';
        } else if (islower(message[i])) {
            message[i] = ((message[i] - 'a' + shift) % 26) + 'a';
        }
    }
}
int main() {
    char message[100];
    int shift;
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the shift value (1 to 25): ");
    scanf("%d", &shift);
    if (shift < 1 || shift > 25) {
        printf("Shift value must be between 1 and 25.\n");
        return 1;
    }
    caesarCipher(message, shift);
    printf("Encrypted message: %s\n", message);

    return 0;
}