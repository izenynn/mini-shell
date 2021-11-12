/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/12 11:19:58 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_terminal(void)
{
	welcome();
}

char	*prompt_read_input(void)
{
	char	*line;

	line = readline("\n" FG_BLU "TODO print pwd" FG_DEF "\n" FG_MAG "❯ " FG_DEF);
	return (line);
}
