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
static int	find_pos(const char *unset)
{
	int		cnt;
	char	*tmp;

	if (unset == NULL)
		return (1);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return (1);
	cnt = 0;
	ft_strlcpy(tmp, unset, ft_strlen(tmp) + ft_strlen(unset));
	tmp[ft_strlen(unset)] = '=';
	tmp[ft_strlen(unset) + 1] = '\0';
	if (ft_strncmp((char *)g_sh.env->data, tmp, ft_strlen(tmp)) == 0)
		return (0);
	while (g_sh.env && g_sh.env->next)
	{
		cnt++;
		if (ft_strncmp((char *)g_sh.env->next->data, tmp,
					   ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (cnt);
		}
		g_sh.env = g_sh.env->next;
	}
	free(tmp);
	return (1);
}

/* */
static void	delete_and_join(t_list *head, int cnt)
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
	if (g_sh.env->next && g_sh.env->next->next)
		aux = g_sh.env->next->next;
	ft_lstdelone(g_sh.env->next, free);
	g_sh.env->next = aux;
	g_sh.env = head;
}

/* */
int	ft_unset(char **unset)
{
	t_list	*head;
	int		i;
	int 	cnt;

	head = g_sh.env;
	i = 0;
	if (unset[1])
	{
		while (unset[++i])
		{
			cnt = find_pos(unset[i]);
			if (!g_sh.env)
				g_sh.env = head;
			else
				delete_and_join(head, cnt);
		}
	}
	else
	{
		write(STDERR_FILENO, "unset: not enough arguments\n", 28);
		return (1);
	}
	g_sh.env = head;
	return (0);
}