/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/15 19:05:11 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	sh;

int	main(void)
{
	char	*line;
	t_lexer	lex;

	/* initialise lex */
	lex.tok_lst = NULL;

	/* initialise shell */
	init_shell();
	/* initialise terminal */
	init_terminal();

	/* minishell_loop() */
	// TODO

	/* shutdown and cleanup */
	// TODO

	return (EXIT_SUCCESS);
}
