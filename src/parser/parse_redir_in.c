/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:17:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 14:25:02 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all in redirections in order */
t_ast	*redir_in(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_in_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = redir_in_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* '<<' <file> */
t_ast	*redir_in_1(void)
{
	char	*file;
	t_ast	*res;

	if (!is_term(CHAR_LS, NULL))
		return (NULL);
	if (!is_term(CHAR_LS, NULL))
		return (NULL);
	file = NULL;
	if (!is_term(TOK, &file))
	{
		free(file);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_RD_HDOC);
	ast_setdata(res, file);
	ast_attach(res, NULL, NULL);
	return (res);
}

/* '<' <file> */
t_ast	*redir_in_2(void)
{
	char	*file;
	t_ast	*res;

	if (!is_term(CHAR_LS, NULL))
		return (NULL);
	file = NULL;
	if (!is_term(TOK, &file))
	{
		free(file);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_RD_INFILE);
	ast_setdata(res, file);
	ast_attach(res, NULL, NULL);
	return (res);
}
