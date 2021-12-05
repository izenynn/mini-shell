/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:25:53 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 14:25:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all out redirections in order */
t_ast	*redir_out(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_out_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = redir_out_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* '>>' <file> */
t_ast	*redir_out_1(void)
{
	char	*file;
	t_ast	*res;

	if (!is_term(CHAR_GT, NULL))
		return (NULL);
	if (!is_term(CHAR_GT, NULL))
		return (NULL);
	file = NULL;
	if (!is_term(TOK, &file))
	{
		free(file);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_RD_APPEND);
	ast_setdata(res, file);
	ast_attach(res, NULL, NULL);
	return (res);
}

/* '>' <file> */
t_ast	*redir_out_2(void)
{
	char	*file;
	t_ast	*res;

	if (!is_term(CHAR_GT, NULL))
		return (NULL);
	file = NULL;
	if (!is_term(TOK, &file))
	{
		free(file);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_RD_TRUNC);
	ast_setdata(res, file);
	ast_attach(res, NULL, NULL);
	return (res);
}
