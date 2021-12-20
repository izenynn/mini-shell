/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:00:13 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/20 10:00:32 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	print_err(const char *new_env)
{
	write(STDERR_FILENO, "unset: ", 7);
	write(STDERR_FILENO, new_env, ft_strlen(new_env));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not a valid identifier\n", 23);
}

int	unset_error_handle(char *new_env)
{
	int		i;

	i = 0;
	if ((new_env[0] >= 'A' && new_env[0] <= 'Z')
		|| (new_env[0] >= 'a' && new_env[0] <= 'z')
		|| new_env[0] == '_')
	{
		while (new_env[++i])
		{
			if (ft_isalnum(new_env[i]) == 0 && new_env[i] != '_')
			{
				print_err(new_env);
				return (1);
			}
		}
		return (0);
	}
	else
		print_err(new_env);
	return (1);
}
