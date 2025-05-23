#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *token;

    while (1) {
        printf("> ");  // Minimal prompt symbol
        fflush(stdout);

        if (!fgets(line, MAX_LINE, stdin)) break;

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) break;

        // Tokenize input
        int i = 0;
        token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue; // Skip empty input

        pid_t pid = fork();
        if (pid == 0) {
            // Child: try to run command
            execvp(args[0], args);
            // If we reach here, command failed
            printf(":(\n");
            exit(1);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            // Check if command ran successfully
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                printf(":)\n");
            } else {
                printf(":(\n");
            }
        } else {
            // Fork failed
            printf(":(\n");
        }
    }

    return 0;
}

