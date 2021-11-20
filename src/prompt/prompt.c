/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 13:53:51 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <sh.h>

/* get line */
static char	*rl_gets(void)
{
	char	*line;

	line = readline("❯ " FG_DEF);
	if (line && *line)
		add_history(line);
	return (line);
}

/* prompt message */
static void	print_prompt_msg(void)
{
	char	*dir;
	char	*prompt_clr;

	dir = (char *)malloc(PATH_MAX * sizeof(char));
	if (getcwd(dir, PATH_MAX) == NULL)
		dir = NULL;
	dir[PATH_MAX - 1] = '\0';
	if (g_sh.status == EXIT_SUCCESS)
		prompt_clr = ft_strdup(FG_MAG);
	else
		prompt_clr = ft_strdup(FG_RED);
	ft_dprintf(STDERR_FILENO, "\n" FG_BLU "%s" FG_DEF "\n" "%s",
		dir, prompt_clr);
	free(dir);
	free(prompt_clr);
}

/* read input on prompt */
char	*prompt_read_input(void)
{
	char	*line;

	print_prompt_msg();
	line = rl_gets();
	return (line);
}
