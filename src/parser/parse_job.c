/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:03:15 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 23:56:22 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all job in order */
t_ast	*job(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = job_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = job_2();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = job_3();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = job_4();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* '(' <command> ')' '|' <job> */
t_ast	*job_1(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_nd;
	t_ast	*res;

	if (!is_term(CHAR_OPR, NULL))
		return (NULL);
	cmd_nd = cmd();
	if (cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_CPR, NULL) || !is_term(CHAR_PIPE, NULL))
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	job_nd = job();
	if (job_nd == NULL)
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_PIPE);
	ast_attach(res, cmd_nd, job_nd);
	return (res);
}

/* <command> '|' <job> */
t_ast	*job_2(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_nd;
	t_ast	*res;

	cmd_nd = cmd();
	if (cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_PIPE, NULL))
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	job_nd = job();
	if (job_nd == NULL)
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_PIPE);
	ast_attach(res, cmd_nd, job_nd);
	return (res);
}

/* '(' <command> ')' */
t_ast	*job_3(void)
{
	t_ast	*cmd_nd;

	if (!is_term(CHAR_OPR, NULL))
		return (NULL);
	cmd_nd = cmd();
	if (cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_CPR, NULL))
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	return (cmd_nd);
}

/* <command> */
t_ast	*job_4(void)
{
	return (cmd());
}
