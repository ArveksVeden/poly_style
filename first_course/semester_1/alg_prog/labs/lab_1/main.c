#include <stdio.h>

int main(void) {
    int current = 0, maxInt = 0;
    while (current >= maxInt) {
        maxInt = current;
        current++;
    }
    printf("(max) int = %d\n", maxInt);

    maxInt = 0; current = 0;
    while (current <= maxInt) {
        maxInt = current;
        current--;
    }
    printf("(min) int = %d\n", maxInt);

    unsigned int currentUInt = 0, maxUInt = 0;
    while (currentUInt >= maxUInt) {
        maxUInt = currentUInt;
        currentUInt++;
    }
    printf("(max) unsigned int = %u\n", maxUInt);
    printf("(min) unsigned int = 0\n");

    short currentShort = 0, maxShort = 0;
    while (currentShort >= maxShort) {
        maxShort = currentShort;
        currentShort++;
    }
    printf("(max) short = %hd\n", maxShort);

    maxShort = 0; currentShort = 0;
    while (currentShort <= maxShort) {
        maxShort = currentShort;
        currentShort--;
    }
    printf("(min) short = %hd\n", maxShort);

    unsigned short currentUShort = 0, maxUShort = 0;
    while (currentUShort >= maxUShort) {
        maxUShort = currentUShort;
        currentUShort++;
    }
    printf("(max) unsigned short = %hu\n", maxUShort);
    printf("(min) unsigned short = 0\n");

    long currentLong = 0, maxLong = 0;
    while (currentLong >= maxLong) {
        maxLong = currentLong;
        currentLong++;
    }
    printf("(max) long = %ld\n", maxLong);

    maxLong = 0; currentLong = 0;
    while (currentLong <= maxLong) {
        maxLong = currentLong;
        currentLong--;
    }
    printf("(min) long = %ld\n", maxLong);

    unsigned long currentULong = 0, maxULong = 0;
    while (currentULong >= maxULong) {
        maxULong = currentULong;
        currentULong++;
    }
    printf("(max) unsigned long = %lu\n", maxULong);
    printf("(min) unsigned long = 0\n");

    long long currentLongLong = 1, maxLongLong = 1;
    while (currentLongLong >= maxLongLong) {
        maxLongLong = currentLongLong;
        currentLongLong *= 2;
    }
    maxLongLong = maxLongLong * 2 - 1;
    printf("(max) long long = %lld\n", maxLongLong);

    maxLongLong = maxLongLong * (-1) - 1;
    printf("(min) long long = %lld\n", maxLongLong);

    unsigned long long currentULL = 1, maxULL = 1;
    while (currentULL >= maxULL) {
        maxULL = currentULL;
        currentULL *= 2;
    }
    maxULL = maxULL * 2 - 1;

    printf("(max) unsigned long long = %llu\n", maxULL);
    printf("(min) unsigned long long = 0\n");

    unsigned char currentUChar = 0, maxUChar = 0;
    while (currentUChar >= maxUChar) {
        maxUChar = currentUChar;
        currentUChar += 1;
    }
    printf("(max) unsigned char = %u\n", maxUChar);
    printf("(min) unsigned char = 0\n");

    char currentChar = 1, maxChar = 1;
    while (currentChar >= maxChar) {
        maxChar = currentChar;
        currentChar += 1;
    }
    printf("(max) char = %d\n", maxChar);

    currentChar = 1; maxChar = 1;
    while (currentChar <= maxChar) {
        maxChar = currentChar;
        currentChar -= 1;
    }
    printf("(min) char = %d\n", maxChar);

    return 0;
}