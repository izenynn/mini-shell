/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_gen_st.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 12:37:01 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 20:59:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* on general state handle quotes */
static void	on_gen_st_quotes(t_lexsup *ls)
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
	else if (ls->type == CHAR_OCL)
	{
		ls->st = ST_IN_CURLY;
		ls->tok->data[ls->j++] = CHAR_OCL;
		ls->tok->type = TOK;
	}
}

/* on general state handle withe spaces */
static int	on_gen_st_ws(t_lexsup *ls, const size_t sz)
{
	if (ls->j > 0)
	{
		ls->tok->data[ls->j] = 0;
		ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
		if (ls->tok->next == NULL)
			perror_ret("malloc", 1);
		ls->tok = ls->tok->next;
		if (tok_init(ls->tok, sz - ls->i))
			return (1);
		ls->j = 0;
	}
	return (0);
}

/* on general state handle special characters */
static int	on_gen_st_sp(t_lexsup *ls, const size_t sz)
{
	if (ls->j > 0)
	{
		ls->tok->data[ls->j] = '\0';
		ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
		if (!ls->tok->next)
			perror_ret("malloc", 1);
		ls->tok = ls->tok->next;
		if (tok_init(ls->tok, sz - ls->i))
			return (1);
		ls->j = 0;
	}
	ls->tok->data[0] = ls->type;
	ls->tok->data[1] = '\0';
	ls->tok->type = ls->type;
	ls->tok->next = (t_tok *)malloc(sizeof(t_tok));
	ls->tok = ls->tok->next;
	if (tok_init(ls->tok, sz - ls->i))
		return (1);
	return (0);
}

static int	on_gen_st_esc(t_lexsup *ls, const char *line)
{
	ls->tok->data[ls->j++] = line[++ls->i];
	ls->tok->type = TOK;
	return (0);
}

/* on general state */
int	handle_gen_st(t_lexsup *ls, const char *line, const size_t sz)
{
	if (ls->type == CHAR_QOUTE || ls->type == CHAR_DQOUTE
		|| ls->type == CHAR_OCL)
		on_gen_st_quotes(ls);
	else if (ls->type == CHAR_ESCSEQ)
		on_gen_st_esc(ls, line);
	else if (ls->type == CHAR_GEN)
	{
		ls->tok->data[ls->j++] = ls->c;
		ls->tok->type = TOK;
	}
	else if (ls->type == CHAR_WS || ls->type == CHAR_TAB)
	{
		if (on_gen_st_ws(ls, sz))
			return (1);
	}
	else if (ls->type == CHAR_SC || ls->type == CHAR_GT || ls->type == CHAR_LS
		|| ls->type == CHAR_AMP || ls->type == CHAR_PIPE
		|| ls->type == CHAR_OPR || ls->type == CHAR_CPR)
	{
		if (on_gen_st_sp(ls, sz))
			return (1);
	}
	return (0);
}
