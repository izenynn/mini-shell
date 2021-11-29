/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:20:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:48:37 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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
