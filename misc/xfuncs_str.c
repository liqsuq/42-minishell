/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfuncs_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:26:50 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 16:01:11 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*xstrdup(const char *s)
{
	char	*str;

	str = ft_strdup(s);
	if (str == NULL)
		fatal_error("strdup", strerror(errno));
	return (str);
}

char	*xsubstr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (str == NULL)
		fatal_error("substr", strerror(errno));
	return (str);
}

char	*xitoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (str == NULL)
		fatal_error("itoa", strerror(errno));
	return (str);
}
