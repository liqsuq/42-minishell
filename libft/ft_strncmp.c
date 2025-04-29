/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:59:20 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:30:36 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && (i < (n - 1)))
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff > 0)
			return (1);
		if (diff < 0)
			return (-1);
		i++;
	}
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (diff > 0)
		return (1);
	if (diff < 0)
		return (-1);
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char s1[] = "A";
// 	char s2[] = "A";
// 	s2[0] = (char)('A' + 256);
// 	printf("ft_strncmp(ABC, ABC, 3): %d\n", ft_strncmp("ABC", "ABC", 3));
// 	printf("ft_strncmp(ABC, AB , 3): %d\n", ft_strncmp("ABC", "AB", 3));
// 	printf("ft_strncmp(ABC, AB , 2): %d\n", ft_strncmp("ABC", "AB", 2));
// 	printf("ft_strncmp(ABA, ABZ, 3): %d\n", ft_strncmp("ABA", "ABZ", 3));
// 	printf("ft_strncmp(ABJ, ABC, 3): %d\n", ft_strncmp("ABJ", "ABC", 3));
// 	printf("ft_strncmp(ABJ, ABC, 0): %d\n", ft_strncmp("ABJ", "ABC", 0));
// 	printf("ft_strncmp(A, A + 256, 1): %d\n", ft_strncmp(s1, s2, 1));
// 	printf("\n");
// 	printf("strncmp(ABC, ABC, 3): %d\n", strncmp("ABC", "ABC", 3));
// 	printf("strncmp(ABC, AB , 3): %d\n", strncmp("ABC", "AB", 3));
// 	printf("strncmp(ABC, AB , 2): %d\n", strncmp("ABC", "AB", 2));
// 	printf("strncmp(ABA, ABZ, 3): %d\n", strncmp("ABA", "ABZ", 3));
// 	printf("strncmp(ABJ, ABC, 3): %d\n", strncmp("ABJ", "ABC", 3));
// 	printf("strncmp(ABJ, ABC, 0): %d\n", strncmp("ABJ", "ABC", 0));
// 	printf("ft_strncmp(A, A + 256, 1): %d\n", ft_strncmp(s1, s2, 1));
// 	return (0);
// }
