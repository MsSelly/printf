#include "main.h"

/**
 * get_flags - calc active flags
 * Desc – produce active flags’
 * @format: format string to produce arg
 * @t: take a parameter
 * Return: active flags
 */

int get_flags(const char *format, int *t)
{

	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j,curr_t;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_t = *t + 1; format[curr_t] != '\0'; curr_t++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_t] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*t = curr_t - 1;

	return (flags);
}
