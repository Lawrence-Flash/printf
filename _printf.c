#include "main.h"
#include <stdio.h>

/**
 * _printf - custom printf function with limited functionality.
 * @format: Format string with directives
 *
 * Description: this function produces output according to a format string
 * It handles the following conversion specifiers: c, s, %.
 * It writes the output to stdout, the standard ouput stream. The function
 * retruns the number of characters printted (excluding the null byte used
 * to end output to strings).
 *
 * Return: The number of characters printed (excluding the null byte).
 */

int _printf(const char *format, ...)
{
	int co = 0;
	va_list args;
	int i;

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			co++;
		}
		else
		{
			i++;
			switch (format[i])
			{
				case 'c':
				{
					char c = va_arg(args, int);
					_putchar(c);
					co++;
					break;
				}
				case 's':
				{
					char *str = va_arg(args, char *);
					while (*str)
					{
						_putchar(*str++);
						co++;
					}
					break;
				}
				case '%':
				{
					_putchar('%');
					co++;
					break;
				}
				default:
				{
					_putchar('%');
					_putchar(format[i]);
					co += 2;
					break;
				}
			}
		}
	}

	va_end(args);
	return co;
}
