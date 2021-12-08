/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:19:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/08 20:07:29 by                  ###   ########.fr       */
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
	{
		free(n_path);
		n_path = ft_getenv("PWD");
		if (!n_path)
			return ;
	}
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
			return (0);
		}
		g_sh.env = g_sh.env->next;
	}
	return (1);
}

int	goto_home(void)
{
	char	*home;
	t_list	*head;

	home = ft_getenv("HOME");
	head = g_sh.env;
	if (chdir(home) == -1)
	{
		print_error(home);
		free(home);
		return (1);
	}
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
	{
		free(aux);
		return (1);
	}
	aux = ft_realloc(aux, ft_strlen(dir) + ft_strlen(home) + 1);
	tmp = ft_strjoin(home, aux);
	if (chdir(tmp) == -1)
	{
		print_error(tmp);
		free(home);
		free(aux);
		free(tmp);
		return (1);
	}
	free(home);
	free(aux);
	free(tmp);
	return (0);
}

int	goto_oldpwd(t_list *head)
{
	char	*opwd;

	opwd = ft_getenv("OLDPWD");
	if (!opwd)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	if (chdir(opwd) == -1)
	{
		free(opwd);
		return (1);
	}
	free(opwd);
	set_oldpwd(head);
	update_env();
	return (0);
}

int	ft_changedir(char **dir)
{
	t_list	*head;

	head = g_sh.env;
	if (dir[1] && ft_strncmp(dir[1], "-", 1) == 0)
		return (goto_oldpwd(head));
	set_oldpwd(head);
	if (!dir[1] || dir[1][0] == '~')
	{
		if (!dir[1])
		{
			if (home_handler(head) == 1)
				return (1);
			return (0);
		}
		else if (goto_dir(dir[1]) == 1)
			return (1);
		else
		{
			locate_env(head);
			return (0);
		}
	}
	else if (chdir(dir[1]) == -1)
		return (print_error(dir[1]));
	else
		set_env(head);
	return (0);
}
