/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natsumi <natsumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:49:54 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/17 02:22:06 by natsumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
  char	*line;
  int	last_status;
	
	last_status = 0;
  rl_outstream = stderr;
  while (1)
  {
    line = readline(PROMPT);
    if (line == NULL)
        break ;
    if (*line)
    {
        add_history(line);
        last_status = interpret(line);
    }
    free(line);
  }
  return (last_status);
}
