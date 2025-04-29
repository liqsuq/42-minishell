// nodeutils.c

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		fatal_error("malloc", strerror(errno));
	node->kind = kind;
	return (node);
}

t_node	*add_node(t_node **head, t_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	return (add_node(&(*head)->next, new));
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_node(node->next);
	free_node(node->redirects);
	free_token(node->args);
	free(node);
}
