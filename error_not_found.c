#include "main.h"

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = strlen(datash->av[0]) + strlen(ver_str);
	length += strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	strcpy(error, datash->av[0]);
	strcat(error, ": ");
	strcat(error, ver_str);
	strcat(error, ": ");
	strcat(error, datash->args[0]);
	strcat(error, ": not found\n");
	strcat(error, "\0");
	free(ver_str);
	return (error);
}
