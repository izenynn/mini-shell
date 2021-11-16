/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/16 11:39:20 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		// TODO handle signals

		line = prompt_read_input();
		if (line == NULL || ft_strlen(line) <= 0)
			continue ;

		/* lexer */
		lexer_build(line, ft_strlen(line), &lex);
		free(line);

		t_tok *tmp;
		tmp = lex.tok_lst;
		while (tmp)
		{
			printf("type: %d, data: %s\n", tmp->type, tmp->data);
			tmp = tmp->next;
		}

		// TODO parse the tokens into an abstract syntax tree
		// TODO free all before looping again
	}

	/* shutdown and cleanup */
	// TODO

	return (EXIT_SUCCESS);
}
