#include "../minishell.h"

static void redirect_output(t_node *node)
{
    node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (node->filefd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    node->stashed_std_fd = dup(STDOUT_FILENO);
    if (node->stashed_std_fd < 0)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    if (dup2(node->filefd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(node->filefd);
    node->filefd = -1;
}

static void redirect_input(t_node *node)
{
    node->filefd = open(node->filename->word, O_RDONLY);
    if (node->filefd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    node->stashed_std_fd = dup(STDIN_FILENO);
    if (node->stashed_std_fd < 0)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    if (dup2(node->filefd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(node->filefd);
    node->filefd = -1;
}

static void redirect_append(t_node *node)
{
    node->filefd = open(node->filename->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (node->filefd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    node->stashed_std_fd = dup(STDOUT_FILENO);
    if (node->stashed_std_fd < 0)
    {
        perror("dup");
        exit(EXIT_FAILURE);
    }
    if (dup2(node->filefd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(node->filefd);
    node->filefd = -1;
}


void perform_redirection(t_node *node, t_env **env)
{
    (void)env;

    if (node->kind == ND_REDIR_OUT)
        redirect_output(node);
    else if (node->kind == ND_REDIR_IN)
        redirect_input(node);
    else if (node->kind == ND_REDIR_APPEND)
        redirect_append(node);
    // else if (node->kind == ND_REDIR_HEREDOC)
    //     redirect_heredoc(node, env);
}

void reset_redirection(t_node *node)
{
    if (node->kind == ND_REDIR_OUT || node->kind == ND_REDIR_APPEND)
    {
        if (dup2(node->stashed_std_fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    else if (node->kind == ND_REDIR_IN || node->kind == ND_REDIR_HEREDOC)
    {
        if (dup2(node->stashed_std_fd, STDIN_FILENO) < 0)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
    }
    close(node->stashed_std_fd);
}

// static void redirect_heredoc(t_node *node, t_env **env)
// {
//     node->filefd = read_heredoc(node->delimiter->word, node->is_delimiter_quote, env);
//     if (node->filefd < 0)
//     {
//         perror("heredoc");
//         exit(EXIT_FAILURE);
//     }
//     node->stashed_std_fd = dup(STDIN_FILENO);
//     if (node->stashed_std_fd < 0)
//     {
//         perror("dup");
//         exit(EXIT_FAILURE);
//     }
//     if (dup2(node->filefd, STDIN_FILENO) < 0)
//     {
//         perror("dup2");
//         exit(EXIT_FAILURE);
//     }
//     close(node->filefd);
//     node->filefd = -1;
// }

// int read_heredoc(const char *delimiter, bool is_delimiter_quote, void *env)
// {
//     int pipefd[2];
//     char *line;

//     (void)is_delimiter_quote;  // 今は使わないので無視
//     (void)env;                 // 今は使わないので無視

//     if (pipe(pipefd) < 0)
//     {
//         perror("pipe");
//         return -1;
//     }

//     while (1)
//     {
//         line = readline("> ");
//         if (!line)
//         {
//             break;
//         }
//         if (strcmp(line, delimiter) == 0)
//         {
//             free(line);
//             break;
//         }
//         dprintf(pipefd[1], "%s\n", line);
//         free(line);
//     }
//     close(pipefd[1]);
//     return pipefd[0];
// }
