/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:31:35 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/09 16:26:17 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int fd, int c)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	print_str(int fd, char *str)
{
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, fd);
	return (ft_strlen(str));
}

int	print_raw(int fd, const char *format)
{
	char	*str;
	int		i;

	i = 0;
	while (format[i] != '\0' && format[i] != '%')
		i++;
	str = ft_substr(format, 0, i);
	if (str == NULL)
		return (-1);
	ft_putstr_fd(str, fd);
	free(str);
	return (i);
}
