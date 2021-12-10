/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:38:04 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/10 13:32:41 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	copy_and_concat(const char *unset, char *tmp)
{
	ft_strlcpy(tmp, unset, ft_strlen(tmp) + ft_strlen(unset));
	tmp[ft_strlen(unset)] = '=';
	tmp[ft_strlen(unset) + 1] = '\0';
}

/* move list to desired positon */
static t_list	*find_pos(const char *unset, t_list *aux)
{
	char	*tmp;

	if (unset == NULL)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return (NULL);
	copy_and_concat(unset, tmp);
	if (ft_strncmp(aux->data, tmp, ft_strlen(tmp)) == 0)
		return (aux);
	while (aux && aux->next)
	{
		if (ft_strncmp(aux->next->data, tmp,
				ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (aux);
		}
		aux = aux->next;
	}
	free(tmp);
	return (NULL);
}

/* */
static void	delete_and_join(t_list *tmp, t_list *head, int cnt)
{
	t_list	*aux;

	aux = NULL;
	if (cnt == 0)
	{
		aux = g_sh.env->next;
		ft_lstdelone(g_sh.env, free);
		g_sh.env = aux;
		return ;
	}
	if (tmp->next && tmp->next->next)
		aux = tmp->next->next;
	ft_lstdelone(tmp->next, free);
	tmp->next = aux;
	tmp = head;
	g_sh.env = tmp;
}

/* */
int	ft_unset(char **unset)
{
	t_list	*aux;
	t_list	*head;
	int		i;
	int		size;

	aux = g_sh.env;
	head = g_sh.env;
	i = 0;
	size = ft_lstsize(aux);
	if (unset[1])
	{
		while (unset[++i])
		{
			aux = find_pos(unset[i], aux);
			if (aux && ft_lstsize(aux) == size)
				delete_and_join(aux, head, 0);
			else
				delete_and_join(aux, head, 1);
		}
	}
	return (0);
}
