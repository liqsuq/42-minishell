/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:41:34 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/02 16:03:34 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path	*new_path(char *name, size_t len)
{
	t_path	*path;

	if (name == NULL)
		return (NULL);
	path = ft_calloc(1, sizeof(t_path));
	if (path == NULL)
		return (NULL);
	path->name = ft_substr(name, 0, len);
	if (path->name == NULL)
		return (free(path), NULL);
	path->next = NULL;
	return (path);
}

t_path	*push_path(t_path **head, t_path *new)
{
	if (head == NULL || new == NULL)
		return (NULL);
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	return (push_path(&(*head)->next, new));
}

void	pop_path(t_path **head, t_path *prev)
{
	if (head == NULL || *head == NULL)
		return ;
	if ((*head)->next == NULL)
	{
		free((*head)->name);
		free(*head);
		if (prev != NULL)
			prev->next = NULL;
		else
			*head = NULL;
		return ;
	}
	pop_path(&(*head)->next, *head);
}

char	*dump_path(t_path *head)
{
	char	path[PATH_MAX];

	ft_bzero(path, sizeof(path));
	while (head != NULL)
	{
		if (ft_strlcat(path, "/", sizeof(path)) >= PATH_MAX
			|| ft_strlcat(path, head->name, sizeof(path)) >= PATH_MAX)
			return (NULL);
		head = head->next;
	}
	if (ft_strlen(path) == 0)
		return (ft_strdup("/"));
	return (ft_strdup(path));
}

void	free_path(t_path **path)
{
	if (path == NULL || *path == NULL)
		return ;
	free_path(&(*path)->next);
	free((*path)->name);
	free(*path);
	*path = NULL;
}
