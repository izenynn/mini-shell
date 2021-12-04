/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:27:32 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/03 16:19:11 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all command line in order */
t_ast	*cmd_line(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = cmd_line_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_2();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_3();
	if (new_node)
		return (new_node);
	return (NULL);
}

/* <job> ';' <command line> */
t_ast	*cmd_line_1(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_line_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	while (g_sh.tok != NULL && g_sh.tok->type == CHAR_SC)
		g_sh.tok = g_sh.tok->next;
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, cmd_line_nd);
	return (res);
}

/* <job> ';' */
t_ast	*cmd_line_2(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	while (g_sh.tok != NULL && g_sh.tok->type == CHAR_SC)
		g_sh.tok = g_sh.tok->next;
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, NULL);
	return (res);
}

/* <job> */
t_ast	*cmd_line_3(void)
{
	return (job());
}
