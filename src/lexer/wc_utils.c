/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:49:16 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 17:52:16 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* locate node and get previous node */
/*void	tok_locate(t_tok **head, t_tok **cur, t_tok **prev, t_tok *match)
{
	*prev = NULL;
	*cur = *head;
	while(*cur && *cur != match)
	{
		*prev = *cur;
		*cur = (*cur)->next;
	}
}*/

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

	while (*s1 != '\0' && *s2 != '\0'&& ft_tolower(*s1) == ft_tolower(*s2))
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
			aux->next = (t_tok *)ft_calloc(1, sizeof(t_tok));
		aux = aux->next;
	}
	sort_list(head);
}

/*int main() {
	char *s1;
	char *s2;

	s1 = ft_strdup("abc");
	s2 = ft_strdup("Acd");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("Abc");
	s2 = ft_strdup("acd");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("Abc");
	s2 = ft_strdup("Bcd");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("bbc");
	s2 = ft_strdup("acd");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	// --------------------------------------

	s1 = ft_strdup(".");
	s2 = ft_strdup("..");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("..");
	s2 = ft_strdup(".cache");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("libft");
	s2 = ft_strdup("CHANGELOG.md");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("~");
	s2 = ft_strdup("\\");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("~");
	s2 = ft_strdup("libft");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

	s1 = ft_strdup("\\");
	s2 = ft_strdup("libft");
	printf("s1: %s\ns2: %s\nres: %d\n\n", s1, s2, lowercmp(s1, s2));
	free(s1);
	free(s2);

}*/

/*int main() {
	t_tok **head;

	t_tok *t1;
	t_tok *t2;
	t_tok *t3;
	t_tok *t4;
	t_tok *t5;

	t1 = (t_tok *)malloc(sizeof(t_tok));
	t2 = (t_tok *)malloc(sizeof(t_tok));
	t3 = (t_tok *)malloc(sizeof(t_tok));
	t4 = (t_tok *)malloc(sizeof(t_tok));
	t5 = (t_tok *)malloc(sizeof(t_tok));

	t1->data = ft_strdup("token 1");
	t2->data = ft_strdup("token 2");
	t3->data = ft_strdup("token 3");
	t4->data = ft_strdup("token 4");
	t5->data = ft_strdup("token 5");

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	t5->next = NULL;

	head = (t_tok **)malloc(sizeof(t_tok *));
	*head = t1;

	printf("HEAD\np: %p, d: %s\n\n", (void *)*head, (*head)->data);

	printf("TOKEN LIST\n");
	for (t_tok *aux = *head; aux != NULL; aux = aux->next)
	{
		printf("p: %p, d: %s\n\n", (void *)aux, aux->data);
	}

	// -----------------------------------------------

	tok_swap(head, t4, t5);

	printf("---------------------------\n");

	printf("HEAD\np: %p, d: %s\n\n", (void *)*head, (*head)->data);

	printf("TOKEN LIST\n");
	for (t_tok *aux = *head; aux != NULL; aux = aux->next)
	{
		printf("p: %p, d: %s\n\n", (void *)aux, aux->data);
	}

	// -----------------------------------------------

	free(t1->data);
	free(t2->data);
	free(t3->data);
	free(t4->data);
	free(t5->data);

	free(t1);
	free(t2);
	free(t3);
	free(t4);
	free(t5);

	free(head);
}*/
