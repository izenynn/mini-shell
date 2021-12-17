/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:33 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 23:02:38 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle general state */
static int	gen_st(t_tok *tok, int *st, int *len, int i)
{
	if (tok->data[i] == CHAR_DL)
	{
		if (expand(tok, i + 1, *st))
			return (1);
		*len = ft_strlen(tok->data);
	}
	else if (tok->data[i] == CHAR_QOUTE)
		*st = ST_IN_QUOTE;
	else if (tok->data[i] == CHAR_DQOUTE)
		*st = ST_IN_DQUOTE;
	return (0);
}

/* handle other states */
static int	other_st(t_tok *tok, int *st, int *len, int i)
{
	if (*st == ST_IN_QUOTE)
	{
		if (tok->data[i] == CHAR_QOUTE)
			*st = ST_GEN;
	}
	else if (*st == ST_IN_DQUOTE)
	{
		if (tok->data[i] == CHAR_DL)
		{
			if (expand(tok, i + 1, *st))
				return (1);
			*st = ST_GEN;
			*len = ft_strlen(tok->data);
		}
		else if (tok->data[i] == CHAR_DQOUTE)
			*st = ST_GEN;
	}
	return (0);
}

/* build tokens for new expanded token */
static void	re_lexer_build(t_tok **tok, t_tok **prev, t_lexer *lex)
{
	t_lexer	tmp;
	t_tok	*aux;

	if (lexer_build((*tok)->data, ft_strlen((*tok)->data), &tmp) <= 0)
		return ;
	aux = tmp.tok_lst;
	while (aux != NULL)
		aux = aux->next;
	insert_toklst(tok, prev, lex, tmp.tok_lst);
}

/* handle variables expand */
int	handle_expand(t_tok **tok, t_tok **prev, t_lexer *lex)
{
	int		st;
	int		i;
	int		len;

	st = ST_GEN;
	len = ft_strlen((*tok)->data);
	i = -1;
	while (i < len && (*tok)->data[++i] != '\0')
	{
		if (st == ST_GEN)
		{
			gen_st(*tok, &st, &len, i);
		}
		else
		{
			other_st(*tok, &st, &len, i);
		}
	}
	re_lexer_build(tok, prev, lex);
	return (0);
}
