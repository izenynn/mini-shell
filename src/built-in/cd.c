/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:04 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/22 18:01:31 by                  ###   ########.fr       */
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
	g_sh.env->data = ft_strjoin("PWD=", n_path);
	free(n_path);
}

int	locate_env(t_list *head)
{
	while (g_sh.env)
	{
		if (ft_strncmp("PWD=", (char *)g_sh.env->data, 4) == 0)
		{
			update_env();
			g_sh.env = head;
			g_sh.status = 0;
			return (0);
		}
		g_sh.env = g_sh.env->next;
	}
	g_sh.status = 1;
	return (1);
}

static int	goto_home(void)
{
	char	*home;
	t_list	*head;

	home = ft_getenv("HOME");
	head = g_sh.env;
	if (chdir(home) == -1)
	{
		print_error(home);
		free(home);
		g_sh.status = 1;
		return (1);
	}
	g_sh.status = 0;
	locate_env(head);
	free(home);
	return (0);
}

static int	goto_dir(const char *dir)
{
	char	*aux;
	char	*tmp;
	char	*home;

	aux = ft_substr(dir, 1, ft_strlen(dir) - 1);
	home = ft_getenv("HOME");
	if (!home)
		return (1);
	aux = ft_realloc(aux, ft_strlen(dir) + ft_strlen(home) + 1);
	tmp = ft_strjoin(home, aux);
	if (chdir(tmp) == -1)
	{
		print_error(tmp);
		free(home);
		free(aux);
		free(tmp);
		g_sh.status = 1;
		return (1);
	}
	free(home);
	free(aux);
	free(tmp);
	return (0);
}

int	ft_changedir(char **dir)
{
	t_list	*head;

	head = g_sh.env;
	set_oldpwd(head);
	if (!dir[1] || dir[1][0] == '~')
	{
		if (!dir[1])
		{
			goto_home();
			return (0);
		}
		if (goto_dir(dir[1]) == 1)
			return (1);
	}
	if (chdir(dir[1]) == -1)
	{
		print_error(dir[1]);
		return (1);
	}
	return (1);
}
