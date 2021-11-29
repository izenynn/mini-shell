/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:10:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:18:31 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all redirections in order */
t_ast	*redir(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	g_sh.tok = save;
	new_node = redir_1();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = redir_2();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = redir_3();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = redir_4();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}

/* <redir in> <redir out> */
t_ast	*redir_1(void)
{
	t_ast	*redir_in_nd;
	t_ast	*redir_out_nd;
	t_ast	*res;

	// <redir in>
	redir_in_nd = redir_in();
	if (redir_in_nd == NULL)
		return (NULL);

	// <redir out>
	redir_out_nd = redir_out();
	if (redir_out_nd == NULL)
	{
		ast_del(redir_in_nd);
		return (NULL);
	}

	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR);
	ast_attach(res, redir_in_nd, redir_out_nd);
	return (res);
}

/* <redir out> <redir in> */
t_ast	*redir_2(void)
{
	t_ast	*redir_in_nd;
	t_ast	*redir_out_nd;
	t_ast	*res;

	// <redir out>
	redir_out_nd = redir_out();
	if (redir_out_nd == NULL)
		return (NULL);

	// <redir in>
	redir_in_nd = redir_in();
	if (redir_in_nd == NULL)
	{
		ast_del(redir_out_nd);
		return (NULL);
	}

	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR);
	ast_attach(res, redir_in_nd, redir_out_nd);
	return (res);
}

/* <redir in> */
t_ast	*redir_3(void)
{
	t_ast	*redir_in_nd;
	t_ast	*res;

	// <redir in>
	redir_in_nd = redir_in();
	if (redir_in_nd == NULL)
		return (NULL);

	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR);
	ast_attach(res, redir_in_nd, NULL);
	return (res);
}

/* <redir out> */
t_ast	*redir_4(void)
{
	t_ast	*redir_out_nd;
	t_ast	*res;

	// <redir out>
	redir_out_nd = redir_out();
	if (redir_out_nd == NULL)
		return (NULL);

	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR);
	ast_attach(res, NULL, redir_out_nd);
	return (res);
}
