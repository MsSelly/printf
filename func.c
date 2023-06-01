#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - prints a char
 * @types: list of arguments
 * @buffer: buffer array to handle print
 * @flags:  calculate active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - prints a string
 * @types: list a of arguments
 * @buffer: buffer array to handle print
 * @flags:  calculates active flags
 * @width: get width.
 * @precision: precision specification
 * @size: size specifier
 * Return: number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, u;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (u = width - length; u > 0; u--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (u = width - length; u > 0; u--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - prints percent sign
 * @types: list of arguments
 * @buffer: buffer array handle print
 * @flags:  calculate active flags
 * @width: Get width
 * @precision: precision specification
 * @size: size specifier
 * Return: number of chars  to print
*/
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - print int
 * @types: lista of arguments
 * @buffer: buffer array to handle print
 * @flags:  calculates active flags
 * @width: get width.
 * @precision: precision specification
 * @size: size specifier
 * Return: number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int e = BUFF_SIZE - 2;
	int is_negative = 0;
	long int q = va_arg(types, long int);
	unsigned long int num;

	t = convert_size_number(t, size);

	if (t == 0)
		buffer[e--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)t;

	if (t < 0)
	{
		num = (unsigned long int)((-1) * t);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[e--] = (num % 10) + '0';
		num /= 10;
	}

	e++;

	return (write_number(is_negative, e, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - prints an unsigned number
 * @types: lista of arguments
 * @buffer: buffer array to handle print
 * @flags:  calculates active flags
 * @width: get width.
 * @precision: precision specification
 * @size: size specifier
 * Return: numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, g, h, sum;
	unsigned int x[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	g = 2147483648; /* (2 ^ 31) */
	x[0] = n / g;
	for (h = 1; h < 32; h++)
	{
		g /= 2;
		x[h] = (n / g) % 2;
	}
	for (h = 0, sum = 0, count = 0; h < 32; h++)
	{
		sum += x[h];
		if (sum || h == 31)
		{
			char z = '0' + x[h];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

