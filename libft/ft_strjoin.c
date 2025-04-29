/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:17:21 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 15:14:45 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*cur;

	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	cur = ptr;
	while (s1 != NULL && *s1 != '\0')
		*cur++ = *s1++;
	while (s2 != NULL && *s2 != '\0')
		*cur++ = *s2++;
	*cur = '\0';
	return (ptr);
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	char	*ptr;
// 	ptr = ft_strjoin("42", "tokyo");
// 	if (!ptr)
// 		return (1);
// 	printf("%s\n", ptr);
// 	free(ptr);
// 	ptr = ft_strjoin(NULL, "tokyo");
// 	if (!ptr)
// 		return (1);
// 	printf("%s\n", ptr);
// 	free(ptr);
// 	ptr = ft_strjoin("42", NULL);
// 	if (!ptr)
// 		return (1);
// 	printf("%s\n", ptr);
// 	free(ptr);
// 	ptr = ft_strjoin(NULL, NULL);
// 	if (!ptr)
// 		return (1);
// 	printf("%s\n", ptr);
// 	return (0);
// }
