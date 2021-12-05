/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:10:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 14:26:42 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all redirections in order */
t_ast	*redir(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = redir_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = redir_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <redir in> */
t_ast	*redir_1(void)
{
	t_ast	*res;

	res = redir_in();
	if (res == NULL)
		return (NULL);
	ast_attach(res, NULL, NULL);
	return (res);
}

/* <redir out> */
t_ast	*redir_2(void)
{
	t_ast	*res;

	res = redir_out();
	if (res == NULL)
		return (NULL);
	ast_attach(res, NULL, NULL);
	return (res);
}
