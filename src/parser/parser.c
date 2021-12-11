/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:22 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/11 22:08:55 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* parse main function */
int	parse(t_lexer *lex, t_ast **ast)
{
	g_sh.tok = lex->tok_lst;
	g_sh.cmdline_ast = (t_ast **)malloc(sizeof(t_ast *));
	*ast = cmd_line();
	if (lex->n_toks == 0)
		return (1);
	if (g_sh.tok != NULL && g_sh.tok->type != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: syntax error near: %s\n",
			g_sh.tok->data);
		free(g_sh.cmdline_ast);
		return (1);
	}
	free(g_sh.cmdline_ast);
	return (0);
}
