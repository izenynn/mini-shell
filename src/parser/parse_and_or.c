/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:59:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/11 21:42:23 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all "and or" in order */
t_ast	*and_or(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	g_sh.tok = save;
	new_node = and_or_1();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = and_or_2();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = and_or_3();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = and_or_4();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = and_or_5();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = and_or_6();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}

t_ast	*and_or_1(void)
{
	t_ast	*cmd_line_nd;
	t_ast	*res;

	// '('
	if (!is_term(CHAR_OPR, NULL))
		return (NULL);

	// <cmd line>
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
		return (NULL);

	// ')'
	if (!is_term(CHAR_CPR, NULL))
	{
		ast_del(cmd_line_nd);
		return (NULL);
	}

	// '&&'
	if (!is_term(CHAR_AMP, NULL) || !is_term(CHAR_AMP, NULL))
	{
		ast_del(cmd_line_nd);
		return (NULL);
	}

	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_AND);
	//ast_attach(res, job_nd, and_or_nd);
	ast_attach(res, cmd_line_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res);

	// <and or>
	if (and_or() == NULL)
		return (NULL);

	return (res);
}

t_ast	*and_or_2(void)
{
	return (NULL);
}

t_ast	*and_or_3(void)
{
	return (NULL);
}

/* <job> && <and or> */
t_ast	*and_or_4(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	// <job>
	job_nd = job();
	if (job_nd == NULL)
		return (NULL);

	// '&&'
	if (!is_term(CHAR_AMP, NULL) || !is_term(CHAR_AMP, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}

	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_AND);
	//ast_attach(res, job_nd, and_or_nd);
	ast_attach(res, job_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res);

	// <and or>
	if (and_or() == NULL)
		return (NULL);

	return (res);
}

/* <job> || <and or> */
t_ast	*and_or_5(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	// <job>
	job_nd = job();
	if (job_nd == NULL)
		return (NULL);

	// '&&'
	if (!is_term(CHAR_PIPE, NULL) || !is_term(CHAR_PIPE, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}

	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_OR);
	//ast_attach(res, job_nd, and_or_nd);
	ast_attach(res, job_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res);

	// <and or>
	if (and_or() == NULL)
		return (NULL);

	return (res);
}

/* <job> */
t_ast	*and_or_6(void)
{
	t_ast	*res;

	res = job();
	if (res == NULL)
		return (NULL);
	ast_insert_and_or(g_sh.ao_ast, res);
	return (res);
}
