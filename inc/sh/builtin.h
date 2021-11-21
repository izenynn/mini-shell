/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:49:49 by acostal-          #+#    #+#             */
/*   Updated: 2021/11/20 19:49:51 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*** PROTOTYPES ***/

int		ft_export(char **new_env);
int		ft_get_wdir(const char *n);
void	print_error(const char *dir);
void	ft_env(const char *n);
int		ft_unset(char **unset);
void	ft_exit(char *exit);
int		ft_echo(const char *str, const char *flag);
int		ft_changedir(const char *dir);

#endif
