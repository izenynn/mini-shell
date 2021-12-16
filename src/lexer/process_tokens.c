/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:15:12 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 21:15:32 by dpoveda-         ###   ########.fr       */
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

static int	handle_tok_token(t_lexer *lex, t_toksup *ts)
{
	char	*trimed;

	if (handle_expand(ts->aux))
		return (0);
	if (ts->is_heredoc == 0 && handle_wildcards(&ts->aux, ts->prev, lex))
		return (0);
	if (check_tok(lex, &ts->aux, ts->prev))
		return (1);
	trimed = (char *)malloc(ft_strlen(ts->aux->data) + 1);
	if (trimed == NULL)
		return (perror_ret("fatal error", 0));
	trim_quotes(trimed, ts->aux->data);
	free(ts->aux->data);
	ts->aux->data = trimed;
	ts->cnt++;
	return (-1);
}

/* parse tokens */
static int	parse_tokens(t_tok *tok, t_tok *prev, t_lexer *lex)
{
	t_toksup	ts;
	int			ret;

	ts.aux = tok;
	ts.prev = prev;
	ts.is_heredoc = 0;
	ts.cnt = 0;
	while (ts.aux)
	{
		if (ts.aux->type == TOK)
		{
			ret = handle_tok_token(lex, &ts);
			if (ret == 0)
				return (0);
			else if (ret == 1)
				continue ;
		}
		if (ts.prev && ts.prev->type == CHAR_LS && ts.aux->type == CHAR_LS)
			ts.is_heredoc = 1;
		else
			ts.is_heredoc = 0;
		ts.prev = ts.aux;
		ts.aux = ts.aux->next;
	}
	return (ts.cnt);
}

/* process tokens */
int	process_tokens(t_lexer *lex)
{
	t_tok	*tok;
	t_tok	*prev;
	int		cnt;

	prev = NULL;
	tok = lex->tok_lst;
	cnt = parse_tokens(tok, prev, lex);
	return (cnt);
}
