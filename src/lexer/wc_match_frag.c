/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_match_frag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 20:31:03 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 01:41:49 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static const char	*handle_quotes(int *st, const char *f)
{
	if (*st == ST_GEN && (*f == CHAR_QOUTE || *f == CHAR_DQOUTE))
	{
		if (*f == CHAR_QOUTE)
			*st = ST_IN_QUOTE;
		else if (*f == CHAR_DQOUTE)
			*st = ST_IN_DQUOTE;
		f++;
	}
	return (f);
}

static int	wc_match_fragment_qmark(const char **f, const char **t, int *st)
{
	if (**f == '?' && *st == ST_GEN)
		(*f)++;
	else
	{
		if (**f != **t)
			return (0);
		(*f)++;
	}
	return (1);
}

static void	wc_match_fragment_end(const char **frag, const char **tgt,
		const char *f, const char *t)
{
	*frag = f;
	*tgt = t;
}

/*
 * This function will be called multiple times while we iterate
 * through the wildcard
 */
int	wc_match_fragment(const char **frag, const char **tgt,
		const char *tgt_end, int *st)
{
	const char	*f;
	const char	*t;

	f = *frag;
	t = *tgt;
	while (*f && (*f != '*' || *st != ST_GEN) && t < tgt_end)
	{
		f = handle_quotes(st, f);
		if ((*st == ST_IN_QUOTE && *f == CHAR_QOUTE)
			|| (*st == ST_IN_DQUOTE && *f == CHAR_DQOUTE))
		{
			*st = ST_GEN;
			if (*(++f) == '*')
				break ;
		}
		if (wc_match_fragment_qmark(&f, &t, st) == 0)
			return (0);
		t++;
	}
	if (!*f || (*f == '*' && *st == ST_GEN))
	{
		wc_match_fragment_end(frag, tgt, f, t);
		return (1);
	}
	return (0);
}
