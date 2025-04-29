/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:20:17 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:08:22 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (size <= dstlen)
		return (size + srclen);
	while (*dst != '\0')
		dst++;
	i = 0;
	while (*src != '\0' && i++ < (size - dstlen - 1))
		*dst++ = *src++;
	*dst = '\0';
	return (dstlen + srclen);
}

// /* cc -Wall -Wextra ft_strlcat.c -lbsd */
// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char	dest01_1[64] = "42";
// 	char	dest01_2[64] = "42";
// 	char	dest02_1[64] = "42";
// 	char	dest02_2[64] = "42";
// 	char	dest03_1[64] = "42";
// 	char	dest03_2[64] = "42";
// 	char	dest04_1[64] = "42";
// 	char	dest04_2[64] = "42";
// 	char	dest05_1[64] = "";
// 	char	dest05_2[64] = "";
// 	char	dest06_1[64] = "42";
// 	char	dest06_2[64] = "42";
// 	char	dest07_1[64] = "";
// 	char	dest07_2[64] = "";
// 	char	dest09[64] = "42";
// 	char	src[64] = "tokyo";
// 	int		result;
// 	printf("01 - strlcat(\"42\", \"tokyo\", 8):\n");
// 	result = strlcat(dest01_1, src, 8);
// 	printf("    %s: %d\n", dest01_1, result);
// 	result = ft_strlcat(dest01_2, src, 8);
// 	printf("    %s: %d\n", dest01_2, result);
// 	printf("02 - strlcat(\"42\", \"tokyo\", 2):\n");
// 	result = strlcat(dest02_1, src, 2);
// 	printf("    %s: %d\n", dest02_1, result);
// 	result = ft_strlcat(dest02_2, src, 2);
// 	printf("    %s: %d\n", dest02_2, result);
// 	printf("03 - strlcat(\"42\", \"tokyo\", 3):\n");
// 	result = strlcat(dest03_1, src, 3);
// 	printf("    %s: %d\n", dest03_1, result);
// 	result = ft_strlcat(dest03_2, src, 3);
// 	printf("    %s: %d\n", dest03_2, result);
// 	printf("04 - strlcat(\"42\", \"\", 8):\n");
// 	result = strlcat(dest04_1, "", 8);
// 	printf("    %s: %d\n", dest04_1, result);
// 	result = ft_strlcat(dest04_2, "", 8);
// 	printf("    %s: %d\n", dest04_2, result);
// 	printf("05 - strlcat(\"\", \"tokyo\", 8):\n");
// 	result = strlcat(dest05_1, src, 8);
// 	printf("    %s: %d\n", dest05_1, result);
// 	result = ft_strlcat(dest05_2, src, 8);
// 	printf("    %s: %d\n", dest05_2, result);
// 	printf("06 - strlcat(\"42\", \"tokyo\", 0):\n");
// 	result = strlcat(dest06_1, src, 0);
// 	printf("    %s: %d\n", dest06_1, result);
// 	result = ft_strlcat(dest06_2, src, 0);
// 	printf("    %s: %d\n", dest06_2, result);
// 	printf("07 - strlcat(\"\", \"tokyo\", 0):\n");
// 	result = strlcat(dest07_1, src, 0);
// 	printf("    %s: %d\n", dest07_1, result);
// 	result = ft_strlcat(dest07_2, src, 0);
// 	printf("    %s: %d\n", dest07_2, result);
// 	printf("08 - strlcat(NULL, \"tokyo\", 8):\n");
// 	result = ft_strlcat(NULL, src, 8);
// 	printf("    %s: %d\n", (char *)NULL, result);
// 	printf("09 - strlcat(\"42\", NULL, 8):\n");
// 	result = ft_strlcat(dest09, NULL, 8);
// 	printf("    %s: %d\n", dest09, result);
// 	printf("10 - strlcat(NULL, NULL, 8):\n");
// 	result = ft_strlcat(NULL, NULL, 8);
// 	printf("    %s: %d\n", (char *)NULL, result);
// 	return (0);
// }
