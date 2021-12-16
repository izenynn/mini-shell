/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:28:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 18:33:49 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* delete a token and join the previous with the next one */
void	del_node(t_tok **tok, t_tok *prev)
{
	t_tok	*tmp;

	if (prev == NULL)
	{
		tmp = *tok;
		*tok = (*tok)->next;
		free(tmp->data);
		free(tmp);
	}
	else
	{
		tmp = *tok;
		*tok = (*tok)->next;
		prev->next = *tok;
		free(tmp->data);
		free(tmp);
	}
}

/* delte all hidden files */
int	del_hidden_files(t_tok **head)
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
t_tok	*create_list(void)
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

void	match(t_tok **head, const char *wildcard)
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

void	rejoin_tokens(t_tok **tok, t_tok *prev, t_lexer *lex, t_tok *head)
{
	int		cnt;
	t_tok	*aux;

	aux = head;
	cnt = 1;
	while (aux->next && ++cnt)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = head;
	else
		prev->next = head;
	free((*tok)->data);
	free(*tok);
	lex->n_toks += cnt;
	*tok = aux->next;
}

int	handle_wildcards(t_tok **tok, t_tok *prev, t_lexer *lex)
{
	t_tok	*head;

	head = create_list();
	if (head == NULL)
		return (1);
	if (ft_strncmp((*tok)->data, ".", 1))
		del_hidden_files(&head);
	match(&head, (*tok)->data);
	if (head == NULL)
		return (0);
	if (prev && head->next != NULL
		&& (prev->type == CHAR_GT || prev->type == CHAR_LS))
	{
		wc_put_error(tok, head);
		return (1);
	}
	rejoin_tokens(tok, prev, lex, head);
	return (0);
}
