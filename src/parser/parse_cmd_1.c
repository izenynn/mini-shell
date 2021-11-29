/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:30:53 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:48:35 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all command in order */
t_ast	*cmd(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	g_sh.tok = save;
	new_node = cmd_1();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_2();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_3();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_4();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_5();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}

/* <redir in> <simple cmd> <redir out> */
t_ast	*cmd_1(void)
{
	t_ast	*redir_in_nd;
	t_ast	*redir_out_nd;
	t_ast	*simple_cmd_nd;
	t_ast	*redir_nd;
	t_ast	*res;

	// <redir in>
	redir_in_nd = redir_in();
	if (redir_in_nd == NULL)
		return (NULL);
	// <simple cmd>
	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
	{
		ast_del(redir_in_nd);
		return (NULL);
	}
	// <redir out>
	redir_out_nd = redir_out();
	if (redir_out_nd == NULL)
	{
		ast_del(redir_in_nd);
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	// create redir node
	redir_nd = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(redir_nd, AST_REDIR);
	ast_attach(redir_nd, redir_in_nd, redir_out_nd);
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_CMD);
	ast_attach(res, redir_nd, simple_cmd_nd);
	return (res);
}

/* <redir out> <simple cmd> <redir in> */
t_ast	*cmd_2(void)
{
	t_ast	*redir_in_nd;
	t_ast	*redir_out_nd;
	t_ast	*simple_cmd_nd;
	t_ast	*redir_nd;
	t_ast	*res;

	// <redir out>
	redir_out_nd = redir_out();
	if (redir_out_nd == NULL)
		return (NULL);
	// <simple cmd>
	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
	{
		ast_del(redir_out_nd);
		return (NULL);
	}
	// <redir in>
	redir_in_nd = redir_in();
	if (redir_in_nd == NULL)
	{
		ast_del(redir_out_nd);
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	// create redir node
	redir_nd = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(redir_nd, AST_REDIR);
	ast_attach(redir_nd, redir_in_nd, redir_out_nd);
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_CMD);
	ast_attach(res, redir_nd, simple_cmd_nd);
	return (res);
}
