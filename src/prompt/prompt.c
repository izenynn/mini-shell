/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:44 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/30 14:01:21 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* prompt message */
static char	*get_prompt_cwd(void)
{
	char	*dir;
	char	*home;
	char	*res;

	dir = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	if (getcwd(dir, PATH_MAX) == NULL)
	{
		free(dir);
		dir = NULL;
	}
	if (dir == NULL)
		dir = ft_getenv("PWD");
	if (dir == NULL)
		return (ft_strdup("error"));
	dir[ft_strlen(dir)] = '\0';
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

	aux1 = get_prompt_cwd();
	aux2 = ft_strdup("$ ");
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
	line = readline(prompt);
	//line = readline("> ");
	free(prompt);
	return (line);
}
