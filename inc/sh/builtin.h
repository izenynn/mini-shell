/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:49:49 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/22 19:22:36 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <libft/ft_lst.h>

/*** PROTOTYPES ***/

int		ft_export(char **new_env);
int		ft_get_wdir(const char **n);
void	ft_env(const char **n);
int		ft_changedir(const char **dir);
int		ft_echo(const char **str);
int		ft_unset(char **unset);
void	ft_exit(char **exit);
/* Builtins utils */
int		error_handle(char *new_env);
void	try_to_goto_olpwd(void);
int		set_oldpwd(t_list *head);
void	print_error(const char *dir);

#endif
