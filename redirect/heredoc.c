// heredoc.c

#include "minishell.h"

static void read_heredoc_into_node(t_node *heredoc_node, const char *delim, bool is_quoted, t_env *env)
{
  char *line;
  char *buf;
  (void)is_quoted;
  (void)env;

  heredoc_node->heredoc_content = ft_calloc(1, sizeof(char));
  if (!heredoc_node->heredoc_content)
    fatal_error("malloc heredoc_content");
  while (1)
  {
    line = readline("> ");
    if (!line)
      break;
    if (!ft_strcmp(line, delim))
    {
      free(line);
      break;
    }
    buf = ft_strjoin(heredoc_node->heredoc_content, line);
    free(heredoc_node->heredoc_content);
    heredoc_node->heredoc_content = buf;
    buf = ft_strjoin(heredoc_node->heredoc_content, "\n");
    free(heredoc_node->heredoc_content);
    heredoc_node->heredoc_content = buf;
    free(line);
  }
}

t_token *parse_redirect_heredoc(t_data *data, t_node *node, t_token *token)
{
  (void)data;

  t_token *delim_token = token->next;
  bool is_quoted = false;
  if (ft_strchr(delim_token->word, SQUOTE) == NULL
   && ft_strchr(delim_token->word, DQUOTE) == NULL)
    is_quoted = false;
  else
    is_quoted = true;

  read_heredoc_into_node(node, delim_token->word, !is_quoted, NULL);
  return delim_token->next;
}

void setup_heredoc_input(t_node *redi)
{
  int pipefd[2];
  if (pipe(pipefd) < 0)
    fatal_error("pipe");

  if (redi->heredoc_content)
    write(pipefd[1], redi->heredoc_content, ft_strlen(redi->heredoc_content));
  close(pipefd[1]);
  redi->stashed_fd = dup(STDIN_FILENO);
  if (redi->stashed_fd < 0)
    fatal_error("dup (stashed_fd)");
  if (dup2(pipefd[0], STDIN_FILENO) < 0)
    fatal_error("dup2");
  close(pipefd[0]);
}