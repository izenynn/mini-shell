/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:24:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/11/03 19:10:18 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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
	int		p[2];

	if (pipe(fd) == -1)
		perror_ret("pipe", 1);
	p[WRITE_END] = fd[WRITE_END];
	p[READ_END] = fd[READ_END];
	handle_cmd(ast->left, init_io(FALSE, TRUE, fd, p[READ_END]));
	ast = ast->right;
	while (ast != NULL && ast_gettype(ast) == AST_PIPE)
	{
		close(p[WRITE_END]);
		if (pipe(fd) == -1)
			perror_ret("pipe", 1);
		p[WRITE_END] = fd[WRITE_END];
		handle_cmd(ast->left, init_io(TRUE, TRUE, fd, p[READ_END]));
		close(p[READ_END]);
		p[READ_END] = fd[READ_END];
		ast = ast->right;
	}
	p[READ_END] = fd[READ_END];
	handle_cmd(ast, init_io(TRUE, FALSE, fd, p[READ_END]));
	close(p[WRITE_END]);
	close(p[READ_END]);
	return (0);
}

/* interpret job */
static int	handle_job(t_ast *ast)
{
	int null_fd[2];

	null_fd[WRITE_END] = 0;
	null_fd[READ_END] = 0;
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_PIPE)
		handle_pipe(ast);
	else
		handle_cmd(ast, init_io(FALSE, FALSE, null_fd, 0));
	handle_zombies();
	return (0);
}

/* interpret "and or" */
static int	handle_and_or(t_ast *ast)
{
	int	type;

	if (ast == NULL)
		return (0);
	type = ast_gettype(ast);
	if (type == AST_AND)
	{
		handle_and_or(ast->left);
		if (g_sh.status == 0)
			handle_and_or(ast->right);
	}
	else if (type == AST_OR)
	{
		handle_and_or(ast->left);
		if (g_sh.status != 0)
			handle_and_or(ast->right);
	}
	else if (type == AST_SEQ)
	{
		handle_and_or(ast->left);
		handle_and_or(ast->right);
	}
	else
		handle_job(ast);
	return (0);
}

/* interpret command line */
int	handle_cmd_line(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_SEQ)
	{
		handle_and_or(ast->left);
		handle_cmd_line(ast->right);
	}
	else
		handle_and_or(ast);
	return (0);
}
