#include <stdio.h>

int main(void) {
    int h;

    do
    {
        printf("Heigth: ");
        scanf("%d", &h);
    } while (h < 1 || h > 8);

    for (int i = 0; i < h; i++) {
        for (int s = i; s < h - 1; s++) {
            putchar(' ');
        }

        for (int b = 0; b <= i; b++) {
            putchar('#');
        }

        printf("  ");
            for (int b = 0; b <= i; b++) {
            putchar('#');
        }

        putchar('\n');
    }

    return 0;
}