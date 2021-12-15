#include <sh.h>

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
}