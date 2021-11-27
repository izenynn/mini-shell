/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:20:01 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/27 11:43:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static char	**lst_to_ptr(void)
{
	char	**env;
	int		i;
	t_list	*head;

	i = 0;
	env = malloc(sizeof(char *) * (ft_lstsize(g_sh.env) + 1));
	head = g_sh.env;
	while (g_sh.env)
	{
		env[i++] = ft_strdup((char *)g_sh.env->data);
		g_sh.env = g_sh.env->next;
	}
	env[i] = NULL;
	g_sh.env = head;
	return (env);
}

static void	print_list(char **env)
{
	int	i;
	int	j;
	int	chk;

	i = -1;
	while (env[++i])
	{
		chk = 0;
		j = -1;
		write(1, env[i], ft_strlen(env[i]));
		while (env[i][++j])
		{
			if (env[i][j] == '=')
			{
				chk++;
				break ;
			}
		}
		if (chk == 0)
			write(1, "=''", 3);
		write(1, "\n", 1);
		free(env[i]);
	}
	free(env);
}

static void	swap_strs(int i, int j, char **env, char *tmp)
{
	if (get_var_len(env[j]) > get_var_len(env[i]))
	{
		if (ft_strncmp(env[j], env[i], get_var_len(env[j])) > 0)
		{
			tmp = ft_strdup(env[j]);
			free(env[j]);
			env[j] = ft_strdup(env[i]);
			free(env[i]);
			env[i] = tmp;
		}
	}
	else
	{
		if (ft_strncmp(env[j], env[i], get_var_len(env[i])) > 0)
		{
			tmp = ft_strdup(env[j]);
			free(env[j]);
			env[j] = ft_strdup(env[i]);
			free(env[i]);
			env[i] = tmp;
		}
	}
}

static void	ft_lst_sorter(void)
{
	int		i;
	int		j;
	char	**env;
	char	*tmp;

	tmp = NULL;
	i = -1;
	env = lst_to_ptr();
	while (env[++i])
	{
		j = -1;
		while (env[++j])
			swap_strs(i, j, env, tmp);
	}
	print_list(env);
}

int	ft_export(char **new_env)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = 0;
	if (!new_env[1])
		ft_lst_sorter();
	else
	{
		while (new_env[++i])
		{
			tmp = ft_substr(new_env[i], 0, get_var_len(new_env[i]));
			aux = ft_getenv(tmp);
			if (!aux)
			{
				if (error_handle(new_env[i]) == 0)
					ft_lstadd_back(&g_sh.env,
						ft_lstnew((void *)ft_strdup(new_env[i])));
				free(tmp);
			}
			else
			{
				free(aux);
				update_var(tmp, new_env[i]);
			}
		}
	}
	return (0);
}
