/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 16:45:28 by dpoveda-         ###   ########.fr       */
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
			// TODO here we will handle wildcards and convert then to tokens
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

/* on general state */
static void	on_gen_st(t_lexsup *ls, const char *line, const size_t sz)
{
	if (ls->type == CHAR_QOUTE)
	{
		ls->st = ST_IN_QUOTE;
		ls->tok->data[ls->j++] = CHAR_QOUTE;
		ls->tok->type = TOK;
	}
	else if (ls->type == CHAR_DQOUTE)
	{
		ls->st = ST_IN_DQUOTE;
		ls->tok->data[ls->j++] = CHAR_DQOUTE;
		ls->tok->type = TOK;
	}
	else if (ls->type == CHAR_ESCSEQ)
	{
		ls->tok->data[ls->j++] = line[++ls->i];
		ls->tok->type = TOK;
	}
	else if (ls->type == CHAR_GEN)
	{
		ls->tok->data[ls->j++] = ls->c;
		ls->tok->type = TOK;
	}
	else if (ls->type == CHAR_WS)
	{
		if (ls->j > 0)
		{
			ls->tok->data[ls->j] = 0;
			ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
			if (!ls->tok->next)
				perror_exit("malloc");
			ls->tok = ls->tok->next;
			tok_init(ls->tok, sz - ls->i);
			ls->j = 0;
		}
	}
	else if (ls->type == CHAR_SC || ls->type == CHAR_GT
		|| ls->type == CHAR_LS || ls->type == CHAR_AMP || ls->type == CHAR_PIPE)
	{
		if (ls->j > 0)
		{
			ls->tok->data[ls->j] = '\0';
			ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
			if (!ls->tok->next)
				perror_exit("malloc");
			ls->tok = ls->tok->next;
			tok_init(ls->tok, sz - ls->i);
			ls->j = 0;
		}
		ls->tok->data[0] = ls->type;
		ls->tok->data[1] = '\0';
		ls->tok->type = ls->type;
		ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
		ls->tok = ls->tok->next;
		tok_init(ls->tok, sz - ls->i);
	}
}

/* process line character */
static void	process_char(t_lexsup *ls, const char *line, const size_t sz)
{
	if (ls->st == ST_GEN)
		on_gen_st(ls, line, sz);
	else if (ls->st == ST_IN_QUOTE)
	{
		ls->tok->data[ls->j++] = ls->c;
		if (ls->type == CHAR_QOUTE)
			ls->st = ST_GEN;
	}
	else if (ls->st == ST_IN_DQUOTE)
	{
		ls->tok->data[ls->j++] = ls->c;
		if (ls->type == CHAR_DQOUTE)
			ls->st = ST_GEN;
	}
	if (ls->type == CHAR_NULL)
	{
		if (ls->j > 0)
		{
			ls->tok->data[ls->j] = '\0';
			ls->j = 0;
		}
	}
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
