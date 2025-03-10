// parse.c

#include "minishell.h"

static int ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

static void parse_redirection(t_node *cmdnode, t_token **rest, t_token *token)
{
  t_node *redir_node = NULL;

  if (!ft_strcmp(token->word, ">"))
    redir_node = new_node(ND_REDIR_OUT);
  else if (!ft_strcmp(token->word, ">>"))
    redir_node = new_node(ND_REDIR_APPEND);
  else if (!ft_strcmp(token->word, "<"))
    redir_node = new_node(ND_REDIR_IN);
  else if (!ft_strcmp(token->word, "<<"))
    redir_node = new_node(ND_REDIR_HEREDOC);
  else
    parse_error("unexpected redirection operator", rest, token);

  token = token->next;
  if (!token || token->kind != TK_WORD)
    parse_error("expected filename (or 'EOF') after redirection", rest, token);

  if (redir_node->kind == ND_REDIR_HEREDOC)
  {
    if (ft_strcmp(token->word, "EOF") != 0)
      parse_error("this minishell only supports '<<EOF' heredoc", rest, token);
  }
  else
  {
    redir_node->filename = tokdup(token);
  }

  add_node(&cmdnode->redirects, redir_node);

  token = token->next;
  *rest = token;
}

t_node *parse(t_token *token)
{
  if (!token)
    return NULL;

  // 最初のコマンドノードを作成
  t_node *head = new_node(ND_SIMPLE_CMD);
  t_node *current = head;

  while (token)
  {
    if (token->kind == TK_WORD)
    {
      append_token(&current->args, tokdup(token));
      token = token->next;
    }
    else if (token->kind == TK_OP)
    {
      if (!ft_strcmp(token->word, "|"))
      {
        token = token->next;
        t_node *newcmd = new_node(ND_SIMPLE_CMD);
        current->next = newcmd;
        current = newcmd;
      }
      else if (!ft_strcmp(token->word, ">")  || !ft_strcmp(token->word, ">>") ||
               !ft_strcmp(token->word, "<")  || !ft_strcmp(token->word, "<<"))
      {
        parse_redirection(current, &token, token);
      }
      else
        parse_error("unexpected token", &token, token);
    }
    else
      parse_error("unexpected token", &token, token);
  }
  return head;
}