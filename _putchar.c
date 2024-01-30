#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: on success, return the number of characters written. on error, -1.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - write a character to stdout
 * @c: the character to print
 *
 * Return: return the number of characters written
 */
int _puts(char *str)
{
	int count = 0;

	while (*str)
	{
		count += _putchar(*str);
		str++;
	}

	return count;
}
