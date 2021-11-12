/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/12 11:55:24 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	initialise_vars()
{
	g_sh.l_exit = EXIT_SUCCESS;
}

/* initialise shell */
void	init_shell()
{
	initialise_vars();
}
