/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:57:55 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/30 19:12:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* is a terminal special character ? */
int	is_term(int type, char **buff)
{
	if (g_sh.tok == NULL)
		return (0);
	if (g_sh.tok->type == type)
	{
		if (buff != NULL)
		{
			*buff = (char *)malloc(
					(ft_strlen(g_sh.tok->data) + 1) * sizeof(char));
			if (*buff == NULL)
				perror_ret("malloc", 0);
			ft_strcpy(*buff, g_sh.tok->data);
		}
		g_sh.tok = g_sh.tok->next;
		return (1);
	}
	g_sh.tok = g_sh.tok->next;
	return (0);
}
