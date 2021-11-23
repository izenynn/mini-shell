/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/23 14:01:49 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* If part of the pwd is home, we'll change it for ~ like bash does*/
static int	check_for_home(char **dir)
{
	char	*home;
	char	*tmp;

	home = ft_getenv("HOME");
	if (home == NULL)
		return (1);
	if (ft_strncmp(*dir, home, ft_strlen(home)) == 0)
	{
		tmp = ft_substr(*dir, ft_strlen(home) - 1,
				ft_strlen(*dir) - ft_strlen(home) + 1);
		tmp[0] = '~';
		free(*dir);
		*dir = ft_strdup(tmp);
		free(tmp);
		free(home);
		return (0);
	}
	free(home);
	return (1);
}

/* prompt message */
static void	print_cwd(void)
{
	char	*dir;

	dir = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	if (getcwd(dir, PATH_MAX) == NULL)
		dir = NULL;
	dir[PATH_MAX] = '\0';
	if (check_for_home(&dir) == 1)
	{
		if (getcwd(dir, PATH_MAX) == NULL)
			dir = NULL;
	}
	ft_dprintf(STDERR_FILENO, "\n" FG_BLU "%s" FG_DEF "\n",
		dir);
	free(dir);
}

/* read input on prompt */
char	*get_prompt(void)
{
	char	*line;

	print_cwd();
	if (g_sh.status == EXIT_SUCCESS)
		line = readline(FG_MAG "❯ " FG_DEF);
	else
		line = readline(FG_RED "❯ " FG_DEF);
	return (line);
}
