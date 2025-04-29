/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:30:01 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/16 17:33:54 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb != 0 && size != 0)
		if ((nmemb > SIZE_MAX / size))
			return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char *s1 = calloc(5, 5);
// 	char *s2 = ft_calloc(5, 5);
// 	char *s3 = calloc(-ULONG_MAX + 4, 1);
// 	char *s4 = ft_calloc(-ULONG_MAX + 4, 1);
// 	char *s5 = calloc(0, 5);
// 	char *s6 = ft_calloc(0, 5);
// 	for (int i = 0; i < 25; i++)
// 		printf("%d ", s1[i]);
// 	printf("\n");
// 	for (int i = 0; i < 25 ; i++)
// 		printf("%d ", s2[i]);
// 	printf("\n");
// 	for (int i = 0; i < 5; i++)
// 		printf("%d ", s3[i]);
// 	printf("\n");
// 	for (int i = 0; i < 5; i++)
// 		printf("%d ", s4[i]);
// 	printf("\n");
// 	printf("%p\n", s5);
// 	printf("%p\n", s6);
// 	free(s1);
// 	free(s2);
// 	free(s3);
// 	free(s4);
// 	free(s5);
// 	free(s6);
// 	return (0);
// }
