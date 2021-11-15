/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/15 20:01:28 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

// TODO function that gets current working directory from path

/* read input on prompt */
char	*prompt_read_input(void)
{
	char	*line;
	char	*dir;
	char	*prompt_clr;

	// get cwd
	dir = (char *)malloc(PATH_MAX * sizeof(char));
	if (getcwd(dir, PATH_MAX) == NULL)
		dir = NULL;
	dir[PATH_MAX - 1] = '\0';

	// get color
	if (g_sh.status == EXIT_SUCCESS)
		prompt_clr = FG_MAG;
	else
		prompt_clr = FG_RED;

	// print prompt
	printf("\n" FG_BLU "%s" FG_DEF "\n" "%s", dir, prompt_clr);
	line = readline("❯ " FG_DEF);
	free(dir);
	return (line);
}
