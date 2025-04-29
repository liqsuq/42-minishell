/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:40:31 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 16:50:31 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("ft_toupper('A'): %c\n", ft_toupper('A'));
// 	printf("ft_toupper('Z'): %c\n", ft_toupper('Z'));
// 	printf("ft_toupper('a'): %c\n", ft_toupper('a'));
// 	printf("ft_toupper('z'): %c\n", ft_toupper('z'));
// 	printf("ft_toupper('0'): %c\n", ft_toupper('0'));
// 	printf("ft_toupper('9'): %c\n", ft_toupper('9'));
// 	printf("ft_toupper(' '): %c\n", ft_toupper(' '));
// 	printf("ft_toupper('!'): %c\n", ft_toupper('!'));
// 	printf("ft_toupper('['): %c\n", ft_toupper('['));
// 	printf("ft_toupper('`'): %c\n", ft_toupper('`'));
// 	printf("ft_toupper('{'): %c\n", ft_toupper('{'));
// 	return (0);
// }
