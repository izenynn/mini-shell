/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/15 20:01:44 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	initialise_vars()
{
	g_sh.status = EXIT_SUCCESS;
}

/* initialise shell */
void	init_shell()
{
	initialise_vars();

	// TODO ignore signals (call signals())
}
