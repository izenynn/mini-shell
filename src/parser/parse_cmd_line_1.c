/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:27:32 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 11:17:14 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all command line in order */
t_ast	*cmd_line(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = cmd_line_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_2();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_3();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_4();
	if (new_node)
		return (new_node);
	g_sh.tok = save;
	new_node = cmd_line_5();
	if (new_node)
		return (new_node);
	return (NULL);
}
