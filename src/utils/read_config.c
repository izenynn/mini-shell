/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:57:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/27 17:50:49 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* open rc file */
static int	open_rc(void)
{
	char	*home;
	char	*file;
	int		fd;

	home = ft_getenv("HOME");
	if (home == NULL)
		return (-1);
	file = dir_join(home, RC_FILE);
	free(home);
	if (access(file, R_OK))
	{
		free(file);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		return (-1);
	}
	free(file);
	return (fd);
}

/* read config from .minishrc */
void	read_config(void)
{
	char	*line;
	int		fd;

	fd = open_rc();
	line = ft_get_next_line(fd);
	while (line)
	{
		handle_line(line);
		line = ft_get_next_line(fd);
	}
}