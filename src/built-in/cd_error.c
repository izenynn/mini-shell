/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:19:48 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/14 11:02:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	print_error(const char *dir)
{
	if (dir)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, dir, ft_strlen(dir));
		write(STDERR_FILENO, ": no such file or directory:\n", 29);
	}
	else
		write(STDERR_FILENO, "cd: HOME not set\n", 17);
	return (1);
}

int	home_handler(void)
{
	if (goto_home() == 1)
		return (1);
	return (0);
}

void	set_env(t_list *env)
{
	locate_env(env);
}
