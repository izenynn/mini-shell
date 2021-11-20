/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 18:03:15 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 12:01:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* test all job in order */
t_ast	*job(void)
{
	t_tok	*save;
	t_ast	*new_node;

	save = g_sh.tok;
	g_sh.tok = save;
	new_node = job_1();
	if (new_node != NULL)
		return (new_node);
	g_sh.tok = save;
	new_node = job_2();
	if (new_node != NULL)
		return (new_node);
	return (NULL);
}

/* <command> '|' <job> */
t_ast	*job_1(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_nd;
	t_ast	*res;

	cmd_nd = cmd();
	if (cmd_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_PIPE, NULL))
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	job_nd = job();
	if (job_nd == NULL)
	{
		ast_del(cmd_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_PIPE);
	ast_attach(res, cmd_nd, job_nd);
	return (res);
}

/* <command> */
t_ast	*job_2(void)
{
	return (cmd());
}
