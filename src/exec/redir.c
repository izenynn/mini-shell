/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:49:51 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/10 14:55:39 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* redirection pipe */
static int	redir_pipe(t_cmd *cmd, t_bool is_parent)
{
	if (cmd->io->is_pipe[FD_IN] == TRUE && !is_parent)
		dup2(cmd->io->fd_read, STDIN_FILENO);
	if (cmd->io->is_pipe[FD_OUT] == TRUE)
		dup2(cmd->io->fd_pipe[WRITE_END], STDOUT_FILENO);
	if (!is_parent && (cmd->io->is_pipe[FD_IN] || cmd->io->is_pipe[FD_OUT]))
	{
		close(cmd->io->fd_pipe[READ_END]);
		close(cmd->io->fd_pipe[WRITE_END]);
		close(cmd->io->fd_read);
	}
	return (0);
}

/* handle type and redir node */
static int	redir_node(t_ast *redir, int fd_io[2], int type)
{
	if (type & AST_RD_TRUNC)
	{
		if (redir_trunc(redir, fd_io) == 1)
			return (1);
	}
	else if (type & AST_RD_APPEND)
	{
		if (redir_append(redir, fd_io) == 1)
			return (1);
	}
	else if (type & AST_RD_INFILE)
	{
		if (redir_infile(redir, fd_io) == 1)
			return (1);
	}
	else if (type & AST_RD_HDOC)
	{
		if (redir_heredoc(redir, fd_io) == 1)
			return (1);
	}
	return (0);
}

/* redirection files ('>', '>>', '<', '<<') */
static int	redir_io(t_cmd *cmd, t_bool is_parent)
{
	int		fd_io[2];
	int		type;
	t_ast	*redir;

	fd_io[0] = -1;
	fd_io[1] = -1;
	redir = cmd->io->redir;
	while (redir != NULL)
	{
		type = ast_gettype(redir);
		if (redir_node(redir, fd_io, type) == 1)
			return (1);
		redir = redir->left;
	}
	if (fd_io[FD_IN] >= 0 && !is_parent)
	{
		dup2(fd_io[FD_IN], STDIN_FILENO);
		close(fd_io[FD_IN]);
	}
	if (fd_io[FD_OUT] >= 0)
	{
		dup2(fd_io[FD_OUT], STDOUT_FILENO);
		close(fd_io[FD_OUT]);
	}
	return (0);
}

/* handle redirections for command */
int	redir_cmd(t_cmd *cmd, t_bool is_parent)
{
	redir_pipe(cmd, is_parent);
	if (redir_io(cmd, is_parent) == 1)
		return (1);
	return (0);
}
