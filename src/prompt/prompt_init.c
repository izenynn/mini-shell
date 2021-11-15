/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:17:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/12 11:49:05 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* welcome message on start */
static void	welcome(void)
{
	/*printf("\n"\
	FG_YEL "           _       _ " FG_RED "    _          _ _ \n"\
	FG_YEL " _ __ ___ (_)_ __ (_)" FG_RED "___| |__   ___| | |\n"\
	FG_YEL "| '_ ` _ \\| | '_ \\| " FG_RED "/ __| '_ \\ / _ \\ | |\n"\
	FG_YEL "| | | | | | | | | | " FG_RED "\\__ \\ | | |  __/ | |\n"\
	FG_YEL "|_| |_| |_|_|_| |_|_" FG_RED "|___/_| |_|\\___|_|_|\n"\
	FG_DEF);*/

	/*printf("\n"\
	FG_GRN "           oo          oo          dP                dP dP\n"\
	FG_YEL "                                   88                88 88\n"\
	FG_RED "88d8b.d8b. dP 88d888b. dP .d8888b. 88d888b. .d8888b. 88 88\n"\
	FG_MAG "88'`88'`88 88 88'  `88 88 Y8ooooo. 88'  `88 88ooood8 88 88\n"\
	FG_BLU "88  88  88 88 88    88 88       88 88    88 88.  ... 88 88\n"\
	FG_CYN "dP  dP  dP dP dP    dP dP `88888P' dP    dP `88888P' dP dP\n"\
	FG_DEF);*/

	printf("\n"\
	FG_YEL "           oo          oo " FG_GRN "         dP                dP dP\n"\
	FG_YEL "                          " FG_YEL "         88                88 88\n"\
	FG_YEL "88d8b.d8b. dP 88d888b. dP " FG_RED ".d8888b. 88d888b. .d8888b. 88 88\n"\
	FG_YEL "88'`88'`88 88 88'  `88 88 " FG_MAG "Y8ooooo. 88'  `88 88ooood8 88 88\n"\
	FG_YEL "88  88  88 88 88    88 88 " FG_BLU "      88 88    88 88.  ... 88 88\n"\
	FG_YEL "dP  dP  dP dP dP    dP dP " FG_CYN "`88888P' dP    dP `88888P' dP dP\n"\
	FG_DEF);
}

/* initialise prompt */
void	init_prompt(void)
{
	welcome();
}
