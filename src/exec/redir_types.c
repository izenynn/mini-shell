/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:01:14 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/10 12:10:04 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* redir '>' */
int	redir_trunc(t_ast *redir, int fd_io[2])
{
	if (fd_io[FD_OUT] >= 0)
		close(fd_io[FD_OUT]);
	fd_io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_io[FD_OUT] == -1)
		return (perror_ret(redir->data, 1));
	return (0);
}

/* redir '>>' */
int	redir_append(t_ast *redir, int fd_io[2])
{
	if (fd_io[FD_OUT] >= 0)
		close(fd_io[FD_OUT]);
	fd_io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd_io[FD_OUT] == -1)
		return (perror_ret(redir->data, 1));
	return (0);
}

/* redir '<' */
int	redir_infile(t_ast *redir, int fd_io[2])
{
	if (fd_io[FD_IN] >= 0)
		close(fd_io[FD_IN]);
	fd_io[FD_IN] = open(redir->data, O_RDONLY);
	if (fd_io[FD_IN] == -1)
		return (perror_ret(redir->data, 1));
	return (0);
}

/* redir '<<' */
int	redir_heredoc(t_ast *redir, int fd_io[2])
{
	if (fd_io[FD_IN] >= 0)
		close(fd_io[FD_IN]);
	fd_io[FD_IN] = open(redir->data, O_RDONLY);
	if (fd_io[FD_IN] == -1)
		return (perror_ret(redir->data, 1));
	if (unlink(redir->data) == -1)
		perror_ret("unlink", 1);
	return (0);
}
