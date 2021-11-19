/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:23:11 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/19 12:23:20 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* <job> ';' <command line> */
t_ast	*cmd_line_1(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_line_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, cmd_line_nd);
	return (res);
}

/* <job> ';' */
t_ast	*cmd_line_2(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_SC, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, NULL);
	return (res);
}

/* <job> '&' <command line> */
t_ast	*cmd_line_3(void)
{
	t_ast	*job_nd;
	t_ast	*cmd_line_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_AMP, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	cmd_line_nd = cmd_line();
	if (cmd_line_nd == NULL)
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, cmd_line_nd);
	return (res);
}

/* <job> '&' */
t_ast	*cmd_line_4(void)
{
	t_ast	*job_nd;
	t_ast	*res;

	job_nd = job();
	if (job_nd == NULL)
		return (NULL);
	if (!is_term(CHAR_AMP, NULL))
	{
		ast_del(job_nd);
		return (NULL);
	}
	res = (t_ast *)malloc(sizeof(t_ast));
	ast_settype(res, AST_SEQ);
	ast_attach(res, job_nd, NULL);
	return (res);
}

/* <job> */
t_ast	*cmd_line_5(void)
{
	return (job());
}
