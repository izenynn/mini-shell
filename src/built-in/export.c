/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:20:01 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/10 12:42:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static char	**lst_to_ptr(void)
{
	char	**env;
	int		i;
	t_list	*aux;

	i = 0;
	env = malloc(sizeof(char *) * (ft_lstsize(*g_sh.env) + 1));
	if (!env)
		return (NULL);
	aux = *g_sh.env;
	while (aux)
	{
		env[i++] = ft_strdup(aux->data);
		aux = aux->next;
	}
	env[i] = NULL;
	return (env);
}

static void	print_list(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j] != '\0')
		{
			write(STDOUT_FILENO, &env[i][j], 1);
			if (env[i][j] == '=')
				break ;
		}
		write(STDOUT_FILENO, "\"", 1);
		while (env[i][++j] != '\0')
		{
			write(STDOUT_FILENO, &env[i][j], 1);
		}
		if (env[i][j] == '\0')
			write(STDOUT_FILENO, "\"", 1);
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
	char	*tmp;
	char	*aux;
	char	*aux2;

	aux = NULL;
	tmp = NULL;
	aux2 = NULL;
	if (!new_env[1])
		ft_lst_sorter();
	else
		export_var(new_env, tmp, aux, aux2);
	return (0);
}
