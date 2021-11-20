/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:34:22 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 12:12:00 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh/ast.h"
#include "sh/parser.h"
#include <sh.h>

/* test token list */
t_ast	*tok_lst(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = tok_lst_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = tok_lst_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <token> <token list> */
t_ast	*tok_lst_1(void)
{
	char	*arg;
	t_ast	*tok_lst_nd;
	t_ast	*res;

	if (!is_term(TOK, &arg))
		return (NULL);
	tok_lst_nd = tok_lst();
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_ARG);
	ast_setdata(res, arg);
	ast_attach(res, NULL, tok_lst_nd);
	return (res);
}

/* (null) */
t_ast	*tok_lst_2(void)
{
	return (NULL);
}
