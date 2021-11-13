/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/13 11:15:32 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh/lexer.h"
#include <sh.h>

/* global var */
t_sh	g_sh;

/* main */
int	main(void)
{
	char	*line;
	t_lexer	lex;

	/* initialise shell */
	init_shell();

	/* initialise terminal */
	init_prompt();

	/* minishell loop */
	while (1)
	{
		line = prompt_read_input();
		// prompt_process_input();

		// TESTS
		printf("line: %s\n", line);

		/* lexer */
		lexer_build(line, ft_strlen(line), &lex);

		// TODO parse the tokens into an abstract syntax tree
		//
		// TODO free all before looping again
	}

	/* shutdown and cleanup */
	// TODO

	return (EXIT_SUCCESS);
}
