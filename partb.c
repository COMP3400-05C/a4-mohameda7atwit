#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        puts("ERROR: No arguments");
        return 1;
    }

    int n = argc - 1; // number of user args
    if (n % 2 == 1) {
        int mid = n / 2; // 0-based
        printf("%s\n", argv[1 + mid]);
    } else {
        int mid1 = n / 2 - 1;
        int mid2 = n / 2;
        printf("%s %s\n", argv[1 + mid1], argv[1 + mid2]);
    }
    return 0;
}
