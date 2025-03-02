#include "minishell.h"

int exec_pipeline(t_node *node)
{
	pid_t pids[256];
	pid_t pid = fork();
	int cmd_count = 0;
	int status = 0;
	int i = 0;
	int in_fd = STDIN_FILENO;
	char **argv = tokens2argv(node->args);

	while (node)
  {
		int pipefd[2];

		if (node->next)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				exit(1);
			}
		}

		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}

		if (pid == 0)
    {
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (node->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			execvp(argv[0], argv);
			perror("execvp");
			exit(127);
		}
    else
    {
			pids[cmd_count++] = pid;
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (node->next)
			{
				close(pipefd[1]);
				in_fd = pipefd[0];
			}
			node = node->next;
		}
	}

  while (i < cmd_count)
  {
    int wstatus;
    waitpid(pids[i], &wstatus, 0);  
    if (i == cmd_count - 1)
      status = WEXITSTATUS(wstatus);
    i++;
  }
	return status;
}
