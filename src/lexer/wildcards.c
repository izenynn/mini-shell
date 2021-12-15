/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:28:26 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 19:20:16 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* delete a token and join the previous with the next one */
void	del_node(t_tok **tok, t_tok *prev)
{
	t_tok	*tmp;

	// TODO maybe this function segfaults when **tok has no elements
	// please try it before changing the code
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
		// wc_match returns 0 when no match is found, so we delete the node
		if (wc_match(wildcard, aux->data) == 0)
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
	// when we exit this func the **head list will contain only the matches
}

int	handle_wildcards(t_tok **tok, t_tok *prev, t_lexer *lex)
{
	t_tok	*aux;
	t_tok	*head;
	int		cnt;

	// if prev token is a here_doc
	// TODO
	// create token list with all files
	head = create_list();
	if (head == NULL)
		return (1);
	// delete node if first is null
	if (head->data == NULL)
		del_node(&head, NULL);
	if (ft_strncmp((*tok)->data, ".", 1))
		del_hidden_files(&head);
	// match
	match(&head, (*tok)->data);
	// if no match
	if (head == NULL)
		return (0);
	// if match and prev token is a redir
	if (prev && head->next != NULL
		&& (prev->type == CHAR_GT || prev->type == CHAR_LS))
	{
		ft_putstr_fd((*tok)->data, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
		tok_del(head);
		return (1);
	}
	// else
	cnt = 1;
	aux = head;
	while (aux->next && ++cnt)
		aux = aux->next;
	aux->next = (*tok)->next;
	// **tok is equal to head, we change head then
	if (lex->tok_lst == *tok)
		lex->tok_lst = head;
	else
		prev->next = head;
	free((*tok)->data);
	free(*tok);
	//*tok = head;
	lex->n_toks += cnt;
	*tok = aux->next;
	//for (t_tok *tokk = lex->tok_lst; tokk != NULL; tokk = tokk->next)
	//	printf("p: %p, d: %s\n", (void *)tokk, tokk->data);
	return (0);
}
