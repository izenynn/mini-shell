/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:11:33 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/08 18:19:04 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static int	handle_expand(t_tok *tok, int start, int st)
{
	int		end;
	int		is_curly;
	char	*name;
	char	*value;
	char	*res;

	is_curly = 0;
	end = start;
	if (tok->data[start] == '?')
	{
		name = ft_strdup("?");
		value = ft_itoa(g_sh.status);
	}
	else if (tok->data[start] == '=')
	{
		name = ft_strdup("");
		value = ft_strdup("\'$\'");
	}
	else
	{
		if (tok->data[end] == '{' && ++end)
		{
			if (tok->data[end] == '}')
				return (error_ret("error: bad substitution\n", 1));
			is_curly = 1;
		}
		while (tok->data[end] != '\0')
		{
			if (is_curly && !ft_isalnum(tok->data[end]) && tok->data[end] != '_'
				&& tok->data[end] != '}')
				return (error_ret("error: bad substitution\n", 1));
			if (st == ST_GEN)
			{
				if (!ft_isalnum(tok->data[end]) && tok->data[end] != '_')
					break ;
			}
			else if (st == ST_IN_DQUOTE)
			{
				if (!ft_isalnum(tok->data[end]) && tok->data[end] != '_')
					break ;
			}
			end++;
		}
		if (is_curly == 1 && tok->data[end] != '}')
			return (error_ret("error: bad substitution\n", 1));
		name = ft_substr(tok->data, start + is_curly, end - start - is_curly);
		if (start + is_curly == end)
			value = ft_strdup("\'$\'");
		else
			value = ft_getenv(name);
	}
	if (value == NULL)
		value = ft_strdup("");
	res = (char *)ft_calloc(sizeof(char),
			ft_strlen(tok->data) - ft_strlen(name) + ft_strlen(value) - is_curly * 2);
	if (res == NULL)
		perror_ret("malloc", 1);
	strncpy(res, tok->data, start - 1);
	strcat(res, value);
	strcat(res, tok->data + start + ft_strlen(name) + (is_curly * 2));
	free(name);
	free(value);
	free(tok->data);
	tok->data = res;
	return (0);
}

int	expand(t_tok *tok)
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
				if (handle_expand(tok, i + 1, st))
					return (1);
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
				if (handle_expand(tok, i + 1, st))
					return (1);
				st = ST_GEN;
				i = -1;
				continue ;
			}
			if (tok->data[i] == CHAR_DQOUTE)
				st = ST_GEN;
		}
	}
	return (0);
}
