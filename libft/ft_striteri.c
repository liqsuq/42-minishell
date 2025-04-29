/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:21:32 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/11 10:54:57 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == NULL)
		return ;
	i = 0;
	while (*s != '\0' && f != NULL)
		f(i++, s++);
}

// #include <stdio.h>
// static void capitalize(unsigned int i, char *c)
// {
// 	(void)i;
// 	*c = ft_toupper(*c);
// }
// int main(void)
// {
// 	char	str[] = "Hello, World!";
// 	ft_striteri(str, &capitalize);
// 	printf("%s\n", str);
// 	return (0);
// }
