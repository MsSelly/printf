#include <unistd.h>

/**
 * _putchar - writes c char in stdout
 * @c: the char to print
 * Return: success 1
 * On error, return -1 and set error appropriately
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
