#include <stdio.h>

int main(void) {
    char name[20];

    printf("Name: ");
    scanf("%s", name);
    
    printf("Hello, %s!\n", name);
    return 0;
}