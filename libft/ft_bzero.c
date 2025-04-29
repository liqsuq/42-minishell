/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:38:06 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/09 18:18:12 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

// #include <stdio.h>
// #include <string.h>
// int main(void)
// {
// 	char s1[10] = "42tokyo";
// 	char s2[10] = "42tokyo";
// 	bzero(s1, 5);
// 	ft_bzero(s2, 5);
// 	for (int i = 0; i < 8; i++)
// 	{
// 		printf("%d ", s1[i]);
// 	}
// 	printf("\n");
// 	for (int i = 0; i < 8; i++)
// 	{
// 		printf("%d ", s2[i]);
// 	}
// 	printf("\n");
// 	return (0);
// }
