#include "main.h"

/**
 * get_size - This calculates size to cast argument
 * @format: This formatted string to print the args
 * @k: list of arguments to be produced
 *
 * Return: precision (Successful)
 */
int get_size(const char *format, int *k)
{
	int curr_k = *k + 1;
	int size = 0;

	if (format[curr_k] == 'l')
		size = S_LONG;
	else if (format[curr_k] == 's')
		size = S_SHORT;

	if (size == 0)
		*k = curr_k - 1;
	else
		*k = curr_k;

	return (size);
}
