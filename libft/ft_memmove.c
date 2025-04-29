/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:47:37 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:06:07 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest > src)
		while (n-- > 0)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char	*src = strdup("Tokyo");
// 	char	*dest1 = strdup("Hello World!");
// 	char	*dest2 = strdup("Hello World!");
// 	ft_memmove(dest1 + 6, src, 5);
// 	memmove(dest2 + 6, src, 5);
// 	printf("ft_memmove: %s\n", dest1);
// 	printf("memmove: %s\n", dest2);
// 	free(src);
// 	free(dest1);
// 	free(dest2);
// 	printf("\n");
// 	dest1 = strdup("Hello World!");
// 	dest2 = strdup("Hello World!");
// 	ft_memmove(dest1 + 6, dest1, 5);
// 	memmove(dest2 + 6, dest2, 5);
// 	printf("ft_memmove: %s\n", dest1);
// 	printf("memmove: %s\n", dest2);
// 	free(dest1);
// 	free(dest2);
// 	printf("\n");
// 	dest1 = strdup("Hello World!");
// 	dest2 = strdup("Hello World!");
// 	ft_memmove(dest1, dest1 + 6, 5);
// 	memmove(dest2, dest2 + 6, 5);
// 	printf("ft_memmove: %s\n", dest1);
// 	printf("memmove: %s\n", dest2);
// 	free(dest1);
// 	free(dest2);
// 	return (0);
// }
