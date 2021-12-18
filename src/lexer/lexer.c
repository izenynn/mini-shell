/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 20:48:34 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* process char */
static int	process_char(t_lexsup *ls, const char *line, const size_t sz)
{
	if (ls->st == ST_GEN)
	{
		if (handle_gen_st(ls, line, sz))
			return (1);
	}
	else
		handle_other_st(ls);
	if (ls->type == CHAR_NULL)
	{
		if (ls->j > 0)
		{
			ls->tok->data[ls->j] = '\0';
			ls->j = 0;
		}
	}
	return (0);
}

/* lexer main functions, get the tokens */
int	lexer_build(const char *line, const size_t sz, t_lexer *lex)
{
	t_lexsup	ls;
	int			ret;

	lex->n_toks = 0;
	if (g_sh.is_expd == FALSE)
		g_sh.tokdel = FALSE;
	if (sz == 0 || init_ls(&ls, lex, sz) == 1)
		return (0);
	while (1)
	{
		if (ls.i > (int)sz)
			break ;
		ls.c = line[ls.i];
		ls.type = get_ctype(ls.c);
		if (process_char(&ls, line, sz))
			return (0);
		ls.i++;
		if (ls.c == '\0')
			break ;
	}
	ret = process_tokens(lex);
	if (ret == -1)
		return (-1);
	lex->n_toks += ret;
	return (lex->n_toks);
}
