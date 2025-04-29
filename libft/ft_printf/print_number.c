/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:32:18 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/09 16:26:58 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ultohex(unsigned long n)
{
	int				len;
	unsigned long	tmpn;
	char			*str;
	const char		*base = "0123456789abcdef";

	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	tmpn = n;
	while (tmpn != 0)
	{
		len++;
		tmpn /= 16;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	while (n != 0)
	{
		str[len--] = base[n % 16];
		n /= 16;
	}
	return (str);
}

int	print_ptr(int fd, unsigned long ptr)
{
	char	*str;
	int		size;

	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	str = ultohex(ptr);
	if (str == NULL)
		return (-1);
	ft_putstr_fd("0x", fd);
	ft_putstr_fd(str, fd);
	size = ft_strlen(str) + 2;
	free(str);
	return (size);
}

static char	*uitobase(unsigned int n, char *base)
{
	int		len;
	long	tmpn;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	tmpn = n;
	while (tmpn != 0)
	{
		len++;
		tmpn /= ft_strlen(base);
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	while (n != 0)
	{
		str[len--] = base[n % ft_strlen(base)];
		n /= ft_strlen(base);
	}
	return (str);
}

int	print_int(int fd, int n, int is_unsigned, char *base)
{
	char	*str;
	int		size;

	if (is_unsigned)
		str = uitobase(n, base);
	else
		str = ft_itoa(n);
	if (str == NULL)
		return (-1);
	ft_putstr_fd(str, fd);
	size = ft_strlen(str);
	free(str);
	return (size);
}
