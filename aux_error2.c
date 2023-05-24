#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datash: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = strlen(datash->av[0]) + strlen(ver_str);
	length += strlen(datash->args[0]) + strlen(msg) + 4;
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
	strcat(error, msg);
	strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @datash: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(data_shell *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datash->counter);
	length = strlen(datash->av[0]) + strlen(ver_str);
	length += strlen(datash->args[0]) + 24;
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
	strcat(error, ": Permission denied\n");
	strcat(error, "\0");
	free(ver_str);
	return (error);
}
