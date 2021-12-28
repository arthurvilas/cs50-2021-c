#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLEN 5000

int main(void) {

    char text[MAXLEN], *trav;
    int letters = 0, words = 0, sentences = 0;

    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    
    trav = text;
    while (*trav) {
        if (isalpha(*trav)) {
            letters++;
        } else if (*trav == ' ') {
            words++;
        } else if (*trav == '.' || *trav == '!' || *trav == '?') {
            sentences++;
        }
        trav++;
    }
    words++; // Count first word

    // Coleman-Liau index
    float L = (letters / (float) words) * 100;
    float S = (sentences / (float) words) * 100;

    int grade = round((0.0588 * L - 0.296 * S - 15.8));

    if (grade < 1) {
        printf("Before Grade 1\n");
    } else if (grade >= 16) {
        printf("Grade 16+\n");
    } else {
       printf("Grade %i\n", grade);
    }

    return 0;
}