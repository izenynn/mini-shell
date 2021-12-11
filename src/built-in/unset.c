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

/* move list to desired positon */
static t_list	*find_pos(const char *unset, int *count)
{
	char	*tmp;
	t_list	*aux;

	if (unset == NULL)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return (NULL);
	strcpy(tmp, unset);
	tmp[ft_strlen(unset)] = '=';
	tmp[ft_strlen(unset) + 1] = '\0';
	aux = *g_sh.env;
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
int	ft_unset(char **unset)
{
	t_list	*aux;
	int		i;
	int 	cnt;

	aux = *g_sh.env;
	i = 0;
	cnt = 0;
	if (unset[1])
	{
		while (unset[++i])
		{
			aux = find_pos(unset[i], &cnt);
			printf("%d\n", cnt);
			if (aux != NULL)
				delete_and_join(aux, cnt);
		}
	}
	else
	{
		write(STDERR_FILENO, "unset: not enough arguments\n", 28);
		return (1);
	}
	return (0);
}