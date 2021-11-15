#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "../../libft/inc/libft.h"
void	ft_env(void);
int		ft_unset(char *unset);
int		ft_export(char *new_env);

typedef struct s_global
{
	extern int	g_status;
	char		**env;
}t_global;

t_global	sh;

int	main(void)
{
	extern char	**environ;

	sh.env = environ;
	ft_env();
	printf("\n\n");
	ft_export(NULL);
	printf("\n\n");
	ft_export("a=123");
	ft_env();
	printf("\n\n");
	ft_unset("a");
}
