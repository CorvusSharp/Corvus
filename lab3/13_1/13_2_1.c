#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

// Custom output function to handle both terminal and file output
void print_output(const char *message) {
    printf("%s", message); // Print to the terminal

    FILE *file = fopen("output.txt", "a");
    if (file) {
        fputs(message, file); // Write to the file
        fclose(file);
    } else {
        perror("Error opening output file");
    }
}

void case_a() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        print_output("Case A: Child process running.\n");
        sleep(2);
        print_output("Case A: Child process finishing.\n");
        exit(EXIT_SUCCESS);
    } else { // Parent process
        int status;

        // Wait for the child process to finish
        waitpid(pid, &status, 0);
        print_output("Case A: Parent process after child process completion.\n");
    }
}

void case_b() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        print_output("Case B: Child process running.\n");
        sleep(4);
        print_output("Case B: Child process finishing.\n");
        exit(EXIT_SUCCESS);
    } else { // Parent process
        print_output("Case B: Parent process finishing without waiting for child process.\n");
        exit(EXIT_SUCCESS);
    }
}

void case_c() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        print_output("Case C: Child process running.\n");
        sleep(6);
        print_output("Case C: Child process finishing.\n");
        exit(EXIT_SUCCESS);
    } else { // Parent process
        print_output("Case C: Parent process not waiting for child process.\n");
    }
}

int main() {
    print_output("Starting demonstration of all three situations:\n");

    case_a();

    case_b();
    sleep(5); // Sleep to allow the child process of case B to complete

    case_c();
    print_output("Execute 'ps' command to observe the process states:\n");
    system("ps -o pid,ppid,stat,command");

    // Wait for the child process of case C to prevent a zombie process
    int status;
    waitpid(-1, &status, 0);

    print_output("End of demonstration.\n");

    return 0;
}

