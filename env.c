#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

extern char **environ;

int main()
{
    char cmd[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGS];
    char *path = getenv("PATH");
    char *token = strtok(cmd, " ");
    int status;
    int i = 0;
    char *path_token = strtok(path, ":");

    while (1)
    {
        printf("cisfun$ ");
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

        if (strcmp(cmd, "exit") == 0)
        {
            exit(0);
        }

        if (strcmp(cmd, "env") == 0)
        {
            char **env = environ;

            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }

            continue;
        }

        while (token != NULL)
        {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;

            if (i >= MAX_ARGS)
            {
                fprintf(stderr, "Error: Too many arguments\n");
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
                pid_t pid = fork();

                if (pid < 0)
                {
                    fprintf(stderr, "Error: Failed to fork process\n");
                    break;
                }

                if (pid == 0)
                {
                    execve(cmd_path, args, NULL);
                    fprintf(stderr, "Error: Failed to execute '%s': %s\n", args[0], strerror(errno));
                    exit(errno);
                }

                waitpid(pid, &status, 0);

                break;
            }

            path_token = strtok(NULL, ":");
        }

        if (path_token == NULL)
        {
            fprintf(stderr, "Error: '%s' command not found\n", args[0]);
        }
    }

    return 0;
}
