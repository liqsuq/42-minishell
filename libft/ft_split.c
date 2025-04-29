/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:47:13 by kadachi           #+#    #+#             */
/*   Updated: 2024/11/11 12:54:02 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	splitlen(char const *s, char c)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static size_t	splitcnt(char const *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += splitlen(s, c);
		}
		else
			s++;
	}
	return (count);
}

static void	*splitfree(char **splits)
{
	char	**cur;

	if (splits == NULL)
		return (NULL);
	cur = splits;
	while (*cur != NULL)
		free(*cur++);
	free(splits);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	char	**cur;

	splits = malloc((splitcnt(s, c) + 1) * sizeof(char *));
	if (!splits)
		return (NULL);
	cur = splits;
	while (s != NULL && *s != '\0')
	{
		if (*s != c)
		{
			*cur = ft_substr(s, 0, splitlen(s, c));
			if (*cur++ == NULL)
				return (splitfree(splits));
			s += splitlen(s, c);
		}
		else
			s++;
	}
	*cur = NULL;
	return (splits);
}

// #include <stdio.h>
// int main(void)
// {
// 	char	**splits;
// 	splits = ft_split("   Hello, 42 Tokyo!   ", ' ');
// 	if (splits == NULL)
// 		return (1);
// 	for (int i = 0; splits[i] != NULL; i++)
// 		printf("%s\n", splits[i]);
// 	for (int i = 0; splits[i] != NULL; i++)
// 		free(splits[i]);
// 	free(splits);
// 	return (0);
// }
