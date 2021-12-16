/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:52:08 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 20:52:46 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* '(' <command line> ')'*/
t_ast	*and_or_3(void)
{
	t_ast	*res;
	t_ast	*save;

	if (!is_term(CHAR_OPR, NULL))
		return (NULL);
	save = *g_sh.ao_ast;
	res = cmd_line();
	if (res == NULL)
	{
		*g_sh.ao_ast = save;
		return (NULL);
	}
	*g_sh.ao_ast = save;
	if (!is_term(CHAR_CPR, NULL))
	{
		*g_sh.ao_ast = save;
		ast_del(res);
		return (NULL);
	}
	ast_insert_and_or(g_sh.ao_ast, res, TRUE);
	return (res);
}

/* <job> && <and or> */
t_ast	*and_or_4(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_AMP, NULL) || !is_term(CHAR_AMP, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_AND);
	ast_attach(res, job_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res, FALSE);
	if (and_or() == NULL)
		return (NULL);
	return (res);
}

/* <job> || <and or> */
t_ast	*and_or_5(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_PIPE, NULL) || !is_term(CHAR_PIPE, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_OR);
	ast_attach(res, job_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res, FALSE);
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
	ast_insert_and_or(g_sh.ao_ast, res, TRUE);
	return (res);
}
