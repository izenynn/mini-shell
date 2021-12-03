/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:53:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/03 15:55:16 by dpoveda-         ###   ########.fr       */
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
	//char	*name;
	t_ast	*res;

	//if (!is_term(TOK, &name))
	//	return (NULL);
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_attach(res, NULL, NULL);
	ast_settype(res, AST_CMD);
	//ast_setdata(res, name);
	res->data = NULL;
	// set cmd_ast global
	g_sh.cmd_ast = res;
	// get token list
	tok_lst();
	// in nothing between nodes
	if (res != NULL && res->data == NULL && res->left == NULL && res->right == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
