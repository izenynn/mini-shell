/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:20:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 17:10:17 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all command in order */
t_ast	*cmd(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = cmd_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_2();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_3();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <simple command> '<' <file> */
t_ast	*cmd_1(void)
{
	char	*file;
	t_ast	*simple_cmd_nd;
	t_ast	*res;

	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_LS, NULL))
	{
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	if (!is_term(TOK, &file))
	{
		free(file);
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR_IN);
	ast_setdata(res, file);
	ast_attach(res, NULL, simple_cmd_nd);
	return (res);
}

/* <simple command> '>' <file> */
t_ast	*cmd_2(void)
{
	char	*file;
	t_ast	*simple_cmd_nd;
	t_ast	*res;

	simple_cmd_nd = simple_cmd();
	if (simple_cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_GT, NULL))
	{
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	if (!is_term(TOK, &file))
	{
		free(file);
		ast_del(simple_cmd_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_REDIR_OUT);
	ast_setdata(res, file);
	ast_attach(res, NULL, simple_cmd_nd);
	return (res);
}

/* <simple command> */
t_ast	*cmd_3(void)
{
	return (simple_cmd());
}
