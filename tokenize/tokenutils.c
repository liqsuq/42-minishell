// tokenutils.c

#include "minishell.h"

int	tokenlen(t_token *token)
{
	if (token == NULL)
		return (0);
	return (1 + tokenlen(token->next));
}

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
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	add_token(&(*head)->next, new);
}

t_token	*dup_token(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, token->kind));
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	free_token(token->next);
	free(token->word);
	free(token);
}
