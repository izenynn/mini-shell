/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:49:49 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/27 11:31:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/** INCLUDES ***/

# include <libft/ft_lst.h>

/*** DATA ***/

typedef struct s_blti	t_blti;

struct s_blti {
	char	*name;
	int		(*f)(char **);
	t_blti	*next;
};

/*** PROTOTYPES ***/

/* built in */
int		ft_export(char **new_env);
int		ft_get_wdir(char **n);
int		ft_env(char **n);
int		ft_changedir(char **dir);
int		ft_echo(char **str);
int		ft_unset(char **unset);
int		ft_exit(char **exit);

/* built in utils */
void	update_var(char *var_name, char *var);
void	free_aux(char *tmp, char *aux);
void	home_handler(t_list *head);
void	set_env(t_list *head);
int		locate_env(t_list *head);
int		goto_home(void);
int		error_handle(char *new_env);
int		set_oldpwd(t_list *head);
int		print_error(const char *dir);
void	try_to_goto_olpwd(void);

#endif
