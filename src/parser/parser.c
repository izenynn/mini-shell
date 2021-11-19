/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:22 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/19 11:44:52 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
 * Grammar
 *
 * <command line>		:	<job> ';' <command line>
 * 						|	<job> ';'
 * 						|	<job> '&' <command line>
 * 						|	<job> '&'
 * 						|	<job>
 * 						;
 *
 * <job>				:	<command> '|' <job>
 * 						|	<command>
 * 						;
 *
 * <command>			:	<simple command> '<' <file>
 * 						|	<simple command> '>' <file>
 * 						|	<simple command>
 * 						;
 *
 * <simple command>		:	<name> <token list>
 * 						;
 *
 * <token list>			:	<token> <token list>
 * 						|	(null)
 * 						;
 *
 */

/*
 * Create an ast recursively:
 *
 * cmd_line()		=>	test all command line in order
 * cmd_line_1()		=>	<job> ';' <command line>
 * cmd_line_2()		=>	<job> ';'
 * cmd_line_3()		=>	<job> '&' <command line>
 * cmd_line_4()		=>	<job> '&'
 * cmd_line_5()		=>	<job>
 *
 * job()			=>	test all job in order
 * job_1()			=>	<command> '|' <job>
 * job_2()			=>	<command>
 *
 * cmd()			=>	test all command in order
 * cmd_1()			=>	<simple command> '<' <file>
 * cmd_2()			=>	<simple command> '>' <file>
 * cmd_3()			=>	<simple command>
 *
 * simple_cmd()		=>	test simple cmd
 * simple_cmd_1()	=>	<name> <token list>
 *
 * tok_lst()		=>	test token list
 * tok_lst_1()		=>	<token> <token list>
 * tok_lst_2()		=>	(null)
 *
 */

/* parse main function */
int	parse(t_lexer *lex, t_ast *ast)
{
	g_sh.tok = lex->tok_lst;
	ast = cmd_line();
	if (lex->n_toks == 0)
		return (1);
	if (g_sh.tok != NULL && g_sh.tok->type != 0)
	{
		ft_dprintf(STDERR_FILENO, "Error: syntax error near: %s\n",
			g_sh.tok->data);
		return (1);
	}
	return (0);
}
