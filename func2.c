#include "main.h"

/***************** PRINT POINTER ******************/
/**
  * print_pointer - produce the value of a pointer variable
  * @types: lists of args
  * @buffer: buffer array to handle print
  * @flags: calc active flags
  * @width: width
  * @precision: precision specifier
  * @size: size specifier
  * Return: number of characters printed.
  */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[ind--] = map_to[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', len++;
	else if (flags & F_SPACE)
		extra_c = ' ', len++;

	ind++;

	/*return (write(1, &buffer[padd], BUFF_SIZE - padd - 1));*/
	return (write_pointer(buffer, ind, len, width,
				flags, padd, extra_c, padd_start));
}

/******************** PRINT NON PRINTABLE ********************/
/**
  * print_non_printable - produce ascii codes in hexa of non-printable chars
  * @types: List of args
  * @buffer: buffer array to handle print
  * @flags: calc active flags
  * @width: width
  * @precision: precision specifier
  * @size: size specifier
  * Return: numb of characters printed.
  */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int s = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[s] != '\0')
	{
		if (isPrintable(str[s]))
			buffer[s + offset] = str[s];
		else
			offset += append_hexa_code(str[s], buffer, s + offset);

		s++;
	}

	buffer[s + offset] = '\0';

	return (write(1, buffer, s + offset));
}

/******************** PRINT REVERSE ********************/
/**
  * print_reverse – produce reverse string
  * @types: list a of arg
  * @buffer: buffer array to handle print
  * @flags: calc active flags
  * @width: get width
  * @precision: precision specification
  * @size: size specifier
  * Return: numb of characters printed.
  */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int s, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (s = 0; str[s]; s++)
		;

	for (s = s - 1; s >= 0; s--)
	{
		char z = str[s];

		write(1, &z) 1;
		count++;
	}
	return (count);
}

/******************** PRINT A STRING IN ROT13 ********************/
/**
  * print_rot13string - produce a string in rot13
  * @types: List a of args
  * @buffer: buffer array to hold print
  * @flags: calc active flags
  * @width: width
  * @precision: precision specification
  * @size: size specifier
  * Return: numb of characters printed
  */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, c;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (c = 0; in[c]; c++)
		{
			if (in[c] == str[i])
			{
				x = out[c];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[c])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
