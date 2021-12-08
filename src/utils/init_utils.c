/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:21:17 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/08 20:10:15 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static char	*set_envs(char *pwd, const char *sh_lvl, char *aux)
{
	if (getcwd(pwd, PATH_MAX))
	{
		aux = ft_strjoin("PWD=", pwd);
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(aux)));
	}
	ft_lstadd_back(&g_sh.env, ft_lstnew(ft_strdup((void *)sh_lvl)));
	return (aux);
}

static void	update_shlvl(void)
{
	t_list	*head;
	char	*tmp;
	char	*tmp2;
	int		aux;

	head = g_sh.env;
	while (g_sh.env)
	{
		if (ft_strncmp("SHLVL=", (char *)g_sh.env->data, 6) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
	if (!g_sh.env)
	{
		g_sh.env = head;
		return ;
	}
	tmp = ft_substr((char *)g_sh.env->data, 6,
			ft_strlen((char *)g_sh.env->data) - 6);
	aux = ft_atoi(tmp);
	if (aux < 0)
	{
		aux = 1;
		free(tmp);
		tmp = ft_itoa(aux);
		tmp2 = ft_strjoin("SHLVL=", tmp);
		free(g_sh.env->data);
		g_sh.env->data = ft_strdup(tmp2);
		g_sh.env = head;
		return ;
	}
	aux++;
	free(tmp);
	tmp = ft_itoa(aux);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	free(g_sh.env->data);
	g_sh.env->data = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
	g_sh.env = head;
}

/* initialise enviroment */
void	fill_env(char **env)
{
	int		i;
	char	*pwd;
	char	*sh_lvl;
	char	*aux;

	i = -1;
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return ;
	aux = NULL;
	sh_lvl = ft_strdup("SHLVL=1");
	if (env[0])
	{
		while (env[++i])
			ft_lstadd_back(&g_sh.env, ft_lstnew((void *) ft_strdup(env[i])));
		update_shlvl();
	}
	else
		aux = set_envs(pwd, sh_lvl, aux);
	if (aux)
		free(aux);
	free(pwd);
	free(sh_lvl);
}
