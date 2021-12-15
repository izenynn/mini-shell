/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:36:11 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 01:52:57 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static int wc_match_fragment(const char **frag, const char **tgt, const char *tgt_end)
{
	const char *f;
	const char *t;

	f = *frag;
	t = *tgt;
	while (*f && *f != '*' && t < tgt_end)
	{
		if (*f != *t)
			return (0);
		f++;
		t++;
	}
	if (!*f || *f == '*')
	{
		*frag = f;
		*tgt = t;
		return (1);
	}
	return (0);
}

static int wc_match_inner(const char *wc, const char *tgt, size_t tgt_len)
{
	const char 	*stgt;
	const char	*swc;
	const char	*tgt_end;
	int			ret;

	tgt_end = tgt + tgt_len;
	if (*wc != '*')
	{
		ret = wc_match_fragment(&wc, &tgt, tgt_end);
		if (ret <= 0)
			return (ret);
	}
	while (*wc)
	{
		while (*wc == '*')
			wc++;
		if (!*wc)
			return (1);
		ret = 0;
		while (*tgt)
		{
			swc = wc;
			stgt = tgt;
			ret = wc_match_fragment(&wc, &tgt, tgt_end);
			if (ret < 0)
				return (ret);
			if (ret > 0 && !*wc && tgt != tgt_end)
			{
				tgt = tgt_end - (tgt - stgt);
				wc = swc;
				return (wc_match_fragment(&wc, &tgt, tgt_end));
			}
			if (ret > 0)
				break ;
			tgt++;
		}
		if (ret > 0)
			continue;
		return (0);
	}
	return (tgt == tgt_end);
}

int	wc_match(const char *wildcard, const char *target)
{
    return (wc_match_inner(wildcard, target, strlen(target)));
}
