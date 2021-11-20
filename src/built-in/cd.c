/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:04 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 18:55:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	update_env(void)
{
	char	*n_path;

	n_path = malloc(sizeof(char) * (PATH_MAX + 1));
	if (!n_path)
		return ;
	if (getcwd(n_path, PATH_MAX) == NULL)
		return ;
	free(g_sh.env->data);
	g_sh.env->data = ft_strdup("PWD=");
	g_sh.env->data = ft_realloc(g_sh.env->data, sizeof(char)
			* (ft_strlen(n_path) + 5));
	g_sh.env->data = ft_strcat((char *)g_sh.env->data, n_path);
	free(n_path);
}

int	ft_changedir(const char *dir)
{
	t_list	*head;

	head = g_sh.env;
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
	{
		write(1, "cd: no such file or directory: ",
			  ft_strlen("cd: no such file or directory: "));
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
		return (-1);
	}
	else
	{
		while (g_sh.env)
		{
			if (ft_strncmp("PWD=", (char *)g_sh.env->data, 4) == 0)
			{
				update_env();
				g_sh.env = head;
				return (0);
			}
			g_sh.env = g_sh.env->next;
		}
	}
	return (1);
}
