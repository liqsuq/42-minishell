/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:59:16 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/11 10:55:00 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (f != NULL)
			ptr[i] = f(i, s[i]);
		else
			ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

// #include <stdio.h>
// char to_upper(unsigned int i, char c)
// {
// 	(void)i;
// 	return (ft_toupper(c));
// }
// int main(void)
// {
// 	char	*str = "Hello, World!";
// 	char	*new = ft_strmapi(str, to_upper);
// 	printf("%s\n", new);
// 	free(new);
// 	return (0);
// }
