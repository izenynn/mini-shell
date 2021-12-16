/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:09:29 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 21:34:38 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle hd on cmd */
static int	hd_cmd(t_ast *ast)
{
	t_ast	*redir;

	redir = ast->left;
	while (redir != NULL)
	{
		if (ast_gettype(redir) & AST_RD_HDOC)
		{
			if (handle_heredoc(redir))
				return (1);
		}
		redir = redir->left;
	}
	return (0);
}

/* handle hd on pipe */
static int	hd_pipe(t_ast *ast)
{
	t_ast	*job;

	if (hd_cmd(ast->left))
		return (1);
	job = ast->right;
	while (job != NULL && ast_gettype(job) == AST_PIPE)
	{
		if (hd_cmd(job->left))
			return (1);
		job = job->right;
	}
	if (hd_cmd(job))
		return (1);
	return (0);
}

/* handle hd on job */
static int	hd_job(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_PIPE)
	{
		if (hd_pipe(ast))
			return (1);
	}
	else
	{
		if (hd_cmd(ast))
			return (1);
	}
	return (0);
}

/* handle hd in "and or" */
static int	hd_and_or(t_ast *ast)
{
	int	type;

	if (ast == NULL)
		return (0);
	type = ast_gettype(ast);
	if (type == AST_AND || type == AST_OR || type == AST_SEQ)
	{
		if (hd_and_or(ast->left))
			return (1);
		if (hd_and_or(ast->right))
			return (1);
	}
	else
	{
		if (hd_job(ast))
			return (1);
	}
	return (0);
}

/* handle hd on command line */
int	hd_cmd_line(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	if (ast_gettype(ast) == AST_SEQ)
	{
		if (hd_and_or(ast->left))
			return (1);
		if (hd_cmd_line(ast->right))
			return (1);
	}
	else
	{
		if (hd_and_or(ast))
			return (1);
	}
	return (0);
}
