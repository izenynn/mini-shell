/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:24:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/30 14:11:10 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* interpret simple cmd */
static int	handle_simple_cmd(t_ast *ast, t_io *io)
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
	t_ast	*redir_nd;

	if (ast == NULL)
		return (0);
	type = ast_gettype(ast);
	if (type == AST_SIMPLECMD)
		handle_simple_cmd(ast, io);
	else if (type == AST_CMD)
	{
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
		}
		handle_simple_cmd(ast->right, io);
	}
	return (0);
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
