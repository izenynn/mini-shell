/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:33:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/23 14:07:03 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
 * ctrl + c = 2 -> exit code = 130
 * ctrl + z = 18 -> exit code = 146
 * ctrl + \ = 3 -> exit code = 131
 * //TODO HANDLE ctrl + d
 *
 */

//TODO set exit code on status global var

/* handle signals */
static void	sig_handler(int signum)
{
	(void)signum;
	/*printf("\n%d\n", signum);
	if (signum == 18)
		ft_exit("146");
	if (signum == 2)
		ft_exit("130");
	if (signum == 3)
		ft_exit("131");*/
}

/* initialise signals */
int	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}

// TODO enb_signals()
// TODO dis_signals()
