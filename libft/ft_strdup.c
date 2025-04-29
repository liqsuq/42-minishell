/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:34:18 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 20:38:10 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(s);
	ptr = malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, size + 1);
	return (ptr);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *str = "Hello, World!";
// 	char *dup = ft_strdup(str);
// 	printf("%s\n", dup);
// 	free(dup);
// 	return (0);
// }
