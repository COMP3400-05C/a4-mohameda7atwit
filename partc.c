#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        puts("ERROR: No arguments");
        return 1;
    }

    const char* word = argv[1];
    const char* file = argv[2];

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 2;
    }

    if (pid == 0) {
        char* gargs[] = {"grep", "-s", "-q", (char*)word, (char*)file, NULL};
        execv("/usr/bin/grep", gargs);
        perror("exec");
        _exit(2);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return 2;
    }

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            printf("FOUND: %s\n", word);
            return 0;
        } else if (code == 1) {
            printf("NOT FOUND: %s\n", word);
            return 0;
        } else if (code == 2) {
            printf("ERROR: %s doesn't exist\n", file);
            return 2;
        } else {
            printf("ERROR: grep returned %d\n", code);
            return 2;
        }
    } else if (WIFSIGNALED(status)) {
        printf("ERROR: child terminated by signal\n");
        return 2;
    }

    return 2;
}
