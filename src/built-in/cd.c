/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:19:37 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/17 18:08:05 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	update_env(t_list **env)
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
	free((*env)->data);
	(*env)->data = ft_strjoin("PWD=", n_path);
	free(n_path);
}

int	goto_home(void)
{
	char	*home;
	t_list	*head;

	home = ft_getenv("HOME");
	head = *g_sh.env;
	if (!home || chdir(home) == -1)
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

static int	goto_oldpwd(t_list *env)
{
	char	*opwd;
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	pwd = NULL;
	opwd = ft_getenv("OLDPWD");
	if (!opwd)
	{
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return (1);
	}
	if (chdir(opwd) == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, opwd, ft_strlen(opwd));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		free(opwd);
		return (1);
	}
	free(opwd);
	set_oldpwd(env, tmp, pwd);
	locate_env(env);
	return (0);
}

int	ft_changedir(char **dir)
{
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	pwd = NULL;
	if (dir[1] && ft_strncmp(dir[1], "-", 1) == 0)
		return (goto_oldpwd(*g_sh.env));
	set_oldpwd(*g_sh.env, tmp, pwd);
	if (!dir[1] || (!ft_strncmp(dir[1], "~\0", 2)
			|| !ft_strncmp(dir[1], "~/", 2)))
	{
		if (!dir[1] || !ft_strncmp(dir[1], "~\0", 2))
		{
			if (home_handler() == 1)
				return (1);
			return (0);
		}
		else if (goto_dir(dir[1]) == 1)
			return (1);
	}
	else if (dir[1][0] != '\0' && chdir(dir[1]) == -1)
		return (print_error(dir[1]));
	else
		set_env(*g_sh.env);
	return (0);
}
