#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 50

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

int main(void)
{
    // Get input words from both players
    char word1[MAXLEN], word2[MAXLEN];

    printf("Player 1: ");
    scanf("%s", word1);

    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print result
    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }
    return 0;
}

int compute_score(char *word)
{
    int wordScore = 0;

    while (*word != '\0') {
        if (isupper(*word)) {
            wordScore += POINTS[*word - 'A'];

        } else if (islower(*word)) {
            wordScore += POINTS[*word - 'a'];
        }
        word++;
    }
    return wordScore;
}