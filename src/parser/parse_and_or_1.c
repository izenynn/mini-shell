/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:59:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 20:53:08 by dpoveda-         ###   ########.fr       */
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

static t_ast	*new_and_or_node(int type, t_ast *cmd_line_nd)
{
	t_ast	*res;

	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, type);
	ast_attach(res, cmd_line_nd, NULL);
	ast_insert_and_or(g_sh.ao_ast, res, FALSE);
	return (res);
}

/* '(' <command line> ')' && <and or> */
t_ast	*and_or_1(void)
{
	t_ast	*cmd_line_nd;
	t_ast	*res;
	t_ast	*save;

	if (!is_term(CHAR_OPR, NULL))
		return (NULL);
	save = *g_sh.ao_ast;
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		*g_sh.ao_ast = save;
		return (NULL);
	}
	*g_sh.ao_ast = save;
	if (!is_term(CHAR_CPR, NULL)
		|| !is_term(CHAR_AMP, NULL) || !is_term(CHAR_AMP, NULL))
	{
		ast_del(cmd_line_nd);
		return (NULL);
	}
	res = new_and_or_node(AST_AND, cmd_line_nd);
	if (and_or() == NULL)
		return (NULL);
	return (res);
}

/* '(' <command line> ')' || <and or> */
t_ast	*and_or_2(void)
{
	t_ast	*cmd_line_nd;
	t_ast	*res;
	t_ast	*save;

	if (!is_term(CHAR_OPR, NULL))
		return (NULL);
	save = *g_sh.ao_ast;
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		*g_sh.ao_ast = save;
		return (NULL);
	}
	*g_sh.ao_ast = save;
	if (!is_term(CHAR_CPR, NULL)
		|| !is_term(CHAR_PIPE, NULL) || !is_term(CHAR_PIPE, NULL))
	{
		ast_del(cmd_line_nd);
		return (NULL);
	}
	res = new_and_or_node(AST_OR, cmd_line_nd);
	if (and_or() == NULL)
		return (NULL);
	return (res);
}
