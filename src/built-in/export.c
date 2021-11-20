/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:36:31 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 16:36:33 by acostal-         ###   ########.fr       */
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
	g_sh.env = head;
	env[i] = NULL;
	return (env);
}

static void	print_list(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		printf("%s\n", env[i]);
		free(env[i]);
	}
	free(env);
}

static void	swap_strs(int i, int j, char **env, char *tmp)
{
	if (custom_len(env[j]) > custom_len(env[i]))
	{
		if (ft_strncmp(env[j], env[i], custom_len(env[j])) > 0)
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
		if (ft_strncmp(env[j], env[i], custom_len(env[i])) > 0)
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

	i = -1;
	if (!new_env)
		ft_lst_sorter();
	else
	{
		while (new_env[++i])
			ft_lstadd_back(&g_sh.env, ft_lstnew(new_env[i]));
		g_sh.status = 0;
	}
	return (0);
}
