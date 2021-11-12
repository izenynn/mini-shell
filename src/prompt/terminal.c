/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/11 14:46:12 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_terminal(void)
{
	char	*line;

	/* display welcome message */
	welcome();
	/* get input loop */
	while (1)
	{
		printf("\n" FG_BLU "TODO print pwd\n" FG_DEF);
		line = readline(FG_MAG "❯" FG_DEF);
		//line = readline(FG_MAG ">" FG_DEF);
		printf("line: %s\n", line);
	}
}
