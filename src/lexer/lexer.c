/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/13 12:59:21 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh/lexer.h"
#include <sh.h>

/* get char type */
static int	get_ctype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
	 	return (CHAR_DQOUTE);
	else if (c == '|')
	 	return (CHAR_PIPE);
	else if (c == '&')
	 	return (CHAR_AMP);
	else if (c == ' ')
	 	return (CHAR_WS);
	else if (c == ';')
	 	return (CHAR_SC);
	else if (c == '\\')
	 	return (CHAR_ESCSEQ);
	else if (c == '\t')
	 	return (CHAR_TAB);
	else if (c == '\n')
	 	return (CHAR_NL);
	else if (c == '>')
	 	return (CHAR_GT);
	else if (c == '<')
	 	return (CHAR_LS);
	else if (c == '\0')
		return (CHAR_NULL);
	return (CHAR_GEN);
}

/* initialise all tok vars at NULL (0) */
static void	init_tok(t_tok *tok, size_t sz)
{
	tok->data = (char *)ft_calloc(sz + 1, sizeof(char));
}

/* detroy toks (recursive) */
/*static void	destroy_tok(t_tok *tok)
{
	if (tok)
	{
		free(tok->data);
		destroy_tok(tok->next);
		free(tok);
	}
}*/

/* build lexer */
int	lexer_build(char *line, size_t sz, t_lexer *lex)
{
	t_tok	*tok;
	char	c;
	int		ctype;
	int		st;
	int		i;

	/* check len */
	lex->n_toks = 0;
	if (sz == 0)
		return (0);

	lex->tok_lst = (t_tok *)ft_calloc(1, sizeof(t_tok));

	/* allocate first token */
	tok = lex->tok_lst;
	init_tok(tok, sz);

	/* initialise state */
	st = ST_GEN;

	i = 0;
	while (1)
	{
		/* get char type */
		c = line[i];
		ctype = get_ctype(c);
		/* if based on char type */
		if (st == ST_GEN)
		{
			if (ctype == CHAR_QOUTE)
			{
				;
			}
			else if (ctype == CHAR_DQOUTE)
			{
				;
			}
			else if (ctype == CHAR_ESCSEQ)
			{
				;
			}
			else if (ctype == CHAR_GEN)
			{
				;
			}
			else if (ctype == CHAR_WS)
			{
				;
			}
			else if (ctype == CHAR_SC || ctype == CHAR_GT || ctype == CHAR_LS
				|| ctype == CHAR_AMP || ctype == CHAR_PIPE)
			{
				;
			}
		}
		else if (st == ST_IN_QUOTE)
		{
			;
		}
		else if (st == ST_IN_DQUOTE)
		{
			;
		}
		/* if null */
		if (ctype == CHAR_NULL)
		{
			;
		}
		/* increment i */
		i++;
		/* do {} while () */
		if (c == '\0')
			break ;
	}

	/* token */

	return (0);
}
