/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:36:11 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 19:30:16 by                  ###   ########.fr       */
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
static int	wc_match_fragment(const char **frag, const char **tgt,
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

static void	skip_asterisks(const char **wc)
{
	while (**wc == '*')
		(*wc)++;
}

static int	wc_match_inner_init(int *st, const char **wc,
							   const char **tgt, const char **tgt_end)
{
	int	ret;

	*st = ST_GEN;
	*tgt_end = *tgt + ft_strlen(*tgt);
	if (**wc != '*')
	{
		ret = wc_match_fragment(wc, tgt, *tgt_end, st);
		if (ret <= 0)
			return (ret);
	}
	return (1);
}

/*
 * This function is the one that handles the matches:
 * It'll iterate through the wildcard and the target and will call
 * multiple times the function that matches fragment.
 * It'll return 0 in case that there is no match and 1 in case
 * we got a match
 */
static int	wc_match_inner(const char *wc, const char *tgt)
{
	const char	*stgt;
	const char	*swc;
	const char	*tgt_end;
	int			ret;
	int			st;

	if (wc_match_inner_init(&st, &wc, &tgt, &tgt_end) <= 0)
		return (0);
	while (*wc)
	{
		skip_asterisks(&wc);
		if (!*wc)
			return (1);
		ret = 0;
		while (*tgt)
		{
			swc = wc;
			stgt = tgt;
			ret = wc_match_fragment(&wc, &tgt, tgt_end, &st);
			if (ret < 0)
				return (ret);
			if (ret > 0 && !*wc && tgt != tgt_end)
			{
				tgt = tgt_end - (tgt - stgt);
				wc = swc;
				return (wc_match_fragment(&wc, &tgt, tgt_end, &st));
			}
			if (ret > 0)
				break ;
			tgt++;
		}
		if (ret > 0)
			continue ;
		return (0);
	}
	return (tgt == tgt_end);
}

int	wc_match(const char *wildcard, const char *target)
{
	return (wc_match_inner(wildcard, target));
}
