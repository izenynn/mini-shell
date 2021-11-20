/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:38:04 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 18:18:45 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* move list to desired positon */
void	find_pos(const char *unset)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return ;
	strcpy(tmp, unset);
	tmp[ft_strlen(unset)] = '=';
	tmp[ft_strlen(unset) + 1] = '\0';
	while (g_sh.env)
	{
		if (ft_strncmp((char *)g_sh.env->next->data, tmp,
				   ft_strlen(tmp)) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
	free(tmp);
}

void	delete_and_join(t_list *head, t_list *aux)
{
	aux = g_sh.env->next->next;
	ft_lstdelone(g_sh.env->next, free);
	g_sh.env->next = aux;
	g_sh.env = head;
}

int	ft_unset(char **unset)
{
	t_list	*head;
	t_list	*aux;
	int		i;

	head = g_sh.env;
	aux = NULL;
	i = -1;
	if (unset)
	{
		while (unset[++i])
		{
			find_pos(unset[i]);
			if (!g_sh.env)
				g_sh.env = head;
			else
				delete_and_join(head, aux);
		}
	}
	else
	{
		printf("%s\n", "unset: not enough arguments");
		return (-1);
	}
	g_sh.env = head;
	return (0);
}
