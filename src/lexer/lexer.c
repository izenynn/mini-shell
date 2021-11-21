/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 12:50:52 by dpoveda-         ###   ########.fr       */
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
			trimed = malloc(ft_strlen(tok->data) + 1);
			trim_quotes(trimed, tok->data);
			free(tok->data);
			tok->data = trimed;
			cnt++;
		}
		tok = tok->next;
	}
	return (cnt);
}

/* lexer main functions, get the tokens */
int	lexer_build(const char *line, const size_t sz, t_lexer *lex)
{
	t_lexsup	ls;

	lex->n_toks = 0;
	if (sz == 0)
		return (0);
	lex->tok_lst = (t_tok *)malloc(sizeof(t_tok));
	ls.tok = lex->tok_lst;
	tok_init(ls.tok, sz);
	ls.st = ST_GEN;
	ls.i = 0;
	ls.j = 0;
	while (1)
	{
		ls.c = line[ls.i];
		ls.type = get_ctype(ls.c);
		process_char(&ls, line, sz);
		ls.i++;
		if (ls.c == '\0')
			break ;
	}
	lex->n_toks = process_tokens(lex);
	return (lex->n_toks);
}
