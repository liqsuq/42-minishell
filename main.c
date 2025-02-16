/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:49:54 by kadachi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/16 07:58:03 by kadachi          ###   ########.fr       */
=======
/*   Updated: 2025/02/16 16:54:45 by natsumi          ###   ########.fr       */
>>>>>>> cfd89ca (testを追加)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			interpret(line);
		}
		free(line);
	}
	return (0);
}
