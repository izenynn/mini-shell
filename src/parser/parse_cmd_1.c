/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:30:53 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/29 15:44:40 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all command in order */
t_ast	*cmd(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;

	g_sh.tok = save;
	new_node = cmd_1();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_2();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_3();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_4();
	if (new_node != NULL)
		return (new_node);

	g_sh.tok = save;
	new_node = cmd_5();
	if (new_node != NULL)
		return (new_node);

	return (NULL);
}
