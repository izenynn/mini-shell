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
static int	find_pos(const char *unset, t_list *aux)
{
    int     count;
	char	*tmp;

	if (unset == NULL)
		return (1);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return (1);
    count = 0;
	ft_strlcpy(tmp, unset, ft_strlen(tmp) + ft_strlen(unset));
	tmp[ft_strlen(unset)] = '=';
	tmp[ft_strlen(unset) + 1] = '\0';
	while (aux && aux->next)
	{
		if (ft_strncmp((char *)aux->data, tmp,
				   ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (count);
		}
		aux = aux->next;
        count++;
	}
	free(tmp);
	return (-1);
}

/* */
static void	delete_and_join(t_list *head, int count)
{
    t_list  *tmp;
	t_list	*aux;

    tmp = g_sh.env;
    aux = NULL;
    if (count == 0)
    {
        aux = tmp->next;
        ft_lstdelone(tmp, free);
        g_sh.env = aux;
        return ;
    }
	if (tmp->next && tmp->next->next)
		aux = tmp->next->next;
	ft_lstdelone(tmp->next, free);
	tmp->next = aux;
	aux = head;
}

/* */
int	ft_unset(char **unset)
{
	t_list	*aux;
	int		i;
    int     count;

	aux = g_sh.env;
	i = 0;
	if (unset[1])
	{
		while (unset[++i])
		{
			count = find_pos(unset[i], aux);
			if (g_sh.env)
				delete_and_join(aux, count);
		}
	}
	else
	{
		write(STDERR_FILENO, "unset: not enough arguments\n", 28);
		return (1);
	}
	return (0);
}
