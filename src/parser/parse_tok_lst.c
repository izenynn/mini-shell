/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tok_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 10:34:22 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/03 15:10:45 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test token list */
t_ast	*tok_lst(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	// token (name)
	g_sh.tok = save;
	new_node = tok_lst_1();
	if (new_node != NULL)
		return (new_node);

	// token (argument)
	g_sh.tok = save;
	new_node = tok_lst_2();
	if (new_node != NULL)
		return (new_node);

	// redir
	g_sh.tok = save;
	new_node = tok_lst_3();
	if (new_node != NULL)
		return (new_node);

	// null
	g_sh.tok = save;
	new_node = tok_lst_4();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}

/* <name> <token list> */
t_ast	*tok_lst_1(void)
{
	char	*name;

	if (g_sh.cmd_ast->data == NULL)
	{
		// check for command
		if (!is_term(TOK, &name))
			return (NULL);
		// set node data
		ast_setdata(g_sh.cmd_ast, name);
		// tok node
		tok_lst();
		return (g_sh.cmd_ast);
	}
	return (NULL);
}

/* <redir> <token list> */
t_ast	*tok_lst_2(void)
{
	t_ast	*res;

	// redir node
	res = redir();
	if (res == NULL)
		return (NULL);
	// tok node
	tok_lst();
	// insert node
	ast_insert(g_sh.cmd_ast, res, FALSE);
	return (res);
}

/* <token> <token list> */
t_ast	*tok_lst_3(void)
{
	char	*arg;
	t_ast	*res;

	// arg node
	if (!is_term(TOK, &arg))
		return (NULL);
	// create node
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_ARG);
	ast_setdata(res, arg);
	// tok node
	tok_lst();
	// insert node
	ast_insert(g_sh.cmd_ast, res, TRUE);
	return (res);
}

/* (null) */
t_ast	*tok_lst_4(void)
{
	return (NULL);
}
