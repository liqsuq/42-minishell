/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:25:20 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/10 14:30:12 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i++ < len)
		*ptr++ = c;
	return (b);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "????????????";
// 	ft_memset(str + 4, '!', 4);
// 	printf("%s\n", str);
// 	return (0);
// }