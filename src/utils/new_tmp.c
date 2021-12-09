/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:27:51 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/09 14:31:57 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* get new temp file name */
static char	*get_fname(char *dir)
{
	char	*name;
	char	*aux;
	int		i;

	i = 0;
	while (++i < 100)
	{
		aux = ft_itoa(i);
		name = ft_strjoin("/.ms_", aux);
		free(aux);
		aux = name;
		name = ft_strjoin(aux, ".tmp");
		free(aux);
		aux = name;
		name = ft_strjoin(dir, aux);
		free(aux);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
	return (NULL);
}

/* fallback 2 -> create temp file on currect dir */
static char	*fallback_2(void)
{
	char	*file;
	char	*aux;

	file = NULL;
	aux = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	getcwd(aux, PATH_MAX);
	if (aux != NULL)
	{
		if (access(aux, R_OK | W_OK) == 0)
			file = get_fname(aux);
		free(aux);
		if (file != NULL)
			return (file);
	}
	return (NULL);
}

/* fallback 1 -> create temp file in user home dir */
static char	*fallback_1(void)
{
	char	*file;
	char	*aux;

	file = NULL;
	aux = ft_getenv("HOME");
	if (aux != NULL)
	{
		if (access(aux, R_OK | W_OK) == 0)
			file = get_fname(aux);
		free(aux);
		if (file != NULL)
			return (file);
	}
	return (fallback_2());
}

/* create temp file on "/tmp" */
char	*new_tmp(void)
{
	char	*file;

	file = NULL;
	if (access(TMPDIR, R_OK | W_OK) == 0)
	{
		file = get_fname(TMPDIR);
		if (file != NULL)
			return (file);
	}
	return (fallback_1());
}
