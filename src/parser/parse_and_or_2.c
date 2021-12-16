/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_or_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:52:08 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 23:56:07 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* support function that creates a node for and_or_4 and and_or_5 */
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
t_ast	*and_or_4(void)
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
t_ast	*and_or_5(void)
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

/* '(' <command line> ')'*/
t_ast	*and_or_6(void)
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
