#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <exec_function>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "execl") == 0) {
        printf("Using execl\n");
    } else if (strcmp(argv[1], "execlp") == 0) {
        printf("Using execlp\n");
    } else if (strcmp(argv[1], "execle") == 0) {
        printf("Using execle\n");
    } else if (strcmp(argv[1], "execv") == 0) {
        printf("Using execv\n");
    } else if (strcmp(argv[1], "execvp") == 0) {
        printf("Using execvp\n");
    } else if (strcmp(argv[1], "execvpe") == 0) {
        printf("Using execvpe\n");
    } else {
        fprintf(stderr, "Unknown exec function: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

