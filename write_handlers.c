#include "main.h"

/****************** WRITE HANDLER ********************/
/**
  * handle_write_char - outputs a string
  * @c: char to be output
  * @buffer: buffer array to handle output
  * @flags: active flags
  * @width: width
  * @precision: precision specifier
  * @size: size specifier
  * Return: numb of characters output.
  */

int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{ /* char is stored at left and padding at buffer's right */
	int g = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[g++] = c;
	buffer[g] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (g = 0; g < width - 1; g++)
			buffer[BUFF_SIZE - g - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - g - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - g - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/******************* WRITE NUMB ********************/
/**
  * write_number - outputs a numb
  * @is_negative: list of arg
  * @ind: index
  * @buffer: buffer array to handle output
  * @flags: active flags
  * @width: width
  * @size: size specifier
  * @precision: precision
  * Return: numb of characters output.
  */

int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
  * write_numb - writes a numb using a buffer
  * @ind: index at which the numb starts
  * @buffer: buffer
  * @flags: active flags
  * @width: width
  * @prec: precision
  * @length: numb length
  * @padd: padding char
  * @extra_c: extra char
  * Return: numb of output characters.
  */
int write_num(int ind, char buffer[], int flags, int width,
		int prec, int length, char padd, char extra_c)
{
	int g, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (g = 1; g < width - length + 1; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], g - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], g - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
  * write_unsigned - write an unsigned numb
  * @is_negative: numb indicating if numb is negative
  * @ind: index at which numb starts
  * @buffer: array of characters
  * @flags: active flags
  * @width: width
  * @precision: precision
  * @size: size
  * Return: numb of output chars.
  */

int write_unsgnd(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1,g = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (g = 0; g < width - length; g++)
			buffer[g] = padd;

		buffer[g] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], g));
		}
		else
		{
			return (write(1, &buffer[0], g) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/****************** WRITE POINTER ********************/
/**
  * write_pointer - write out memory addr
  * @buffer: arrays of characters
  * @ind: index at which numb starts in buffer
  * @length: length of numb
  * @width: width
  * @flags: active flags
  * @padd: character representing padding
  * @extra_c: extra char
  * @padd_start: index at which padding should start
  * Return: numb of characters output.
  */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int g;

	if (width > length)
	{
		for (g = 3; g < width - length + 3; g++)
			buffer[g] = padd;
		buffer[g] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], g - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], g - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], g - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
