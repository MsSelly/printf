#include "main.h"

/**
 * get_width - calc width for output
 * @format: formatted string
 * @i: current index in the format string.
 * @list: list of arguments
 *
 * Return: Calc width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int v;
	int width = 0;

	for (v = *i + 1; format[v] != '\0'; v++)
	{
		if (is_digit(format[v]))
		{
			width *= 10;
			width += format[v] - '0';
		}
		else if (format[v] == '*')
		{
			v++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = v - 1;

	return (width);
}
