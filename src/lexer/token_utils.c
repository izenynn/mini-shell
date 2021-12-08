/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 14:04:10 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/08 17:28:13 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* detroy toks (recursive) */
void	tok_del(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_del(tok->next);
		free(tok);
	}
}

/* initialise token */
int	tok_init(t_tok *tok, size_t sz)
{
	tok->data = (char *)malloc((sz + 2) * sizeof(char));
	if (tok->data == NULL)
		perror_ret("malloc", 1);
	tok->data[0] = '\0';
	tok->type = CHAR_NULL;
	tok->next = NULL;
	return (0);
}
