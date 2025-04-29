/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:59:20 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:34:26 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;

	i = 0;
	while (i < n)
	{
		diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
		if (diff > 0)
			return (1);
		if (diff < 0)
			return (-1);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char s1[] = "A";
// 	char s2[] = "A";
// 	s2[0] = (char)('A' + 256);
// 	printf("ft_strncmp(ABC, ABC, 3): %d\n", ft_memcmp("ABC", "ABC", 3));
// 	printf("ft_strncmp(ABC, AB , 3): %d\n", ft_memcmp("ABC", "AB", 3));
// 	printf("ft_strncmp(ABC, AB , 2): %d\n", ft_memcmp("ABC", "AB", 2));
// 	printf("ft_strncmp(ABA, ABZ, 3): %d\n", ft_memcmp("ABA", "ABZ", 3));
// 	printf("ft_strncmp(ABJ, ABC, 3): %d\n", ft_memcmp("ABJ", "ABC", 3));
// 	printf("ft_strncmp(ABJ, ABC, 0): %d\n", ft_memcmp("ABJ", "ABC", 0));
// 	printf("ft_strncmp(A, A + 256, 1): %d\n", ft_memcmp(s1, s2, 1));
// 	printf("\n");
// 	printf("strncmp(ABC, ABC, 3): %d\n", memcmp("ABC", "ABC", 3));
// 	printf("strncmp(ABC, AB , 3): %d\n", memcmp("ABC", "AB", 3));
// 	printf("strncmp(ABC, AB , 2): %d\n", memcmp("ABC", "AB", 2));
// 	printf("strncmp(ABA, ABZ, 3): %d\n", memcmp("ABA", "ABZ", 3));
// 	printf("strncmp(ABJ, ABC, 3): %d\n", memcmp("ABJ", "ABC", 3));
// 	printf("strncmp(ABJ, ABC, 0): %d\n", memcmp("ABJ", "ABC", 0));
// 	printf("ft_strncmp(A, A + 256, 1): %d\n", ft_memcmp(s1, s2, 1));
// 	return (0);
// }
