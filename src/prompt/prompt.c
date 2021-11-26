/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 19:51:49 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_str.h"
#include "sh/utils.h"
#include <sh.h>

/* change home folder for '~' */
/*static int	check_for_home(char **dir)
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
}*/

/* prompt message */
static char	*get_prompt_cwd(void)
{
	char	*dir;
	char	*home;
	char	*res;

	dir = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	if (getcwd(dir, PATH_MAX) == NULL)
		dir = NULL;
	dir[PATH_MAX] = '\0';
	home = ft_getenv("HOME");
	if (home != NULL && !ft_strncmp(home, dir, ft_strlen(dir) + 1))
	{
		res = ft_strdup("~");
		free(dir);
	}
	else if (ft_strlen(dir) > 1)
	{
		res = ft_strdup(dir + (ft_strrchr(dir, '/') - dir) + 1);
		free(dir);
	}
	else
		res = dir;
	free(home);
	return (res);
}

/* get prompt text */
static char	*get_prompt(void)
{
	char	*msg;
	char	*aux1;
	char	*aux2;

	aux1 = ft_strdup(" " FG_BLU);
	aux2 = get_prompt_cwd();
	msg = ft_strjoin(aux1, aux2);
	free(aux1);
	free(aux2);
	aux1 = msg;
	if (g_sh.status == EXIT_SUCCESS)
		aux2 = ft_strdup(" " FG_MAG "❯" FG_DEF " ");
	else
		aux2 = ft_strdup(" " FG_RED "❯" FG_DEF " ");
	msg = ft_strjoin(aux1, aux2);
	free(aux1);
	free(aux2);
	return (msg);
}

/* read input on prompt */
char	*read_prompt(void)
{
	char	*line;
	char	*prompt;

	prompt = get_prompt();
	//line = readline(prompt);
	line = readline("> ");
	free(prompt);
	return (line);
}
