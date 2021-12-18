/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:59:37 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 20:49:26 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle_expand.c */
static void	special_cases(char c, char **name, char **value)
{
	if (c == '?')
	{
		*name = ft_strdup("?");
		*value = ft_itoa(g_sh.status);
	}
	else if (c == '=')
	{
		*name = ft_strdup("");
		*value = ft_strdup("$");
	}
}

/* is curly */
static int	is_curly(t_expsup *es, t_tok *tok)
{
	int	curly;

	curly = 0;
	if (tok->data[es->end] == '{')
	{
		es->end++;
		if (tok->data[es->end] == '}')
			return (error_ret("error: bad substitution\n", 1));
		curly = 1;
	}
	return (curly);
}

/* get variable name */
static int	get_name(t_expsup *es, t_tok *tok, int *st)
{
	es->curly = is_curly(es, tok);
	while (tok->data[es->end] != '\0')
	{
		if (es->curly && !ft_isalnum(tok->data[es->end])
			&& tok->data[es->end] != '_' && tok->data[es->end] != '}')
			return (error_ret("error: bad substitution\n", 1));
		if (*st == ST_GEN)
		{
			if (!ft_isalnum(tok->data[es->end]) && tok->data[es->end] != '_')
				break ;
		}
		else if (*st == ST_IN_DQUOTE)
		{
			if (!ft_isalnum(tok->data[es->end]) && tok->data[es->end] != '_')
				break ;
		}
		es->end++;
	}
	return (0);
}

/* change token data */
static void	change_data(t_expsup *es, t_tok *tok)
{
	char	*res;
	size_t	size;

	if (es->value == NULL)
		es->value = ft_strdup("");
	size = ft_strlen(tok->data) - ft_strlen(es->name) + ft_strlen(es->value);
	size -= (es->curly * 2);
	res = (char *)ft_calloc(sizeof(char), size);
	if (res == NULL)
		perror_ret("malloc", 1);
	ft_memcpy(res, tok->data, es->start - 1);
	ft_strcat(res, es->value);
	ft_strcat(res,
		tok->data + es->start + ft_strlen(es->name) + (es->curly * 2));
	free(es->name);
	free(es->value);
	free(tok->data);
	tok->data = res;
}

int	expand(t_tok *tok, int *start, int st)
{
	t_expsup	es;

	(*start)++;
	es.curly = 0;
	es.start = *start;
	es.end = *start;
	if (tok->data[*start] == '?' || tok->data[*start] == '=')
		special_cases(tok->data[*start], &es.name, &es.value);
	else
	{
		get_name(&es, tok, &st);
		if (es.curly == 1 && tok->data[es.end] != '}')
			return (error_ret("error: bad substitution\n", 1));
		es.name = ft_substr(tok->data, es.start + es.curly,
				es.end - es.start - es.curly);
		if (es.start + es.curly == es.end)
			es.value = ft_strdup("$");
		else
			es.value = ft_getenv(es.name);
	}
	*start -= 2;
	if (es.value != NULL)
		*start += ft_strlen(es.value);
	change_data(&es, tok);
	return (0);
}
