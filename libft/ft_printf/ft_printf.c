/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:12:47 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 13:25:42 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	select_format(int fd, const char *format, va_list *argp)
{
	if (format[1] == 'c')
		return (print_char(fd, va_arg(*argp, int)));
	if (format[1] == 's')
		return (print_str(fd, va_arg(*argp, char *)));
	if (format[1] == 'p')
		return (print_ptr(fd, va_arg(*argp, unsigned long)));
	if (format[1] == 'd' || format[1] == 'i')
		return (print_int(fd, va_arg(*argp, int), 0, DEC));
	if (format[1] == 'u')
		return (print_int(fd, va_arg(*argp, unsigned int), 1, DEC));
	if (format[1] == 'x')
		return (print_int(fd, va_arg(*argp, unsigned int), 1, HEX_LO));
	if (format[1] == 'X')
		return (print_int(fd, va_arg(*argp, unsigned int), 1, HEX_UP));
	if (format[1] == '%')
		return (print_char(fd, '%'));
	return (-1);
}

int	ft_vdprintf(int fd, const char *format, va_list argp)
{
	int	size;
	int	tmp;

	size = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			tmp = select_format(fd, format, &argp);
			if (tmp == -1)
				return (-1);
			format += 2;
		}
		else
		{
			tmp = print_raw(fd, format);
			if (tmp == -1)
				return (-1);
			format += tmp;
		}
		size += tmp;
	}
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	argp;
	int		size;

	if (format == NULL)
		return (-1);
	va_start(argp, format);
	size = ft_vdprintf(1, format, argp);
	va_end(argp);
	return (size);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	argp;
	int		size;

	if (format == NULL)
		return (-1);
	va_start(argp, format);
	size = ft_vdprintf(fd, format, argp);
	va_end(argp);
	return (size);
}
