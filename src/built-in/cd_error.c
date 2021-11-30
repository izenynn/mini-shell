/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:19:48 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/30 19:02:54 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	print_error(const char *dir)
{
	if (dir)
	{
		write(STDERR_FILENO, "cd: ",
			  ft_strlen("cd: "));
		write(STDERR_FILENO, dir, ft_strlen(dir));
		write(STDERR_FILENO, ": no such file or directory:\n", 29);
	}
	else
		write(STDERR_FILENO, "cd: HOME not set\n", 18);
	return (1);
}

int	home_handler(t_list *head)
{
	if (goto_home() == 1 || locate_env(head))
		return (1);
	return (0);
}

void	set_env(t_list *head)
{
	locate_env(head);
	g_sh.env = head;
}
