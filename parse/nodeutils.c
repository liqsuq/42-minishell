// nodeutils.c

#include "minishell.h"

t_node	*new_node(t_node_kind kind)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		fatal_error("malloc");
	ft_bzero(node, sizeof(t_node));
	node->kind = kind;
	return (node);
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	append_token(t_token **tokens, t_token *tok)
{
	if (*tokens == NULL)
	{
		*tokens = tok;
		return ;
	}
	append_token(&(*tokens)->next, tok);
}

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

void	free_nodes(t_node *node)
{
	t_node	*next;

	while (node != NULL)
	{
		next = node->next;
		free_tokens(node->args);
		free(node);
		node = next;
	}
}

void	print_nodes(t_node *nodes)
{
	t_node	*cur;

	cur = nodes;
	while (cur)
	{
		printf("kind: %d\n", cur->kind);
		print_tokens(cur->args);
		cur = cur->next;
	}
}
