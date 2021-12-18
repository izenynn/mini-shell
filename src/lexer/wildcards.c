/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:28:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 16:37:32 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* delte all hidden files */
static int	del_hidden_files(t_tok **head)
{
	t_tok	*aux;
	t_tok	*prev;

	aux = *head;
	while (aux)
	{
		if (ft_strncmp((char *)aux->data, ".", 1) == 0)
		{
			if (aux == *head)
			{
				del_node(head, NULL);
				aux = *head;
			}
			else
				del_node(&aux, prev);
			continue ;
		}
		prev = aux;
		aux = aux->next;
	}
	return (0);
}

/* Read current dir and fill list with it */
static t_tok	*create_list(void)
{
	t_tok			*head;
	DIR				*ls;
	char			*cwd;
	struct dirent	*list;

	cwd = malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return (NULL);
	if (!getcwd(cwd, PATH_MAX))
		return (NULL);
	ls = opendir(cwd);
	free(cwd);
	head = (t_tok *)ft_calloc(1, sizeof(t_tok));
	if (head == NULL)
		return (NULL);
	list = readdir(ls);
	read_dir(&head, ls, list);
	closedir(ls);
	return (head);
}

static void	match(t_tok **head, const char *wildcard)
{
	t_tok	*aux;
	t_tok	*prev;

	prev = NULL;
	aux = *head;
	while (aux != NULL)
	{
		if (wc_match(wildcard, aux->data) <= 0)
		{
			if (aux == *head)
			{
				del_node(head, NULL);
				aux = *head;
			}
			else
				del_node(&aux, prev);
			continue ;
		}
		prev = aux;
		aux = aux->next;
	}
}

/* handle wildcards in tokens */
int	handle_wildcards(t_tok **tok, t_tok **prev, t_lexer *lex)
{
	t_tok	*head;

	if (wc_check(*tok) == 0)
		return (0);
	head = create_list();
	if (head == NULL)
		return (-1);
	if (ft_strncmp((*tok)->data, ".", 1))
		del_hidden_files(&head);
	match(&head, (*tok)->data);
	if (head == NULL)
		return (0);
	if (head->next != NULL && g_sh.prev
		&& (g_sh.prev->type == CHAR_GT || g_sh.prev->type == CHAR_LS))
	{
		wc_put_error(tok, head);
		return (-1);
	}
	rejoin_tokens(tok, prev, lex, head);
	return (1);
}
