/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:21:17 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/16 17:01:39 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static char	*set_envs(char *pwd, const char *sh_lvl, char *aux)
{
	if (getcwd(pwd, PATH_MAX))
	{
		aux = ft_strjoin("PWD=", pwd);
		ft_lstadd_back(g_sh.env, ft_lstnew((void *)ft_strdup(aux)));
	}
	ft_lstadd_back(g_sh.env, ft_lstnew(ft_strdup((void *)sh_lvl)));
	return (aux);
}

static int	safe_shlvl(t_list *gaux, char **tmp, int *aux)
{
	char	*tmp2;

	if ((*aux) < 0)
	{
		(*aux) = 1;
		free((*tmp));
		(*tmp) = ft_itoa((*aux));
		tmp2 = ft_strjoin("SHLVL=", (*tmp));
		free(gaux->data);
		gaux->data = ft_strdup(tmp2);
		return (1);
	}
	return (0);
}

static void	increment_shlvl(t_list *gaux, char *tmp, int aux)
{
	char	*tmp2;

	aux++;
	free(tmp);
	tmp = ft_itoa(aux);
	tmp2 = ft_strjoin("SHLVL=", tmp);
	free(gaux->data);
	gaux->data = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
}

static void	update_shlvl(void)
{
	t_list	*gaux;
	char	*tmp;
	int		aux;

	gaux = *g_sh.env;
	while (gaux)
	{
		if (ft_strncmp("SHLVL=", (char *)gaux->data, 6) == 0)
			break ;
		gaux = gaux->next;
	}
	if (!gaux)
	{
		ft_lstadd_back(g_sh.env, ft_lstnew(ft_strdup("SHLVL=1")));
		return ;
	}
	tmp = ft_substr((char *)gaux->data, 6,
			ft_strlen((char *)gaux->data) - 6);
	aux = ft_atoi(tmp);
	if (safe_shlvl(gaux, &tmp, &aux) == 1)
		return ;
	else
		increment_shlvl(gaux, tmp, aux);
}

/* initialise enviroment */
void	fill_env(char **env)
{
	int		i;
	char	*pwd;
	char	*sh_lvl;
	char	*aux;

	i = -1;
	g_sh.env = (t_list **)ft_calloc(1, (sizeof(t_list *)));
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd || !g_sh.env)
		return ;
	aux = NULL;
	sh_lvl = ft_strdup("SHLVL=1");
	if (env[0])
	{
		while (env[++i])
			ft_lstadd_back(g_sh.env, ft_lstnew((void *) ft_strdup(env[i])));
		update_shlvl();
	}
	else
		aux = set_envs(pwd, sh_lvl, aux);
	if (aux)
		free(aux);
	free(pwd);
	free(sh_lvl);
}
