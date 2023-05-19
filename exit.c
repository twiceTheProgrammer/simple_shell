#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

int handle_exit()
{
    char cmd[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *path = getenv("PATH");
    char *token = strtok(cmd, " ");
    char *path_token = strtok(path, ":");
    int i = 0;

    while (1)
    {
        printf("$ ");
        fflush(stdout);

        if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        if (strlen(cmd) == 0)
        {
            continue;
        }

        if (strcmp(cmd, "exit") == 0)
        {
            exit(EXIT_SUCCESS);
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

        while (path_token != NULL)
        {
            char cmd_path[MAX_COMMAND_LENGTH];
            strcpy(cmd_path, path_token);
            strcat(cmd_path, "/");
            strcat(cmd_path, args[0]);

            if (access(cmd_path, F_OK) == 0)
            {
                int pid = fork();

                if (pid < 0)
                {
                    printf("Error: Failed to fork process\n");
                    break;
                }

                if (pid == 0)
                {
                    execve(cmd_path, args, NULL);
                    printf("Error: Failed to execute '%s'\n", args[0]);
                    exit(EXIT_FAILURE);
                }

                waitpid(pid, NULL, 0);

                break;
            }

            path_token = strtok(NULL, ":");
        }

        if (path_token == NULL)
        {
            printf("Error: '%s' command not found\n", args[0]);
        }
    }

    return 0;
}
