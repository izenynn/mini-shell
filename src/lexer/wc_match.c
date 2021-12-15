/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 01:36:11 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 13:19:19 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* This function will be called multiple times while we iterate through the wildcard */
static int	wc_match_fragment(const char **frag, const char **tgt,
								const char *tgt_end, int *st)
{
	const char	*f;
	const char	*t;

	f = *frag;
	t = *tgt;
	while (*f && (*f != '*' || *st != ST_GEN) && t < tgt_end)
	{
		//////////////////////////////////////
		if (*st == ST_GEN && (*f == CHAR_QOUTE || *f == CHAR_DQOUTE))
		{
			//printf("quo\n");
			//printf("f: %c, t: %c\n", *f, *t);
			if (*f == CHAR_QOUTE)
				*st = ST_IN_QUOTE;
			else if (*f == CHAR_DQOUTE)
				*st = ST_IN_DQUOTE;
			f++;
		}
		if ((*st == ST_IN_QUOTE && *f == CHAR_QOUTE)
			|| (*st == ST_IN_DQUOTE && *f == CHAR_DQOUTE))
		{
			//printf("quont\n");
			//printf("f: %c, t: %c\n", *f, *t);
			*st = ST_GEN;
			f++;
			if (*f == '*')
				break ;
		}
		//printf("f: %c, t: %c\n", *f, *t);
		//////////////////////////////////////
		if (*f == '?' && *st == ST_GEN)
			f++;
		else //if (*f != '*' || (*f == '*' && *st != ST_GEN))
		{
			if (*f != *t)
				return (0);
			f++;
		}
		t++;
	}
	if (!*f || (*f == '*' && *st == ST_GEN))
	{
		*frag = f;
		*tgt = t;
		return (1);
	}
	return (0);
}

/* This function is the one that handles the matches:
 * It'll iterate through the wildcard and the target and will call
 * multiple times the function that matches fragment.
 * It'll return 0 in case that there is no match and 1 in case
 * we got a match
 */
static int	wc_match_inner(const char *wc, const char *tgt, size_t tgt_len)
{
	const char	*stgt;
	const char	*swc;
	const char	*tgt_end;
	int			ret;
	int			st;

	///////////////////////////////
	st = ST_GEN;
	/*if (st == ST_GEN && (*wc == CHAR_QOUTE || *wc == CHAR_DQOUTE))
		st = ST_IN_QUOTE;
	else if (st != ST_GEN && (*wc == CHAR_QOUTE || *wc == CHAR_DQOUTE))
	{
		wc++;
		st = ST_GEN;
	}*/
	/////////////////////////////////
	tgt_end = tgt + tgt_len;
	if (*wc != '*')
	{
		//printf("1\n");
		ret = wc_match_fragment(&wc, &tgt, tgt_end, &st);
		if (ret <= 0)
			return (ret);
		//printf("2\n");
	}
	while (*wc)
	{
		//printf("3\n");
		// refactor this while
		///////////////////////////////
		/*if (st == ST_GEN && (*wc == CHAR_QOUTE || *wc == CHAR_DQOUTE))
			st = ST_IN_QUOTE;
		else if (st != ST_GEN && (*wc == CHAR_QOUTE || *wc == CHAR_DQOUTE))
		{
			wc++;
			st = ST_GEN;
		}*/
		///////////////////////////////
		//printf("%s\n", wc);
		while (*wc == '*')
			wc++;
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
		//
		if (ret > 0)
			continue ;
		return (0);
	}
	return (tgt == tgt_end);
}

int	wc_match(const char *wildcard, const char *target)
{
	//printf("\n");
	return (wc_match_inner(wildcard, target, strlen(target)));
}
