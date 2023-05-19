#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

/**
 * read_cmd : reads input from user
 * @cmd : pointer to the command
*/

void read_cmd(char *cmd)
{
    printf("cisfun$ ");
    fflush(stdout);

    if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }

    cmd[strcspn(cmd, "\n")] = '\0';
}

/**
 * tokenize_cmd : breaks the input into an array of arguments
 * @cmd : pointer to the command
 * @args : double pointer to the argument
*/

void tokenize_cmd(char *cmd, char **args)
{
    char *token = strtok(cmd, " ");
    int i = 0;

    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;

        if (i >= MAX_ARGS)
        {
            printf("Error: Too many arguments\n");
            break;
        }
    }

    args[i] = NULL;
}

/**
 * execute_cmd : checks if command exist and runs it
 * @args : double pointer to argument
*/

void execute_cmd(char **args)
{
	int status;
	pid_t pid = fork();

    if (access(args[0], F_OK) == -1)
    {
        printf("Error: '%s' command not found\n", args[0]);
        return;
    }

    if (pid < 0)
    {
        printf("Error: Failed to fork process\n");
        return;
    }

    if (pid == 0)
    {
        execve(args[0], args, NULL);
        printf("Error: Failed to execute '%s'\n", args[0]);
        exit(0);
    }

    waitpid(pid, &status, 0);
}

/**
 * _main : reads user input,tokenize and execute
 * 
 * Return = 0
*/
int _main(void)
{
    char cmd[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];

    while (1)
    {
        read_cmd(cmd);

        if (strlen(cmd) == 0)
        {
            continue;
        }

        tokenize_cmd(cmd, args);
        execute_cmd(args);
    }

    return 0;
}
