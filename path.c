#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void path_cmd(char *cmd, char **args, char *path)
{
    char *path_token = strtok(path, ":");
    int status;

    while (path_token != NULL)
    {
        char cmd_path[MAX_COMMAND_LENGTH];
        strcpy(cmd_path, path_token);
        strcat(cmd_path, "/");
        strcat(cmd_path, cmd);

        if (access(cmd_path, F_OK) == 0)
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                printf("Error: Failed to fork process\n");
                break;
            }

            if (pid == 0)
            {
                execve(cmd_path, args, NULL);
                printf("Error: Failed to execute '%s'\n", cmd);
                exit(0);
            }

            waitpid(pid, &status, 0);

            break;
        }

        path_token = strtok(NULL, ":");
    }

    if (path_token == NULL)
    {
        printf("Error: '%s' command not found\n", cmd);
    }
}

int handle_path(void)
{
    char cmd[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *path = getenv("PATH");
    char *token = strtok(cmd, " ");
    int i = 0;

    while (1)
    {
        printf(":) ");
        fflush(stdout);

        if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            exit(0);
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        if (strlen(cmd) == 0)
        {
            continue;
        }
        
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

        path_cmd(args[0], args, path);
    }

    return 0;
}
