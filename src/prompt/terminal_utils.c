/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:17:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/11 14:47:43 by dpoveda-         ###   ########.fr       */
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
	/*printf("\n"\
	FG_YEL "           _       _ " FG_RED "    _          _ _ \n"\
	FG_YEL " _ __ ___ (_)_ __ (_)" FG_RED "___| |__   ___| | |\n"\
	FG_YEL "| '_ ` _ \\| | '_ \\| " FG_RED "/ __| '_ \\ / _ \\ | |\n"\
	FG_YEL "| | | | | | | | | | " FG_RED "\\__ \\ | | |  __/ | |\n"\
	FG_YEL "|_| |_| |_|_|_| |_|_" FG_RED "|___/_| |_|\\___|_|_|\n"\
	FG_DEF "\n");*/

	/*printf("\n"\
	FG_GRN "           oo          oo          dP                dP dP\n"\
	FG_YEL "                                   88                88 88\n"\
	FG_RED "88d8b.d8b. dP 88d888b. dP .d8888b. 88d888b. .d8888b. 88 88\n"\
	FG_MAG "88'`88'`88 88 88'  `88 88 Y8ooooo. 88'  `88 88ooood8 88 88\n"\
	FG_BLU "88  88  88 88 88    88 88       88 88    88 88.  ... 88 88\n"\
	FG_CYN "dP  dP  dP dP dP    dP dP `88888P' dP    dP `88888P' dP dP\n"\
	FG_DEF "\n");*/

	printf("\n"\
	FG_YEL "           oo          oo " FG_GRN "         dP                dP dP\n"\
	FG_YEL "                          " FG_YEL "         88                88 88\n"\
	FG_YEL "88d8b.d8b. dP 88d888b. dP " FG_RED ".d8888b. 88d888b. .d8888b. 88 88\n"\
	FG_YEL "88'`88'`88 88 88'  `88 88 " FG_MAG "Y8ooooo. 88'  `88 88ooood8 88 88\n"\
	FG_YEL "88  88  88 88 88    88 88 " FG_BLU "      88 88    88 88.  ... 88 88\n"\
	FG_YEL "dP  dP  dP dP dP    dP dP " FG_CYN "`88888P' dP    dP `88888P' dP dP\n"\
	FG_DEF "\n");


}
