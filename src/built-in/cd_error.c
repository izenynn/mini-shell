/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:19:48 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/24 19:19:49 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	print_error(const char *dir)
{
	write(STDERR_FILENO, "cd: ",
		  ft_strlen("cd: "));
	write(STDERR_FILENO, dir, ft_strlen(dir));
	write(STDERR_FILENO, ": no such file or directory:\n", 29);
	return (1);
}

void	home_handler(t_list *head)
{
	goto_home();
	locate_env(head);
}

void	set_env(t_list *head)
{
	locate_env(head);
	g_sh.env = head;
}
