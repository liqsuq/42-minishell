/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:52:21 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 13:40:16 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char str[] = "Hello World!";
// 	printf("memchr: %s\n", (char *)memchr(str, 'W', strlen(str)));
// 	printf("ft_memchr: %s\n", (char *)ft_memchr(str, 'W', ft_strlen(str)));
// 	printf("\n");
// 	printf("memchr: %s\n", (char *)memchr(str, 'W'+256, strlen(str)));
// 	printf("ft_memchr: %s\n", (char *)ft_memchr(str, 'W'+256, ft_strlen(str)));
// 	printf("\n");
// 	printf("memchr: %s\n", (char *)memchr(str, 'W', 3));
// 	printf("ft_memchr: %s\n", (char *)ft_memchr(str, 'W', 3));
// 	printf("\n");
// 	printf("memchr: %s\n", (char *)memchr(str, '4', strlen(str)));
// 	printf("ft_memchr: %s\n", (char *)ft_memchr(str, '4', ft_strlen(str)));
// 	return (0);
// }