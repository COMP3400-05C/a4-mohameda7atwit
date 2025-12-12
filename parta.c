#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        puts("ERROR: No arguments");
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        const char* s = argv[i];
        for (const char* p = s; *p != '\0'; ++p) putchar(toupper((unsigned char)*p));
        if (i + 1 < argc) putchar(',');
    }
    putchar('\n');
    return 0;
}
