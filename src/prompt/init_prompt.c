/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 12:17:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 19:47:16 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* welcome message on start */
static void	welcome(void)
{
	ft_dprintf(STDERR_FILENO, "\n"\
	FG_YEL "           oo          oo " FG_GRN "         dP                dP dP\n"\
	FG_YEL "                          " FG_YEL "         88                88 88\n"\
	FG_YEL "88d8b.d8b. dP 88d888b. dP " FG_RED ".d8888b. 88d888b. .d8888b. 88 88\n"\
	FG_YEL "88'`88'`88 88 88'  `88 88 " FG_MAG "Y8ooooo. 88'  `88 88ooood8 88 88\n"\
	FG_YEL "88  88  88 88 88    88 88 " FG_BLU "      88 88    88 88.  ... 88 88\n"\
	FG_YEL "dP  dP  dP dP dP    dP dP " FG_CYN "`88888P' dP    dP `88888P' dP dP\n"\
	FG_DEF "\n");
}

/* initialise prompt */
void	init_prompt(void)
{
	welcome();
}
