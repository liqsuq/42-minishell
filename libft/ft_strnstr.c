/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:49:46 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:36:47 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	printf("strnstr(\"42tokyo\", \"42\", 7) ... \n");
// 	printf("    %s\n", (char *)strnstr("42tokyo", "42", 7));
// 	printf("    %s\n", ft_strnstr("42tokyo", "42", 7));
// 	printf("strnstr(\"42tokyo\", \"tokyo\", 7) ... \n");
// 	printf("    %s\n", (char *)strnstr("42tokyo", "tokyo", 7));
// 	printf("    %s\n", ft_strnstr("42tokyo", "tokyo", 7));
// 	printf("strnstr(\"42tokyo\", \"tokyo\", 3) ... \n");
// 	printf("    %s\n", (char *)strnstr("42tokyo", "tokyo", 3));	
// 	printf("    %s\n", ft_strnstr("42tokyo", "tokyo", 3));
// 	printf("strnstr(\"42tokyo\", \"\", 7) ... \n");
// 	printf("    %s\n", (char *)strnstr("42tokyo", "", 7));
// 	printf("    %s\n", ft_strnstr("42tokyo", "", 7));
// 	printf("strnstr(\"42tokyo\", \"tokyo\", 0) ... \n");
// 	printf("    %s\n", (char *)strnstr("42tokyo", "tokyo", 0));
// 	printf("    %s\n", ft_strnstr("42tokyo", "tokyo", 0));
// 	return (0);
// }
