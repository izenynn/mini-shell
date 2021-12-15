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
t_tok	*del_hidden_files(t_tok *head)
{
	//t_tok	*tmp;
	t_tok	*aux;
	t_tok	*prev;

	aux = head;
	while (aux)
	{
		if (ft_strncmp((char *)aux->data, ".", 1) == 0)
		{
			if (aux == head)
			{
				del_node(&aux, NULL);
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
	return (head);
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

int	handle_wildcards(t_tok **tok, t_tok *prev, t_lexer *lex)
{
	t_tok	*aux;
	t_tok	*dir;
	char	*wc;

	// TEST -> only get wildcarf if "*"
	if (ft_strncmp((*tok)->data, "*", 2))
		return (0);
	//
	wc = (*tok)->data;
	dir = create_list();
	if (dir == NULL)
		return (1);
	// delete node if first is null
	if (dir->data == NULL)
		del_node(&dir, NULL);
	if (ft_strncmp(wc, ".", 1))
		dir = del_hidden_files(dir);
	// TODO function that for each element of dir checks if there is a wildcard and have a match
	// if no match
	if (dir == NULL)
		return (0);
	// if match
	aux = dir;
	while (aux->next)
		aux = aux->next;
	aux->next = (*tok)->next;
	if (lex->tok_lst == *tok)
		lex->tok_lst = *tok;
	else
		prev->next = dir;
	free((*tok)->data);
	free(*tok);
	*tok = dir;
	return (0);
}
