/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:16:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 17:24:47 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle zombie process */
void	handle_zombies(void)
{
	int		child;
	pid_t	pid;
	int		status;

	child = 1;
	while (child)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			child = 0;
	}
}
