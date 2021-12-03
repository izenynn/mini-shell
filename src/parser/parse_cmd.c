/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:53:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/02 19:47:14 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test simple cmd */
t_ast	*cmd(void)
{
	return (cmd_1());
}

/* <name> <token list> */
t_ast	*cmd_1(void)
{
	char	*name;
	t_ast	*res;

	if (!is_term(TOK, &name))
		return (NULL);
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_attach(res, NULL, NULL);
	ast_settype(res, AST_CMD);
	ast_setdata(res, name);
	// set cmd_ast global
	g_sh.cmd_ast = res;
	// get token list
	tok_lst();
	return (res);
}
