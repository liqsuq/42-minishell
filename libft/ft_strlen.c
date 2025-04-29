/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:44:57 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/30 18:07:24 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%zu", ft_strlen("1234"));
// 	printf("\n");
// 	printf("%zu", ft_strlen("12"));
// 	printf("\n");
// 	printf("%zu", ft_strlen(""));
// 	printf("\n");
// 		printf("%zu", ft_strlen(NULL));
// 	printf("\n");
// 	return (0);
// }
