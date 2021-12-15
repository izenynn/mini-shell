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

static int wc_match_inner(const char *wc, const char *tgt, size_t tgt_len)
{
	(void)wc;
	(void)tgt;
	(void)tgt_len;
	return (0);
}

int	wc_match(const char *wildcard, const char *target)
{
    return wc_match_inner(wildcard, target, strlen(target));
}
