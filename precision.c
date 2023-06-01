#include "main.h"

/**
  * get_precision - calc precision
  * @format: format string to print arg
  * @i: pointer to current position in format string
  * @list: list of arguments to be printed
  * Return: Precision.
  */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_l = *i + 1;
	int precision = -1;

	/* Check if precision if specified */
	if (format[curr_l] != '.')
		return (precision);

	precision = 0;

	for (curr_l += 1; format[curr_l] != '\0'; curr_l++)
	{
		if (is_digit(format[curr_l]))
		{
			precision *= 10;
			precision += format[curr_l] - '0';
		}
		else if (format[curr_l] == '*')
		{
			curr_l++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_l - 1;

	return (precision);
}
