/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:18:29 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:29:59 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test simple cmd */
t_ast	*simple_cmd(void)
{
	return (simple_cmd_1());
}

/* <name> <token list> */
t_ast	*simple_cmd_1(void)
{
	char	*name;
	t_ast	*tok_lst_nd;
	t_ast	*res;

	if (!is_term(TOK, &name))
		return (NULL);
	tok_lst_nd = tok_lst();
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SIMPLECMD);
	ast_setdata(res, name);
	ast_attach(res, NULL, tok_lst_nd);
	return (res);
}
