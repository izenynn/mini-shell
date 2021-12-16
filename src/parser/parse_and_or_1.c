/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:59:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 23:55:51 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all "and or" in order support func. */
t_ast	*and_or_sup(t_tok *save)
{
	t_ast	*new_node;

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
	return (and_or_sup(save));
}

/* <job> && <and or> */
t_ast	*and_or_1(void)
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
t_ast	*and_or_2(void)
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
t_ast	*and_or_3(void)
{
	t_ast	*res;

	res = job();
	if (res == NULL)
		return (NULL);
	ast_insert_and_or(g_sh.ao_ast, res, TRUE);
	return (res);
}
