// tokenutils.c

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

t_token	*add_token(t_token **head, t_token *new)
{
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	return (add_token(&(*head)->next, new));
}

void	free_token(t_token *token)
{
	if (token == NULL)
		return ;
	free_token(token->next);
	free(token->word);
	free(token);
}

t_token	*dup_token(t_token *token)
{
	char	*word;

	word = strdup(token->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, token->kind));
}

void	pop_token(t_token **head, t_token *token)
{
	t_token	*cur;
	t_token	*prev;

	if (head == NULL || *head == NULL || token == NULL)
		return ;
	cur = *head;
	prev = NULL;
	while (cur != NULL)
	{
		if (cur == token)
		{
			if (prev != NULL)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(token->word);
			free(token);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
