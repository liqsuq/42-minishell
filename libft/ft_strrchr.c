/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:52:21 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:28:00 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	if ((unsigned char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			ret = ((char *)s);
		s++;
	}
	return (ret);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "Hello, World!";
// 	printf("%s\n", ft_strrchr(str, 'W'));
// 	printf("%s\n", ft_strrchr(str, 'o'));
// 	printf("%s\n", ft_strrchr(str, '\0'));
// 	printf("%s\n", ft_strrchr(str, 'z'));
// 	return (0);
// }