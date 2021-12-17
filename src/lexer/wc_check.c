/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 01:12:39 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 01:18:23 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle quotes */
static void	handle_quotes(int *st, char **wc)
{
	if (*st == ST_GEN && (**wc == CHAR_QOUTE || **wc == CHAR_DQOUTE))
	{
		if (**wc == CHAR_QOUTE)
			*st = ST_IN_QUOTE;
		else if (**wc == CHAR_DQOUTE)
			*st = ST_IN_DQUOTE;
		(*wc)++;
	}
}

/* check if a token contains a wildcard */
int	wc_check(t_tok *tok)
{
	int		st;
	char	*wc;

	if (tok->data == NULL)
		return (1);
	st = ST_GEN;
	wc = tok->data;
	while (*wc != '\0')
	{
		handle_quotes(&st, &wc);
		if ((st == ST_IN_QUOTE && *wc == CHAR_QOUTE)
			|| (st == ST_IN_DQUOTE && *wc == CHAR_DQOUTE))
		{
			st = ST_GEN;
			wc++;
		}
		if (st == ST_GEN && (*wc == '?' || *wc == '*'))
			return (1);
		wc++;
	}
	return (0);
}
