/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:38:04 by acostal-          #+#    #+#             */
/*   Updated: 2021/12/20 10:01:34 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* */
static t_list	*build_str(const char *unset, char **tmp)
{
	t_list	*aux;
	char	*tmp2;

	ft_strlcpy(*tmp, unset, ft_strlen(unset) + 1);
	tmp2 = *tmp;
	*tmp = ft_strjoin(tmp2, "=");
	free(tmp2);
	aux = *g_sh.env;
	return (aux);
}

/* move list to desired positon */
static t_list	*find_pos(const char *unset, int *count, char *tmp)
{
	t_list	*aux;

	if (unset == NULL)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 1));
	if (!tmp)
		return (NULL);
	aux = build_str(unset, &tmp);
	if (ft_strncmp((char *)aux->data, tmp, ft_strlen(tmp)) == 0)
	{
		free(tmp);
		return (aux);
	}
	while (aux && aux->next)
	{
		(*count)++;
		if (ft_strncmp((char *)aux->next->data, tmp, ft_strlen(tmp)) == 0)
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
static void	delete_and_join(t_list *aux, int cnt)
{
	t_list	*tmp;

	tmp = NULL;
	if (cnt == 0)
	{
		aux = *g_sh.env;
		*g_sh.env = (*g_sh.env)->next;
		ft_lstdelone(aux, free);
		return ;
	}
	if (aux->next && aux->next->next)
		tmp = aux->next->next;
	ft_lstdelone(aux->next, free);
	aux->next = tmp;
}

/* */
void	execute_unset(char *const *unset, char *tmp, t_list *aux, int i)
{
	int	cnt;

	cnt = 0;
	aux = find_pos(unset[i], &cnt, tmp);
	if (aux != NULL)
		delete_and_join(aux, cnt);
}

/* */
int	ft_unset(char **unset)
{
	int		ret;
	char	*tmp;
	t_list	*aux;
	int		i;

	aux = *g_sh.env;
	tmp = NULL;
	i = 0;
	ret = 0;
	if (!aux && unset[1])
		return (0);
	else if (aux && unset[1])
	{
		while (unset[++i])
		{
			if (unset_error_handle(unset[i]) == 0)
				execute_unset(unset, tmp, aux, i);
			else
				ret = 1;
		}
	}
	return (ret);
}
