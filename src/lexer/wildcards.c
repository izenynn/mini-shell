#include <sh.h>
/*#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "../../libft/inc/libft/ft_mem.h"
#include "../../inc/sh/lexer.h"
#include "../../libft/inc/libft/ft_str.h"
#include "../../libft/inc/libft/ft_lst.h"*/

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
	//t_tok	*tmp;
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
				//head = aux->next;
				//tmp = aux->next;
			}
			else
			{
				del_node(&aux, prev);
				//tmp = aux->next;
				//prev->next = tmp;
			}
			//free(aux->data);
			//free(aux);
			//aux = tmp;
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
	t_tok			*dir;
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
	dir = (t_tok *)ft_calloc(1, sizeof(t_tok));
	if (dir == NULL)
		return (NULL);
	head = dir;
	list = readdir(ls);
	while (list)
	{
		//printf("data: %s\n", list->d_name);
		dir->data = ft_strdup(list->d_name);
		dir->type = TOK;
		list = readdir(ls);
		if (list)
			dir->next = (t_tok *)ft_calloc(1, sizeof(t_tok));
		dir = dir->next;
	}
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

	// TEST -> only get wildcarf if "*"
	if (ft_strncmp((*tok)->data, "*", 2))
		return (0);
	//
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
	// if match
	aux = head;
	while (aux->next)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = *tok;
	else
		prev->next = head;
	free((*tok)->data);
	free(*tok);
	*tok = head;
	return (0);
}
