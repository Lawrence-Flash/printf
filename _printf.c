#include "main.h"
/**
 * _printf - printf function with limited functionality.
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
	int co = 0;i
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
					co += _putchar(va_arg(args, int));
					break;
				}
				case 's':
				{
					co += _puts(va_arg(args, char *), 4096);
				}
				case '%':
				{
					co += _putchar('%');
					break;
				}
				default:
				{
					co += _putchar('%');
					co += _putchar(format[i]);
					break;
				
			}
		}
	}

	va_end(args);
	return co;
}
