/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:32:54 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/16 17:29:19 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	start;
	size_t	end;

	if (s == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s[start] != '\0')
	{
		if (ft_strchr(set, s[start]) == NULL)
			break ;
		start++;
	}
	end = ft_strlen(s);
	while (end-- > 0)
		if (ft_strchr(set, s[end]) == NULL)
			break ;
	return (ft_substr(s, start, end - start + 1));
}

// #include <stdio.h>
// int main(void)
// {
// 	char	*ptr;
// 	ptr = ft_strtrim("Hello, World!", "Hell!");
// 	if (!ptr)
// 		return (1);
// 	printf("%s\n", ptr);
// 	free(ptr);
// 	return (0);
// }