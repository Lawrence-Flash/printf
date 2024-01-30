#include "main.h"

/**
 * _printf - Custoome printf function
 * @format: Format string with format specifiers
 *
 * Return: NUmber of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char buffer[1024];
	char *str_arg;
	int int_arg;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;

			count += handle_specifier(*format, args, buffer, &str_arg, &int_arg);

		}
		else
		{
			buffer[count++] = *format;
		}

		if (count == 1023)
		{
			write(1, buffer, count);
			count = 0;
		}

		format++;
	}

	write(1, buffer, count);
	va_end(args);

	return count;
}

/**
 * handle_non_printable_str - Handle the 'S' specifier in _printf
 * @args: String argument
 * @buffer: Local buffer to store the ouput
 *
 * Return: Number of characters printed for the specifier
 */
int handle_non_printable_str(const char *arg, char *buffer)
{
	int count = 0;
	char hex[3];
	int i = 0;

	while (arg[i] != '\0')
	{
		if (arg[i] < 32 || arg[i] >= 127)
		{
			buffer[count++] = '\\';
			buffer[count++] = 'x';
			
			sprintf(hex, "%02X", (unsigned char)arg[i]);
			count += handle_str(hex, buffer);
		}
		else
		{
			buffer[count++] = arg[i];
		}
		if (count == 1023)
		{
			write(1, buffer, count);
			count = 0;
		}
		
		
		i++;
	}
	return count;
}

/**
 * handle_specifier - handle format specifier in _printf
 * @specifier: format specifier character
 * @args: variable arguments list
 * @buffer: local buffer to store the output
 * @str-arg: pointer to a string argument (for S Specifier)
 * @int_arg: pointer to an integer argument (for some specifiers)
 *
 * Return: Number of characters printed for the specifier
 */
int handle_specifier(char specifier, va_list args, char *buffer, char **str_arg, int *int_arg)
{
	int count = 0;

	switch (specifier)
	{
		case 'c':
			count += handle_char(va-arg(args, int), buffer);
			break;
		case 's':
			*str_arg = va_arg(args, char *);
			count += handle_str(*str_arg, buffer);
			break;
		case '%':
			count += handle_percent(buffer);
			break;
		case 'd':
		case 'i':
			*int_arg = va_arg(args, int);
			count += handle_int(*int_arg, buffer);
			break;
		case 'b':
			*int_arg = va_arg(args, unsigned int);
			count += handle_binary(*int_arg, buffer);
			break;
		case 'S':
			*str_arg = va_arg(args, unsigned int);
			count += handle_non_printable_str(*str_arg, buffer);
			break;
		default:
			break;
	}

	return count;
}

/**
 * handle_char - Handle the 'c' specifier in _printf
 * @arg: Character argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the specifier
 */
int handle_char(int arg, char *buffer)
{
	buffer[0] = arg;
	return 1;
}

/**
 * handle_str - Handle the 's' specifier in _printf
 * @arg: String argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the specifier
 */
int handle_str(const char *arg, char *buffer)
{
	int count = 0;
	int i = 0;
	
	while (arg[i] != '\0')
	{
		buffer[count++] = arg[i++];
		if (count == 1023)
		{
			write(1, buffer, count);
			count = 0;
		}
	}

	return count;
}

/**
 * handle_percent - Handle the '%' specifier in _printf
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the specifier
 */
int handle_percent(char *buffer)
{
	buffer[0] = '%';
	return 1;
}

/**
 * handle_int - Handle the 'd' and 'i' specifier in _printf
 * @arg: Integer argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the spcifier
 */
int handle_int(int arg, char *buffer)
{
	int count;

	count = sprintf(buffer, "%d", arg);
	return count;
}

/**
 * handle_custom_specifier - Handle custom specifier in _printf
 * @specifier: Custom specifier character
 * @args: Variable arguments list
 * @buffer: local buffer to store the output
 * @str_arg: Pointer to a string argument (for S specifier)
 *
 * Return: Number of characters printed for the specifier
 */
int handle_custom_specifier(char specifier, va_list args, char *buffer, char **str_arg)
{
	int count = 0;

	switch (specifier)
	{
		case 'b':
			count += handle_binary(va_arg(args, unsigned int), buffer);
			break;
		case 'S':
			*str-arg = va_arg(args, char *);
			count += handle_non_printable_str(*str_arg, buffer);
			break;
		case 'r':
			*str_arg = va_arg(args, char *);
			count += handle_reversed_str(*str_arg, buffer);
			break;
		case 'R':
			*str_arg = va_arg(args, char *);
			count += handle_rot13_str(*str_arg, buffer);
			break;
		default:
			break;
	}

	return count;
}

/**
 * handle_binary - handle the 'b' specifier in the _printf
 * @arg: Unsigned integer argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the specifier
 */
int handle_binary(unsigned int arg, char *buffer)
{
	int num_bits = 0;
	unsigned int temp = arg;
	int i;

	if (arg == 0)
	{
		buffer[0] = '0';
		return 1;
	}

	while (temp > 0)
	{
		temp >>= 1;
		num_bits++;
	}
	

	for (i = num_bits - 1; i >= 0; i--)
	{
		buffer[num_bits - 1 - i] = ((arg >> i) & 1) ? '1' : '0';
	}

	return num_bits;
}

/**
 * handle_reversed_str - Handle the 'r' specifier in _printf
 * @arg: String argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed to the specifier
 */
int handle_reversed_str(const char *arg, char *buffer)
{
	int length = 0;
	int i, j;
	char temp;
	
	if (arg == NULL)
		return 0;


	while (arg[length] != '\0')
	{
		length++;
	}
	
	for (i = 0, j = length - 1; i < j; i++, j--)
	{
		temp = arg[i];
		buffer[i] = arg[j];
		buffer[j] = temp;
	}

	return length;
}

/**
 * handle_rot13_str - Handle the 'R' specifier in _printf
 * @arg: String argument
 * @buffer: Local buffer to store the output
 *
 * Return: Number of characters printed for the specifier
 */

int handle_rot13_str(const char *arg, char *buffer)
{
	int count = 0;
	char current_char;
	char base;


	if (arg == NULL)
		return 0;

	while(arg[count] != '\0')
	{
		current_char = arg[count];

		if ((current_char >= 'A' && current_char <= 'Z') || (current_char >= 'a' && current_char <= 'z'))
		{
			base = (current_char >= 'A' && current_char <= 'Z') ? 'A' : 'a';
			buffer[count] = (current_char - base + 13) % 26 + base;
		}
		else
		{
			buffer[count] = current_char;
		}

		count++;
	}

	return count;
}

