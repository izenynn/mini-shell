/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:17:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/10 13:36:45 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* die func. refresh screen, print error and exit */
void	die(const char *s)
{
	/* clear screen and move cursor */
	//write(STDOUT_FILENO, "\x1b[2J", 4);
	//write(STDOUT_FILENO, "\x1b[H", 3);

	/* restore terminal */
	//dis_raw_mode();

	/* print error and exit */
	perror(s);
	exit(EXIT_FAILURE);
}

/* welcome message on start */
void	welcome(void)
{
	printf(\
	FG_YEL "           _       _ " FG_RED "    _          _ _ \n"\
	FG_YEL " _ __ ___ (_)_ __ (_)" FG_RED "___| |__   ___| | |\n"\
	FG_YEL "| '_ ` _ \\| | '_ \\| " FG_RED "/ __| '_ \\ / _ \\ | |\n"\
	FG_YEL "| | | | | | | | | | " FG_RED "\\__ \\ | | |  __/ | |\n"\
	FG_YEL "|_| |_| |_|_|_| |_|_" FG_RED "|___/_| |_|\\___|_|_|\n"\
	FG_DEF "\n");
}
