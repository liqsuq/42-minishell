/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:52:21 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:28:00 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((unsigned char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "Hello, World!";
// 	printf("%s\n", ft_strchr(str, 'W'));
// 	printf("%s\n", ft_strchr(str, 'o'));
// 	printf("%s\n", ft_strchr(str, '\0'));
// 	printf("%s\n", ft_strchr(str, 'z'));
// 	return (0);
// }