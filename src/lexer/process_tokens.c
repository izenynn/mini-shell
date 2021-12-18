/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:15:12 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 20:46:49 by dpoveda-         ###   ########.fr       */
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

/* expand variables and wildcards */
static int	handle_expand_and_wc(t_lexer *lex, t_toksup *ts)
{
	int		ret;

	if (ts->semaphore == 0 && g_sh.is_expd == FALSE)
	{
		g_sh.is_expd = TRUE;
		g_sh.prev = ts->prev;
		ret = handle_expand(&ts->aux, &ts->prev, lex, ts);
		g_sh.is_expd = FALSE;
		if (ret == 1)
			return (-1);
		if (check_tok(lex, &ts->aux, ts->prev))
		{
			g_sh.tokdel = TRUE;
			return (1);
		}
	}
	if (ts->semaphore > 0 && g_sh.is_expd == FALSE)
		ts->semaphore--;
	ret = handle_wildcards(&ts->aux, &ts->prev, lex);
	if (ret == -1)
		return (-1);
	else if (ret == 1)
		return (1);
	return (5);
}

/* handle a TOK type token process */
static int	handle_tok_token(t_lexer *lex, t_toksup *ts)
{
	char	*trimed;
	int		ret;

	if (ts->is_heredoc == 0)
	{
		ret = handle_expand_and_wc(lex, ts);
		if (ret != 5)
			return (ret);
	}
	if (g_sh.is_expd == FALSE)
	{
		trimed = (char *)malloc(ft_strlen(ts->aux->data) + 1);
		if (trimed == NULL)
			return (perror_ret("malloc", -1));
		trim_quotes(trimed, ts->aux->data);
		free(ts->aux->data);
		ts->aux->data = trimed;
	}
	ts->cnt++;
	return (2);
}

/* parse tokens */
static int	parse_tokens(t_tok *tok, t_tok *prev, t_lexer *lex, t_toksup *ts)
{
	int			ret;

	ts->aux = tok;
	ts->prev = prev;
	ts->is_heredoc = 0;
	ts->cnt = 0;
	ts->semaphore = 0;
	while (ts->aux)
	{
		if (ts->aux->type == TOK)
		{
			ret = handle_tok_token(lex, ts);
			if (ret <= 0)
				return (ret);
			else if (ret == 1)
				continue ;
		}
		if (ts->prev && ts->prev->type == CHAR_LS && ts->aux->type == CHAR_LS)
			ts->is_heredoc = 1;
		else
			ts->is_heredoc = 0;
		ts->prev = ts->aux;
		ts->aux = ts->aux->next;
	}
	return (ts->cnt);
}

/* process tokens */
int	process_tokens(t_lexer *lex)
{
	t_toksup	ts;
	t_tok		*tok;
	t_tok		*prev;
	int			cnt;

	prev = NULL;
	tok = lex->tok_lst;
	cnt = parse_tokens(tok, prev, lex, &ts);
	return (cnt);
}
