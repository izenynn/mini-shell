/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:03:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 17:48:48 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* destroy lexer */
void	lexer_del(t_lexer *lex)
{
	if (lex == NULL)
		return ;
	tok_del(lex->tok_lst);
}

/* support for get type func */
static int	get_ctype_2(char c)
{
	if (c == CHAR_OCL)
		return (CHAR_OCL);
	else if (c == CHAR_CCL)
		return (CHAR_CCL);
	return (CHAR_GEN);
}

/* get char type */
int	get_ctype(char c)
{
	if (c == '\'')
		return (CHAR_QOUTE);
	else if (c == '\"')
		return (CHAR_DQOUTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMP);
	else if (c == ' ')
		return (CHAR_WS);
	else if (c == ';')
		return (CHAR_SC);
	else if (c == '\\')
		return (CHAR_ESCSEQ);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NL);
	else if (c == '>')
		return (CHAR_GT);
	else if (c == '<')
		return (CHAR_LS);
	else if (c == '\0')
		return (CHAR_NULL);
	return (get_ctype_2(c));
}

/* trim quotes and double quotes */
void	trim_quotes(char *dst, char *src)
{
	int		i;
	int		j;
	int		len;
	char	l_quote;

	len = ft_strlen(src);
	if (len <= 1)
	{
		ft_strcpy(dst, src);
		return ;
	}
	l_quote = 0;
	i = -1;
	j = 0;
	while (++i < len)
	{
		if ((src[i] == '\'' || src[i] == '\"') && l_quote == 0)
			l_quote = src[i];
		else if (src[i] == l_quote)
			l_quote = 0;
		else
			dst[j++] = src[i];
	}
	dst[j] = 0;
}
