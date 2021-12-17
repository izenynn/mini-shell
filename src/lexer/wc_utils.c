/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:49:16 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 00:47:38 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void	wc_put_error(t_tok *const *tok, t_tok *head)
{
	ft_putstr_fd((*tok)->data, STDERR_FILENO);
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
	tok_del(head);
}

/* swap two elements in a list */
static void	swap_data(t_tok *t1, t_tok *t2)
{
	char	*tmp;

	tmp = t1->data;
	t1->data = t2->data;
	t2->data = tmp;
}

/* compare two tokens data */
static int	lowercmp(const char *s1, const char *s2)
{
	int	c1;
	int	c2;

	while (*s1 != '\0' && *s2 != '\0' && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	c1 = (unsigned char)ft_tolower(*s1);
	c2 = (unsigned char)ft_tolower(*s2);
	if (ft_islower(c1))
		c1++;
	if (ft_islower(c2))
		c2++;
	if (c1 == '~')
		c1 = 'a';
	if (c2 == '~')
		c2 = 'a';
	return (c1 - c2);
}

void	sort_list(t_tok **head)
{
	t_tok	*aux1;
	t_tok	*aux2;

	aux1 = *head;
	while (aux1)
	{
		aux2 = aux1->next;
		while (aux2)
		{
			if (lowercmp(aux1->data, aux2->data) > 0)
				swap_data(aux1, aux2);
			aux2 = aux2->next;
		}
		aux1 = aux1->next;
	}
}

/* read current directory */
void	read_dir(t_tok **head, DIR *ls, struct dirent *list)
{
	t_tok	*aux;

	aux = *head;
	while (list)
	{
		aux->data = ft_strdup(list->d_name);
		aux->type = TOK;
		list = readdir(ls);
		if (list)
		{
			aux->next = (t_tok *)ft_calloc(1, sizeof(t_tok));
			aux = aux->next;
		}
	}
	aux->next = NULL;
	sort_list(head);
}
