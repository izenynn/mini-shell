/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:24:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/09 15:57:51 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*static int	handle_cmd_exec(t_ast *ast, t_io *io)
{
	t_cmd	cmd;

	cmd_init(&cmd, ast, io);
	handle_exec_cmd(&cmd);
	cmd_del(&cmd);
	return (0);
}*/

/* interpret cmd */
static int	handle_cmd(t_ast *ast, t_io *io)
{
	int		type;
	t_cmd	cmd;

	if (ast == NULL)
		return (0);
	type = ast_gettype(ast);
	if (type == AST_CMD)
	{
		io->redir = ast->left;
		//
		//handle_cmd_exec(ast, io);
		//
		cmd_init(&cmd, ast, io);
		handle_exec_cmd(&cmd);
		cmd_del(&cmd);
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
	return (0);
}
