/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 13:55:41 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* check token if token is empty or NULL */
static int	check_tok(t_lexer *lex, t_tok **cur, t_tok *prev)
{
	if (*cur == NULL)
		return (1);
	if (ft_strlen((*cur)->data) <= 0)
	{
		if (prev == NULL)
			lex->tok_lst = (*cur)->next;
		else
			prev->next = (*cur)->next;
		free((*cur)->data);
		free(*cur);
		if (prev == NULL)
			*cur = lex->tok_lst;
		else
			*cur = prev->next;
		return (1);
	}
	return (0);
}

/* parse tokens */
static int	parse_tokens(t_tok *tok, t_tok *prev, t_lexer *lex)
{
	char	*trimed;
	int		cnt;
	int		is_heredoc;

	is_heredoc = 0;
	cnt = 0;
	while (tok)
	{
		if (tok->type == TOK)
		{
			if (handle_expand(tok))
				return (0);
			if (is_heredoc == 0 && handle_wildcards(&tok, prev, lex))
				return (0);
			if (check_tok(lex, &tok, prev))
				continue ;
			trimed = (char *)malloc(ft_strlen(tok->data) + 1);
			if (trimed == NULL)
				return (perror_ret("fatal error", 0));
			trim_quotes(trimed, tok->data);
			free(tok->data);
			tok->data = trimed;
			cnt++;
		}
		if (prev && prev->type == CHAR_LS && tok->type == CHAR_LS)
			is_heredoc = 1;
		else
			is_heredoc = 0;
		prev = tok;
		tok = tok->next;
	}
	return (cnt);
}

/* process tokens */
static int	process_tokens(t_lexer *lex)
{
	t_tok	*tok;
	t_tok	*prev;
	int		cnt;

	prev = NULL;
	tok = lex->tok_lst;
	cnt = parse_tokens(tok, prev, lex);
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
	if (init_ls(&ls, lex, sz) == 1)
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
	lex->n_toks = process_tokens(lex);
	return (lex->n_toks);
}
