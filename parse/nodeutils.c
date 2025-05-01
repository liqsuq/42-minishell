/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodeutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:46:11 by kadachi           #+#    #+#             */
/*   Updated: 2025/05/01 17:28:14 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	return (node);
}

t_node	*add_node(t_node **head, t_node *new)
{
	if (head == NULL || new == NULL)
		return (NULL);
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	return (add_node(&(*head)->next, new));
}

void	free_node(t_node **node)
{
	if (node == NULL || *node == NULL)
		return ;
	free_node(&(*node)->next);
	free_node(&(*node)->redirects);
	free_token(&(*node)->args);
	free(*node);
}
