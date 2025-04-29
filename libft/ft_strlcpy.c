/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:39:25 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:13:37 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	i = 0;
	while (*src != '\0' && i++ < (size - 1))
		*dst++ = *src++;
	*dst = '\0';
	return (srclen);
}

// /* cc -Wall -Wextra ft_strlcpy.c -lbsd */
// #include <stdio.h>
// #include <string.h>
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char	dest1[8] = "???????";
// 	char	dest2[8] = "???????";
// 	char	src[] = "42tokyo";
// 	int		result;
// 	printf("01 - strlcpy(dest, \"42tokyo\", 0):\n");
// 	result = strlcpy(dest1, src, 0);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, 0);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("02 - strlcpy(dest, \"42tokyo\", 1):\n");
// 	result = strlcpy(dest1, src, 1);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, 1);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("03 - strlcpy(dest, \"42tokyo\", 2):\n");
// 	result = strlcpy(dest1, src, 2);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, 2);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("04 - strlcpy(dest, \"42tokyo\", 7):\n");
// 	result = strlcpy(dest1, src, 7);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, 7);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("05 - strlcpy(dest, \"42tokyo\", 64):\n");
// 	result = strlcpy(dest1, src, 64);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, 64);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("06 - strlcpy(dest, \"42tokyo\", -1):\n");
// 	result = strlcpy(dest1, src, -1);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, src, -1);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("07 - strlcpy(dest, \"\", 7):\n");
// 	result = strlcpy(dest1, "", 7);
// 	printf("    %s: %d\n", dest1, result);
// 	result = ft_strlcpy(dest2, "", 7);
// 	printf("    %s: %d\n", dest2, result);
// 	printf("08 - strlcpy(NULL, \"42tokyo\", 7):\n");
// 	result = ft_strlcpy(NULL, src, 7);
// 	printf("    %s: %d\n", (char *)NULL, result);
// 	printf("09 - strlcpy(dest, NULL, 7):\n");
// 	result = ft_strlcpy(dest1, NULL, 7);
// 	printf("    %s: %d\n", dest1, result);
// 	printf("10 - strlcpy(NULL, NULL, 7):\n");
// 	result = ft_strlcpy(NULL, NULL, 7);
// 	printf("    %s: %d\n", (char *)NULL, result);
// 	return (0);
// }
