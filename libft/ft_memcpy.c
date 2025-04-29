/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:42:22 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:04:40 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i++ < n)
		((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char	*src = strdup("Tokyo");
// 	char	*dest1 = strdup("Hello World!");
// 	char	*dest2 = strdup("Hello World!");
// 	memcpy(dest1 + 6, src, 5);
// 	ft_memcpy(dest2 + 6, src, 5);
// 	printf("memcpy: %s\n", dest1);
// 	printf("ft_memcpy: %s\n", dest2);
// 	free(src);
// 	free(dest1);
// 	free(dest2);
// 	return (0);
// }
