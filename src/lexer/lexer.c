/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/14 15:56:48 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh/lexer.h"
#include "sh/utils.h"
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
	tok->data = (char *)malloc((sz + 1) * sizeof(char));
	if (!tok->data)
		perror_exit("malloc");
	tok->data[0] = '\0';
	tok->type = CHAR_NULL;
	tok->next = NULL;
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
	int		i, j, k;

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

	/* copy to data */
	i = 0;
	j = 0;
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
				st = ST_IN_QUOTE;
				tok->data[j++] = CHAR_QOUTE;
				tok->type = TOK;
			}
			else if (ctype == CHAR_DQOUTE)
			{
				st = ST_IN_DQUOTE;
				tok->data[j++] = CHAR_DQOUTE;
				tok->type = TOK;
			}
			else if (ctype == CHAR_ESCSEQ)
			{
				tok->data[j++] = line[++i];
				tok->type = TOK;
			}
			else if (ctype == CHAR_GEN)
			{
				tok->data[j++] = c;
				tok->type = TOK;
			}
			else if (ctype == CHAR_WS)
			{
				/* new token */
				if (j > 0)
				{
					tok->data[j] = 0;
					tok->next = (t_tok *)malloc(sizeof(t_tok));
					if (!tok->next)
						perror_exit("malloc");
					tok = tok->next;
					init_tok(tok, sz - i);
					j = 0;
				}
			}
			else if (ctype == CHAR_SC || ctype == CHAR_GT || ctype == CHAR_LS
				|| ctype == CHAR_AMP || ctype == CHAR_PIPE)
			{
				/* end previous token */
				if (j > 0)
				{
					tok->data[j] = '\0';
					tok->next = (t_tok *)malloc(sizeof(t_tok));
					if (!tok->next)
						perror_exit("malloc");
					tok = tok->next;
					init_tok(tok, sz - i);
					j = 0;
				}
				/* create special char token */
				tok->data[0] = ctype;
				tok->data[1] = '\0';
				tok->type = ctype;
				tok->next = (t_tok *)malloc(sizeof(t_tok));
				tok = tok->next;
				init_tok(tok, sz - i);
			}
		}
		else if (st == ST_IN_QUOTE)
		{
			tok->data[j++] = c;
			if (ctype == CHAR_QOUTE)
				st = ST_GEN;
		}
		else if (st == ST_IN_DQUOTE)
		{
			tok->data[j++] = c;
			if (ctype == CHAR_DQOUTE)
				st = ST_GEN;
		}
		/* if null */
		if (ctype == CHAR_NULL)
		{
			if (j > 0)
			{
				tok->data[j] = '\0';
				j = 0;
			}
		}
		/* increment i */
		i++;
		/* do {} while () */
		if (c == '\0')
			break ;
	}

	/* create token */
	tok = lex->tok_lst;
	k = 0;
	/*while (tok)
	{
		if (tok->type == TOKEN)
		{
			;
		}
		tok = tok->next;
	}*/
	/* set number of tokens */
	lex->n_toks = k;
	return (0);
}
