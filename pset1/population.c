#include <stdio.h>

int main(void) {
    int start_size, end_size, years = 0;
    
    do {
        printf("Start size: ");
        scanf("%d", &start_size);
    } while (start_size < 9);

    do {
        printf("End size: ");
        scanf("%d", &end_size);
    } while (end_size < start_size);


    while (start_size < end_size) {
        start_size += (start_size / 3 - start_size / 4);
        years++;
    }

    printf("Years: %d\n", years);

    return 0;
}