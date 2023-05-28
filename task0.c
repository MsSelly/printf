#include "main.h"

/**
  * _printf - writes a function that produce oytput to a format
  * @format: string variables that contains all characters
  @ return: print char
  */

int _printf(const char *format, ...)
{
	int printed_chars;
	conver_t f_list[] = {
		{"o", print_octal},
		{"i", print_integer},
		{"c", print_char},
		{"%", print_percent},
		{"b", print_binary},
		{"x", print_hex},
		{"X", print_heX},
		{"u", unsigned_integer},
		{"r", print_reversed},
		{"R", rot13},
		{"d", print_integer},
		{"s", print_string},
		{NULL, NULL}
	};
	va_list arg_list;

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);
	/*Calling parser function*/
	printed_chars = parser(format, f_list, arg_list);
	va_end(arg_list);
	return (printed_chars);
}
