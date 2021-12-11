/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:10:33 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/10 13:10:36 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	export_var(char **new_env, char *tmp, char *aux, char *aux2)
{
	int	i;

	i = 0;
	while (new_env[++i])
	{
		tmp = ft_substr(new_env[i], 0, get_var_len(new_env[i]));
		aux = ft_getenv(tmp);
		if (!aux)
		{
			if (new_env[i][get_var_len(new_env[i])] != '=')
			{
				aux2 = ft_strjoin(new_env[i], "=");
				free(new_env[i]);
				new_env[i] = aux2;
			}
			add_env(new_env, i);
			free(tmp);
		}
		else
		{
			free(aux);
			update_var(tmp, new_env[i]);
		}
	}
}

void	add_env(char *const *new_env, int i)
{
	if (error_handle(new_env[i]) == 0)
		ft_lstadd_back(g_sh.env,
			ft_lstnew((void *)ft_strdup(new_env[i])));
}

void	free_aux(char *tmp, char *aux)
{
	free(tmp);
	free(aux);
}

static void	print_err(const char *new_env)
{
	write(STDERR_FILENO, "export: ", 8);
	write(STDERR_FILENO, new_env, ft_strlen(new_env));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "not a valid identifier\n", 23);
}

int	error_handle(char *new_env)
{
	int	i;

	i = 0;
	if ((new_env[0] >= 'A' && new_env[0] <= 'Z')
		|| (new_env[0] >= 'a' && new_env[0] <= 'z')
		|| new_env[0] == '_')
	{
		while (new_env[++i] != '=')
		{
			if (ft_isalnum(new_env[i]) == 0
				&& new_env[i] != '_' && new_env[i] != '=')
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
