/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:34:22 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/02 19:45:08 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test token list */
t_ast	*tok_lst(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	// token (argument)
	g_sh.tok = save;
	new_node = tok_lst_1();
	if (new_node != NULL)
		return (new_node);

	// redir
	g_sh.tok = save;
	new_node = tok_lst_2();
	if (new_node != NULL)
		return (new_node);

	// null
	g_sh.tok = save;
	new_node = tok_lst_3();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <redir> <token list> */
t_ast	*tok_lst_1(void)
{
	t_ast	*res;

	// redir node
	res = redir();
	if (res == NULL)
		return (NULL);
	// tok node
	tok_lst();
	// create node
	//res = (t_ast *)malloc(sizeof(t_ast));
	// attach to the left node of redirs :D
	ast_insert(g_sh.cmd_ast, res, FALSE);
	return (res);
}

/* <token> <token list> */
t_ast	*tok_lst_2(void)
{
	char	*arg;
	t_ast	*res;

	// arg node
	if (!is_term(TOK, &arg))
		return (NULL);
	// tok node
	tok_lst();
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_ARG);
	ast_setdata(res, arg);
	//ast_attach(res, NULL, tok_lst_nd);
	ast_insert(g_sh.cmd_ast, res, TRUE);
	return (res);
}

/* (null) */
t_ast	*tok_lst_3(void)
{
	return (NULL);
}
