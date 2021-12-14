/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:10:45 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/14 11:37:50 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int	locate_env(t_list *head)
{
	t_list	*aux;

	aux = head;
	while (aux != NULL)
	{
		if (ft_strncmp("PWD=", (char *)aux->data, 4) == 0)
		{
			update_env(&aux);
			return (0);
		}
		aux = aux->next;
	}
	return (1);
}

void	update_var(char *var_name, char *var)
{
	t_list	*aux;
	char	*content;
	char	*tmp;

	aux = *g_sh.env;
	tmp = ft_strjoin(var_name, "=");
	free(var_name);
	content = ft_substr(var, get_var_len(var) + 1,
			ft_strlen(var) - ft_strlen(tmp));
	while (aux != NULL)
	{
		if (ft_strncmp(tmp, (char *)aux->data, ft_strlen(tmp)) == 0)
			break ;
		aux = aux->next;
	}
	free(aux->data);
	aux->data = ft_strjoin(tmp, content);
	free(tmp);
	free(content);
}

int	try_to_goto_olpwd(t_list **head)
{
	t_list	*aux;

	aux = *head;
	if (!*head)
		return (1);
	while (*head)
	{
		if (ft_strncmp("OLDPWD=", (char *)(*head)->data, 7) == 0)
			return (0);
		*head = (*head)->next;
	}
	*head = aux;
	return (1);
}

void	set_values(t_list **env, const char *aux, int c)
{
	if (c == 0)
	{
		free((*env)->data);
		(*env)->data = (void *)ft_strdup(aux);
	}
	else
		ft_lstadd_back(g_sh.env, ft_lstnew((void *) ft_strdup(aux)));
}

int	set_oldpwd(t_list *env, char *aux, char *pwd)
{
	int		ret;
	t_list	*tmp;

	pwd = ft_getenv("PWD");
	tmp = env;
	ret = try_to_goto_olpwd(&tmp);
	if (tmp == NULL)
	{
		free(pwd);
		return (1);
	}
	if (pwd == NULL)
	{
		pwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
		if (!pwd || getcwd(pwd, PATH_MAX) == NULL)
		{
			free(pwd);
			return (1);
		}
	}
	aux = ft_strjoin("OLDPWD=", pwd);
	set_values(&tmp, aux, ret);
	free(pwd);
	free(aux);
	return (0);
}
