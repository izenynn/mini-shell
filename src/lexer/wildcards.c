//#include <sh.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include "../../libft/inc/libft/ft_mem.h"
#include "../../inc/sh/lexer.h"
#include "../../libft/inc/libft/ft_str.h"
#include "../../libft/inc/libft/ft_lst.h"

t_tok	*del_hidden_files(t_tok *head)
{
	t_tok	*tmp;
	t_tok	*aux;
	t_tok	*prev;

	aux = head;
	while (aux)
	{
		if (ft_strncmp((char *)aux->data, ".", 1) == 0)
		{
			if (aux == head)
			{
				head = aux->next;
				tmp = aux->next;
			}
			else
			{
				tmp = aux->next;
				prev->next = tmp;
			}
			free(aux->data);
			free(aux);
			aux = tmp;
			continue ;
		}
		prev = aux;
		aux = aux->next;
	}
	return (head);
}

/*
 * Delete first 3 nodes because first node is always NULL
 * && delete the . & ..
*/
t_tok	*del_first_nodes(t_tok *list)
{
	t_tok	*aux;

	aux = list;
	list = list->next;
	free(aux->data);
	free(aux);
	return (list);
}

/* Read current dir and fill list with it */
t_tok	*fill_list(void)
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
	list = readdir(ls);
	dir = (t_tok *)ft_calloc(1, sizeof(t_tok));
	if (!dir)
		return (NULL);
	head = dir;
	while (list)
	{
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

int	handle_wildcard(t_tok *wc_tok, t_tok *prev, t_lexer *lex)
{
	t_tok	*aux;
	t_tok	*dir;
	char	*wc;

	// TODO detectar que sea un token de typo data
	wc = wc_tok->data;
	dir = fill_list();
	if (!dir)
		return (1);
	dir = del_first_nodes(dir);
	if (ft_strncmp(wc, ".", 1))
		dir = del_hidden_files(dir);
	aux = dir;
	while (aux)
		aux = aux->next;
	//TODO Si no hay match return 0 (retornar el token recibido);
	aux->next = wc_tok->next;
	if (lex->tok_lst == wc_tok)
		lex->tok_lst = wc_tok;
	else
		prev->next = dir;
	free(wc_tok->data);
	free(wc_tok);
	return (0);
}
