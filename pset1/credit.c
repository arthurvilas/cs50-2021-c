#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool checksum(unsigned long number);

int main(void) {
    unsigned long cardNumber, counter;
    int twoFirstDigits, len = 0;

    printf("Number: ");
    scanf("%ld", &cardNumber);

    if (!checksum(cardNumber)) {
        printf("INVALID\n");
        return 1;
    }

    counter = cardNumber;
    while (counter > 0) {
        counter /= 10;
        len++;
    }
    
    twoFirstDigits = cardNumber / (pow(10, len - 2));

    if (len == 15 && (twoFirstDigits == 34 || twoFirstDigits == 37)) {
        printf("AMERICAN EXPRESS\n");

    } else if (len == 16 && (twoFirstDigits >= 51 && twoFirstDigits <= 55)) {
        printf("MASTERCARD\n");
        
    } else if ((len == 13 || len == 16) && ((twoFirstDigits / 10) % 10 == 4)) {
        printf("VISA\n");

    } else {
        printf("INVALID\n");
    }

    return 0;
}

bool checksum(unsigned long number) {
    int multipliedDigits = 0, notMultipliedDigits = 0;

    while (number > 0) {
        notMultipliedDigits += number % 10;
        number /= 10;

        int digitTimesTwo = (number % 10) * 2;
        while (digitTimesTwo > 0) {
            multipliedDigits += digitTimesTwo % 10;
            digitTimesTwo /= 10;
        }

        number /= 10;
    }

    if ((multipliedDigits + notMultipliedDigits) % 10 == 0) {
        return true;
    } else {
        return false;
    }
}