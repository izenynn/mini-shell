/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:57:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/27 16:11:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* read config from .minishrc */
void	read_config(void)
{
	char	*home;
	char	*file;
	char	*line;
	int		fd;

	home = ft_getenv("HOME");
	if (home == NULL)
		return ;
	file = dir_join(home, RC_FILE);
	free(home);
	if (access(file, R_OK))
	{
		free(file);
		return ;
	}
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return ;
	line = ft_get_next_line(fd);
	while (line)
	{
		handle_line(line);
		line = ft_get_next_line(fd);
	}
}
