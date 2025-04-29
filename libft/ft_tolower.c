/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:40:31 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 16:49:50 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("ft_tolower('A'): %c\n", ft_tolower('A'));
// 	printf("ft_tolower('Z'): %c\n", ft_tolower('Z'));
// 	printf("ft_tolower('a'): %c\n", ft_tolower('a'));
// 	printf("ft_tolower('z'): %c\n", ft_tolower('z'));
// 	printf("ft_tolower('0'): %c\n", ft_tolower('0'));
// 	printf("ft_tolower('9'): %c\n", ft_tolower('9'));
// 	printf("ft_tolower(' '): %c\n", ft_tolower(' '));
// 	printf("ft_tolower('!'): %c\n", ft_tolower('!'));
// 	printf("ft_tolower('['): %c\n", ft_tolower('['));
// 	printf("ft_tolower('`'): %c\n", ft_tolower('`'));
// 	printf("ft_tolower('{'): %c\n", ft_tolower('{'));
// 	return (0);
// }
