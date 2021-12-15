/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:49:16 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/15 16:42:03 by dpoveda-         ###   ########.fr       */
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
void	tok_swap(t_tok **head, t_tok *t1, t_tok *t2)
{
	t_tok	*cur1;
	t_tok	*cur2;
	t_tok	*prev1;
	t_tok	*prev2;
	t_tok	*tmp;

	if (t1 == t2)
		return ;
	// search for t1 an keep track of prev
	prev1 = NULL;
	cur1 = *head;
	while (cur1 && cur1 != t1)
	{
		prev1 = cur1;
		cur1 = cur1->next;
	}
	// search for t2 and keep track of prev
	prev2 = NULL;
	cur2 = *head;
	while (cur2 && cur2 != t2)
	{
		prev2 = cur2;
		cur2 = cur2->next;
	}
	// if either t1 or t2 is not present return
	if (cur1 == NULL || cur2 == NULL)
		return ;

	// if t1 is not head
	if (prev1 != NULL)
		prev1->next = cur2;
	// else t2 is new head
	else
		*head = cur2;

	// if t2 is not head
	if (prev2 != NULL)
		prev2->next = cur1;
	// else t1 is new head
	else
		*head = cur2;

	// swap next pointers
	tmp = cur2->next;
	cur2->next = cur1->next;
	cur1->next = tmp;
}

/* compare two tokens data */
int	lowercmp(const char *s1, const char *s2)
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

void	sort_list(t_tok *head)
{
	t_tok	*aux1;
	t_tok	*aux2;

	aux1 = head;
	while (aux1)
	{
		aux2 = aux1->next;
		while (aux2)
		{
			if (lowercmp(aux1->data, aux2->data) > 0)
				tok_swap(&head, aux1, aux2);
			aux2 = aux2->next;
		}
		aux1 = aux1->next;
	}
}

/* read current directory */
void	read_dir(t_tok *dir, DIR *ls, struct dirent *list)
{
	while (list)
	{
		dir->data = ft_strdup(list->d_name);
		dir->type = TOK;
		list = readdir(ls);
		if (list)
			dir->next = (t_tok *)ft_calloc(1, sizeof(t_tok));
		dir = dir->next;
	}
	sort_list(dir);
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
