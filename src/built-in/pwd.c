#include <sh.h>

char	*ft_get_wdir(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char *) * PATH_MAX); /*REMEMBER TO FREE THE POINTER RETURNED BY THIS FUNCT*/
	if (getcwd(pwd, PATH_MAX))
		return (pwd);
	else
		return (NULL);
}
