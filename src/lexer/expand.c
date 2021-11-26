/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:33 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 14:43:01 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_str.h"
#include <sh.h>

void	expand_var(t_tok *tok, int start, int st)
{
	int		end;
	char	*name;
	char	*value;
	char	*res;

	end = start;
	if (tok->data[end] == '?')
	{
		name = ft_strdup("?");
		value = ft_itoa(g_sh.status);
	}
	else
	{
		while (tok->data[end] != '\0')
		{
			if (st == ST_GEN)
			{
				if (tok->data[end] == CHAR_QOUTE || tok->data[end] == CHAR_DQOUTE
					|| tok->data[end] == CHAR_DL)
					break ;
			}
			else if (st == ST_IN_DQUOTE)
			{
				if (tok->data[end] == CHAR_DQOUTE || tok->data[end] == CHAR_QOUTE
					|| tok->data[end] == CHAR_DL)
					break ;
			}
			end++;
		}
		name = ft_substr(tok->data, start, end - start);
		value = ft_getenv(name);
	}
	//printf("NAME: %s\n", name);
	if (value == NULL)
		value = ft_strdup("");
	//printf("VALUE: %s\n", value);
	res = (char *)ft_calloc(sizeof(char),
		ft_strlen(tok->data) - ft_strlen(name) + ft_strlen(value));
	strncpy(res, tok->data, start - 1);
	//printf("res: %s\n", res);
	strcat(res, value);
	//printf("res: %s\n", res);
	strcat(res, tok->data + start + ft_strlen(name));
	//printf("res: %s\n", res);
	free(name);
	free(value);
	free(tok->data);
	tok->data = res;
}

void	expand(t_tok *tok)
{
	int		st;
	int		i;

	st = ST_GEN;
	i = -1;
	while (tok->data[++i] != '\0')
	{
		if (st == ST_GEN)
		{
			if (tok->data[i] == CHAR_DL)
			{
				expand_var(tok, i + 1, st);
				i = -1;
				continue ;
			}
			else if (tok->data[i] == CHAR_QOUTE)
				st = ST_IN_QUOTE;
			else if (tok->data[i] == CHAR_DQOUTE)
				st = ST_IN_DQUOTE;
		}
		else if (st == ST_IN_QUOTE)
		{
			if (tok->data[i] == CHAR_QOUTE)
				st = ST_GEN;
		}
		else if (st == ST_IN_DQUOTE)
		{
			if (tok->data[i] == CHAR_DL)
			{
				expand_var(tok, i + 1, st);
				st = ST_GEN;
				i = -1;
				continue ;
			}
			if (tok->data[i] == CHAR_DQOUTE)
				st = ST_GEN;
		}
	}
}
