#include "main.h"

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = strlen(datash->av[0]) + strlen(ver_str);
	length += strlen(datash->args[0]) + strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	strcpy(error, datash->av[0]);
	strcat(error, ": ");
	strcat(error, ver_str);
	strcat(error, ": ");
	strcat(error, datash->args[0]);
	strcat(error, ": Illegal number: ");
	strcat(error, datash->args[1]);
	strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
