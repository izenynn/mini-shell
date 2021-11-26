/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 12:46:53 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* process tokens */
static int	process_tokens(t_lexer *lex)
{
	t_tok	*tok;
	char	*trimed;
	int		cnt;

	tok = lex->tok_lst;
	cnt = 0;
	while (tok)
	{
		if (tok->type == TOK)
		{
			expand(tok);
			// TODO wildcards
			trimed = malloc(ft_strlen(tok->data) + 1);
			if (trimed == NULL)
				return (perror_ret("fatal error", 0));
			trim_quotes(trimed, tok->data);
			free(tok->data);
			tok->data = trimed;
			cnt++;
		}
		tok = tok->next;
	}
	return (cnt);
}

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

	lex->n_toks = 0;
	if (sz == 0)
		return (0);
	lex->tok_lst = (t_tok *)malloc(sizeof(t_tok));
	if (!lex->tok_lst)
		return (perror_ret("fatal error", 0));
	ls.tok = lex->tok_lst;
	tok_init(ls.tok, sz);
	ls.st = ST_GEN;
	ls.i = 0;
	ls.j = 0;
	while (1)
	{
		ls.c = line[ls.i];
		ls.type = get_ctype(ls.c);
		if (process_char(&ls, line, sz))
			return (0);
		ls.i++;
		if (ls.c == '\0')
			break ;
	}
	lex->n_toks = process_tokens(lex);
	return (lex->n_toks);
}
