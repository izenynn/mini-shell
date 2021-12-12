/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:27:32 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/12 00:12:08 by dpoveda-         ###   ########.fr       */
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
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_line_3();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}

/* <and or> ';'... <command line> */
t_ast	*cmd_line_1(void)
{
	t_ast	*and_or_nd;
	t_ast	*cmd_line_nd;
	t_ast	*res;

	// <and or>
	*g_sh.cmdline_ast = NULL;
	and_or();
	and_or_nd = *g_sh.cmdline_ast;
	if (and_or_nd == NULL)
		return (NULL);
	// ';'
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(and_or_nd);
		return (NULL);
	}
	while (g_sh.tok != NULL && g_sh.tok->type == CHAR_SC)
		g_sh.tok = g_sh.tok->next;
	// <command line>
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		ast_del(and_or_nd);
		return (NULL);
	}
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, and_or_nd, cmd_line_nd);
	return (res);
}

/* <and or> ';'... */
t_ast	*cmd_line_2(void)
{
	t_ast	*and_or_nd;
	t_ast	*cmd_line_nd;
	t_ast	*res;

	// <and or>
	*g_sh.cmdline_ast = NULL;
	and_or();
	and_or_nd = *g_sh.cmdline_ast;
	if (and_or_nd == NULL)
		return (NULL);
	// ';'
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(and_or_nd);
		return (NULL);
	}
	while (g_sh.tok != NULL && g_sh.tok->type == CHAR_SC)
		g_sh.tok = g_sh.tok->next;
	// <command line>
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		ast_del(and_or_nd);
		return (NULL);
	}
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, and_or_nd, cmd_line_nd);
	return (res);
}

/* <and or> */
t_ast	*cmd_line_3(void)
{
	t_ast	*and_or_nd;

	// <and or>
	*g_sh.cmdline_ast = NULL;
	and_or();
	and_or_nd = *g_sh.cmdline_ast;
	if (and_or_nd == NULL)
		return (NULL);
	return (and_or_nd);
}
