#ifdef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>


int _printf(const char *format, ...);
int _putchar(char c);

//helper functions for handling format specifiers
void print_char(char c, int *count);
void print_string(const char *str, int *count);
void print_integer(int n, int *count);
void print_unsigned(unsigned int n, int *count);


#endif
