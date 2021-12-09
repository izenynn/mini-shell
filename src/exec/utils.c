/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:48:15 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/09 15:54:44 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* initialise io struct */
t_io	*init_io(t_bool p_read, t_bool p_write, int fd_pipe[2], int fd_read)
{
	t_io	*io;

	io = (t_io *)malloc(sizeof(t_io));
	io->is_pipe[READ_END] = p_read;
	io->is_pipe[WRITE_END] = p_write;
	if (p_read || p_write)
	{
		io->fd_pipe[READ_END] = fd_pipe[READ_END];
		io->fd_pipe[WRITE_END] = fd_pipe[WRITE_END];
		io->fd_read = fd_read;
	}
	io->redir = 0;
	return (io);
}

/* join two strings with a '/' between them */
char	*dir_join(char const *dir1, char const *dir2)
{
	char	*save;
	char	*out;

	if (!dir1 || !dir2)
		return (NULL);
	out = malloc(ft_strlen(dir1) + ft_strlen(dir2) + 2);
	if (!out)
		return (NULL);
	save = out;
	while (*dir1)
		*out++ = *dir1++;
	*out++ = '/';
	while (*dir2)
		*out++ = *dir2++;
	*out = '\0';
	return (save);
}
