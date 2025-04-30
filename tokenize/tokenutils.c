/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:47:08 by kadachi           #+#    #+#             */
/*   Updated: 2025/04/29 18:47:29 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		fatal_error("malloc", strerror(errno));
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

	word = ft_strdup(token->word);
	if (word == NULL)
		fatal_error("ft_strdup", strerror(errno));
	return (new_token(word, token->kind));
}

void	pop_token(t_token **head, t_token *token, t_token *prev)
{
	if (head == NULL || *head == NULL || token == NULL)
		return ;
	if (*head == token)
	{
		if (prev != NULL)
			prev->next = (*head)->next;
		else
			*head = (*head)->next;
		free(token->word);
		free(token);
		return ;
	}
	pop_token(&(*head)->next, token, *head);
}
