/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:44:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 14:07:51 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* lexer main functions, get the tokens */
int	lexer_build(char *line, size_t sz, t_lexer *lex)
{
	t_tok	*tok;
	char	c;
	int		ctype;
	int		st;
	int		i, j;

	/* check len */
	lex->n_toks = 0;
	if (sz == 0)
		return (0);

	lex->tok_lst = (t_tok *)ft_calloc(1, sizeof(t_tok));

	/* allocate first token */
	tok = lex->tok_lst;
	tok_init(tok, sz);

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
					tok_init(tok, sz - i);
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
					tok_init(tok, sz - i);
					j = 0;
				}
				/* create special char token */
				tok->data[0] = ctype;
				tok->data[1] = '\0';
				tok->type = ctype;
				tok->next = (t_tok *)malloc(sizeof(t_tok));
				tok = tok->next;
				tok_init(tok, sz - i);
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
	lex->n_toks = 0;
	while (tok)
	{
		if (tok->type == TOK)
		{
			// TODO here we will handle wildcards and convert then to tokens
			/* trim quotes and double quotes */
			char* trimed = malloc(ft_strlen(tok->data) + 1);
			trim_quotes(trimed, tok->data);
			free(tok->data);
			tok->data = trimed;
			/* set counter */
			lex->n_toks++;
		}
		tok = tok->next;
	}
	/* return number of tokens */
	return (lex->n_toks);
}
