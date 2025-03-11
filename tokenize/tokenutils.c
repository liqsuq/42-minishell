// tokenutil.c

#include "minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		fatal_error(strerror(errno));
	token->word = word;
	token->kind = kind;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*last;

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

void	free_token(t_token *token)
{
	t_token	*next;

	while (token != NULL)
	{
		next = token->next;
		free(token->word);
		free(token);
		token = next;
	}
}
