/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:24:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/03 14:50:18 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* interpret simple cmd */
static int	handle_cmd_exec(t_ast *ast, t_io *io)
{
	t_cmd	cmd;

	cmd_init(&cmd, ast, io);
	handle_exec_cmd(&cmd);
	cmd_del(&cmd);
	return (0);
}

/* interpret cmd */
static int	handle_cmd(t_ast *ast, t_io *io)
{
	int	type;

	if (ast == NULL)
		return (0);
	type = ast_gettype(ast);
	if (type == AST_CMD)
	{
		/*
		redir_nd = ast->left;
		// redir in
		if (redir_nd->left != NULL)
		{
			if (ast_gettype(redir_nd->left) == AST_RD_INFILE)
			{
				io->redir |= RD_INFILE;
				io->files[FD_IN] = redir_nd->left->data;
			}
			if (ast_gettype(redir_nd->left) == AST_RD_HDOC)
			{
				io->redir |= RD_HDOC;
				io->files[FD_IN] = redir_nd->left->data;
			}
		}
		// redir out
		if (redir_nd->right != NULL)
		{
			if (ast_gettype(redir_nd->right) == AST_RD_TRUNC)
			{
				io->redir |= RD_TRUNC;
				io->files[FD_OUT] = redir_nd->right->data;
			}
			if (ast_gettype(redir_nd->right) == AST_RD_APPEND)
			{
				io->redir |= RD_APPEND;
				io->files[FD_OUT] = redir_nd->right->data;
			}
		}*/
		io->redir = ast->left;
		handle_cmd_exec(ast, io);
	}
	return (0);
}

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

/* interpret pipe */
static int	handle_pipe(t_ast *ast)
{
	int		fd[2];
	int		p_read;
	int		p_write;
	t_ast	*job;

	if (pipe(fd) == -1)
		perror_ret("pipe", 1);
	p_write = fd[WRITE_END];
	p_read = fd[READ_END];

	handle_cmd(ast->left, init_io(FALSE, TRUE, fd, p_read));

	job = ast->right;
	while (job != NULL && ast_gettype(job) == AST_PIPE)
	{
		close(p_write);
		if (pipe(fd) == -1)
			perror_ret("pipe", 1);
		p_write = fd[WRITE_END];

		handle_cmd(job->left, init_io(TRUE, TRUE, fd, p_read));

		close(p_read);
		p_read = fd[READ_END];
		job = job->right;
	}
	p_read = fd[READ_END];

	handle_cmd(job, init_io(TRUE, FALSE, fd, p_read));

	close (p_write);
	close(p_read);
	return (0);
}

/* interpret job */
static int	handle_job(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_PIPE)
		handle_pipe(ast);
	else
		handle_cmd(ast, init_io(FALSE, FALSE, 0, 0));
	handle_zombies();
	return (0);
}

/* interpret command line */
static int	handle_cmd_line(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_SEQ)
	{
		handle_job(ast->left);
		handle_cmd_line(ast->right);
	}
	else
		handle_job(ast);
	return (0);
}

/* execute syntax tree */
int	exec_ast(t_ast *ast)
{
	handle_cmd_line(ast);
	//handle_zombies();
	return (0);
}
