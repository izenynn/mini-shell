#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_export(char **new_env);
char	*ft_get_wdir(void);
void	ft_env(void);
int		ft_unset(char **unset);
void	ft_exit(int exit_code);
int		ft_echo(const char *str, const char *flag);
int		ft_changedir(const char *dir);
#endif