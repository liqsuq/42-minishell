// nodeutils.c

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (node == NULL)
		fatal_error("malloc");
	node->kind = kind;
	return (node);
}

void	add_node(t_node **head, t_node *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	add_node(&(*head)->next, new);
}

t_token	*tokdup(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, token->kind));
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_node(node->next);
	free_token(node->args);
	free(node);
}

// void	print_nodes(t_node *nodes)
// {
// 	t_node	*cur;

// 	cur = nodes;
// 	while (cur)
// 	{
// 		printf("kind: %d\n", cur->kind);
// 		print_tokens(cur->args);
// 		cur = cur->next;
// 	}
// }
