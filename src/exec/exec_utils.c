/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:16:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 18:55:51 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle zombie process */
void	handle_zombies(void)
{
	pid_t	pid;
	int		status;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		g_sh.status = status;
	}
}
