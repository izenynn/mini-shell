#include <sh.h>

t_list	*fill_list(t_list *env, char **environ)
{
	int	i;

	i = -1;
	while (environ[++i])
		ft_lstadd_back(&env, ft_lstnew(environ[i]));
	return (env);
}
