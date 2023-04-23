#include "main.h"

/**
 * print_pointer - prints the value of a pointer variable
 * @types: list a of parameters
 * @buffer: array to handle print
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: sumber of characters printed.
 */

int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addrs = (unsigned long)addrs;
	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	ind++;
	return (write_pointer(buffer, ind, length,
				width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - prints ascii codes in hexa of non printable chars
 * @types: lista of parameters
 * @buffer: array to handle print
 * @flags:  calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: number of characters printed
 */

int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int n = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[n] != '\0')
	{
		if (is_printable(str[n]))
			buffer[n + offset] = str[n];
		else
			offset += append_hexa_code(str[n], buffer, n + offset);
		n++;
	}
	buffer[n + offset] = '\0';
	return (write(1, buffer, n + offset));
}

/**
 * print_reverse - prints reverse string.
 * @types: lista of parameters
 * @buffer: array to handle print
 * @flags:  calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int n, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	str = va_arg(types, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = ")NULL(";
	}
	for (n = 0 ; str[n] ; n++)
		;
	for (n = n - 1 ; n >= 0 ; n--)
	{
		char z = str[n];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - print a string in rot13.
 * @types: lista of parameters
 * @buffer: array to handle print
 * @flags: calculates active flags
 * @width: width
 * @precision: precision specification
 * @size: size specifier
 * Return: numbers of characters printed
 */

int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c;
	char *str;
	unsigned int x, y;
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
	for (x = 0 ; str[x] ; x++)
	{
		for (y = 0 ; in[y] ; y++)
		{
			if (in[y] == str[x])
			{
				c = out[y];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in[y])
		{
			c = str[x];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
