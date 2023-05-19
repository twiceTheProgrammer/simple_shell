#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

/**
 *
 * fflush: used to flush output of buffer
 * to ensure prompt is displayed immediately
 * fgets: used to read command from the user, stored in the cmd buffer.
 * strcspn: used to find the index of the newline character in the buffer.
 * strlen: used to check if the command is empty
 * access: used to check if specified command exists as executable file
 * execve: used to execute with specified command and arguments
 *
 * Return: 0 (success)
 */


/**
 * display_prompt - displays the cisfun$ prompt
 *
 * return = 0
 */

void display_prompt()
{
    printf("cisfun$ ");
    fflush(stdout);
}
/**
 * read_cmd - reads input command in the shell
 *
 * return = 0
 */

int read_shell_cmd(char* cmd)
{
    if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
    {
        printf("\n");
        exit(0);
    }
    cmd[strcspn(cmd, "\n")] = '\0';

    if (strlen(cmd) == 0)
    {
        return 0;
    }

    return 1;
}

/**
 * check_executable_file - checks if cmd is executable,
 * prints an error if not execuetale
 * return = 0
 */

int check_executable_file(char* cmd)
{
    if (access(cmd, F_OK) == -1) {
        printf("Error: '%s' command not found\n", cmd);
        return 0;
    }

    return 1;
}

/**
 * main - takes the above functions process and excute with execve
 *
 * return = 0
 */

int execute(void)
{
    char cmd[MAX_COMMAND_LENGTH];
    char **args = (char**) malloc(sizeof(char*) * 2);

    while (1)
    {
        display_prompt();

        if (!read_shell_cmd(cmd))
	{
            continue;
        }

        if (!check_executable_file(cmd))
	{
            continue;
        }
        args[0] = strdup(cmd);
        args[1] = NULL;
        execve(cmd, args, NULL);
 
        printf("Error: Failed to execute '%s'\n", cmd);
    }

    return 0;
}
