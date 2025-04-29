/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:42:15 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/16 16:59:27 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}

// #include <stdio.h>
// int main(void)
// {
// 	char	*str = "Hello, World!";
// 	char	*new1 = ft_substr(str, 0, 14);
// 	char	*new2 = ft_substr(str, 0, 5);	
// 	char	*new3 = ft_substr(str, 7, 6);
// 	char	*new4 = ft_substr(str, 0, 1024);
// 	char	*new5 = ft_substr(str, 1024, 14);
// 	printf("%s\n", new1);
// 	printf("%s\n", new2);
// 	printf("%s\n", new3);
// 	printf("%s\n", new4);
// 	printf("%s\n", new5);
// 	free(new1);
// 	free(new2);
// 	free(new3);
// 	free(new4);
// 	free(new5);
// 	return (0);
// }
