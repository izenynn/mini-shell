/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:53:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 14:24:29 by dpoveda-         ###   ########.fr       */
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
	t_ast	*res;

	res = (t_ast *)malloc(sizeof(t_ast));
	ast_attach(res, NULL, NULL);
	ast_settype(res, AST_CMD);
	res->data = NULL;
	g_sh.cmd_ast = res;
	tok_lst();
	if (res != NULL && res->data == NULL
		&& res->left == NULL && res->right == NULL)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
