#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABETLEN 26
#define MAXLEN 5000

int main(int argc, char* argv[]) {

    // Validate Key
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    } else if (argv[1][ALPHABETLEN] != '\0') {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char usedLetters[ALPHABETLEN] = {0};
    for (int i = 0; i < ALPHABETLEN; i++) {
        if (!isalpha(argv[1][i])) {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        argv[1][i] = toupper(argv[1][i]);

        int position = argv[1][i] - 'A';
        if (usedLetters[position] == 0) {
            usedLetters[position]++;
        } else {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    // Get user input
    char text[MAXLEN];
    printf("plaintext: ");
    fgets(text, sizeof(text), stdin);

    // Print ciphertext
    printf("ciphertext: ");
    for (char *p = text; *p != '\0'; p++) {
        if (isupper(*p)) {
            *p = argv[1][*p - 'A'];
            putchar(*p);

        } else if (islower(*p)) {
            *p = tolower(argv[1][*p - 'a']);
            putchar(*p);

        } else {
            putchar(*p);
        }
    }

    return 0;
}