#include "main.h"

/**
 * is_Printable - evaluates if a char is printable
 * @c: char to be evaluated.
 *
 * Return: 1 if c is printable, 0 if otherwise
 */
int is_Printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - append ascci in hexadecimal code to buffer
 * @buffer: array of chars.
 * @ind: index at where to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: always 3
 */

int append_hexa_code(char ascii_code, char buffer[], int ind)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[ind++] = '\\';
	buffer[ind++] = 'x';

	buffer[ind++] = map_to[ascii_code / 16];
	buffer[ind] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if a char is a digit
 * @c: char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @numb: numb to be casted.
 * @size: numb indicating type to be casted.
 *
 * Return: casted value of numb
 */
long int convert_size_number(long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((short)numb);

	return ((int)numb);
}

/**
 * convert_size_unsgnd - casts a number to the specified size
 * @numb: numb to be casted
 * @size: numb indicating type to be casted
 *
 * Return: casted value of numb
 */
long int convert_size_unsgnd(unsigned long int numb, int size)
{
	if (size == S_LONG)
		return (numb);
	else if (size == S_SHORT)
		return ((unsigned short)numb);

	return ((unsigned int)numb);
}
