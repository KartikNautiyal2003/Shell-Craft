#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_LINE 1000
#define MAX_ARGS 70

// Function to display the prompt with smile emoji
void print_prompt()
{
    printf(":)  "); // Simple smile as prompt
    fflush(stdout);
}

// Function to handle built-in pwd
void builtin_pwd()
{
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) //Get current working directory
    {
        printf("%s\n", cwd);
    }
    else
    {
        printf(":( Error: Could not get current directory\n");
    }
}

// Function to handle built-in cd
void builtin_cd(char *path)
{
    if (path == NULL)
    {
        printf(":( Error: Please provide a path\n");
        return;
    }
    if (chdir(path) != 0) //Change directory (return 0 on success)
    {
        printf(":( Error: Cannot change directory\n");
    }
}

// Function to parse the input into arguments
void parse_input(char *line, char **args)
{
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

// Function to handle input/output redirection
void handle_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror(":( Error opening file for output");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        else if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                perror(":( Error opening file for input");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}

// Function to execute external or built-in command
void execute_command(char **args)
{
    if (args[0] == NULL)
        return; // Empty command

    // Handle built-in commands
    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        builtin_cd(args[1]);
        return;
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        builtin_pwd();
        return;
    }

    pid_t pid = fork();
    if (pid == 0)  //For child process
    {
        handle_redirection(args); // Redirect if needed (replace STDIO with some file)
        execvp(args[0], args);  //System call
        printf(":( Error: Command not found\n"); // Command failed
        exit(1);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        printf(":( Error: Fork failed\n");
    }
}

int main()
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1)
    {
        print_prompt();

        if (!fgets(line, MAX_LINE, stdin))
        {
            break;
        }

        // Remove newline
        line[strcspn(line, "\n")] = 0;

        parse_input(line, args);
        execute_command(args);
    }

    return 0;
}
