/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:43:18 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/05 15:57:44 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**trans_args(char **argv, t_token *args)
{
	if (args == NULL)
		return (argv);
	*argv = xstrdup(args->word);
	return (trans_args(argv + 1, args->next));
}

char	**new_argv(t_token *args)
{
	char	**argv;
	size_t	len;
	t_token	*cur;

	len = 0;
	cur = args;
	while (cur != NULL)
	{
		len++;
		cur = cur->next;
	}
	argv = xcalloc((len + 1), sizeof(char *));
	if (trans_args(argv, args) == NULL)
		return (free_argv(&argv), NULL);
	return (argv);
}

void	free_argv(char ***argv)
{
	char	**cur;

	cur = *argv;
	while (*cur != NULL)
		free(*cur++);
	free(*argv);
	*argv = NULL;
}
