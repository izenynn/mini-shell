/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:20:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:42:05 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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

/* <simple command> <redir>*/
t_ast	*cmd_3(void)
{
	t_ast	*simple_cmd_nd;
	t_ast	*redir_nd;
	t_ast	*res;

	// <simple cmd>
	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
		return (NULL);
	// <redir>
	redir_nd = redir();
	if (redir_nd == NULL)
	{
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_CMD);
	ast_attach(res, redir_nd, simple_cmd_nd);
	return (res);
}

/* <redir> <simple command> */
t_ast	*cmd_4(void)
{
	t_ast	*simple_cmd_nd;
	t_ast	*redir_nd;
	t_ast	*res;

	// <redir>
	redir_nd = redir();
	if (redir_nd == NULL)
		return (NULL);
	// <simple cmd>
	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
	{
		ast_del(redir_nd);
		return (NULL);
	}
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_CMD);
	ast_attach(res, redir_nd, simple_cmd_nd);
	return (res);
}

/* <simple command> */
t_ast	*cmd_5(void)
{
	return (simple_cmd());
}
