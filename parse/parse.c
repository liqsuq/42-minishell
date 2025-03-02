// parse.c

#include "minishell.h"

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

int ft_strcmp(const char *s1, const char *s2)
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

static t_node *parse_simple_command(t_token **rest, t_token *token)
{
  t_node *cmdnode = new_node(ND_SIMPLE_CMD);

  while (token)
  {
    if (token->kind == TK_WORD)
    {
      append_token(&cmdnode->args, tokdup(token));
      token = token->next;
    }
    else if (token->kind == TK_OP &&
             (!ft_strcmp(token->word, ">")  || !ft_strcmp(token->word, ">>") ||
              !ft_strcmp(token->word, "<")  || !ft_strcmp(token->word, "<<")))
    {
      parse_redirection(cmdnode, &token, token);
    }
    else if (token->kind == TK_OP && !ft_strcmp(token->word, "|"))
    {
      // パイプはここでは処理しない。呼び出し元で扱う
      break;
    }
    else
    {
      parse_error("unexpected token", &token, token);
      break;
    }
  }
  // 読み終わった時点で token を呼び出し側に返す
  *rest = token;
  return cmdnode;
}

static t_node *parse_pipeline(t_token **rest, t_token *token)
{
  t_node *left_cmd = parse_simple_command(&token, token);
  // 左辺の単純コマンドを1つ取る
  if (!left_cmd)
  {
    *rest = token;
    return NULL;
  }

  // 次のトークンが '|' なら、パイプラインノードを作る
  if (token && token->kind == TK_OP && !ft_strcmp(token->word, "|"))
  {
    token = token->next; // '|' を消費
    t_node *pipe_node = new_node(ND_PIPELINE);
    pipe_node->left = left_cmd;
    // 右辺は再帰的にパイプラインをパース
    pipe_node->right = parse_pipeline(&token, token);
    *rest = token;
    return pipe_node;
  }

  // パイプがなければ、単純コマンドだけ返す
  *rest = token;
  return left_cmd;
}

t_node *parse(t_token *token)
{
  t_node *root = parse_pipeline(&token, token);
  // 構文エラーがある場合などの処理
  return root;
}
