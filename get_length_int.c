#include "main.h"

/**
 * get_len - length of int.
 * @num: param.
 * Return: int.
 */

int get_len(int num)
{
	unsigned int n1;
	int length = 1;

	if (num < 0)
	{
		length++;
		n1 = num * -1;
	}
	else
	{
		n1 = num;
	}
	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}