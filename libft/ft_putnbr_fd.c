/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:46:53 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 18:04:13 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

// #include <stdio.h>
// int main(void)
// {
// 	ft_putnbr_fd(42, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-42, 1);
// 	printf("\n");
// 	ft_putnbr_fd(0, 1);
// 	printf("\n");
// 	ft_putnbr_fd(2147483647, 1);
// 	printf("\n");
// 	ft_putnbr_fd(-2147483648, 1);
// 	printf("\n");
// 	return (0);
// }
