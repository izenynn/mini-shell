/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:14:11 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/19 11:14:34 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*** PROTOTYPES ***/

int		ft_export(char **new_env);
char	*ft_get_wdir(void);
void	ft_env(void);
int		ft_unset(const char *unset);
void	ft_exit(int exit_code);
int		ft_echo(const char *str, const char *flag);
int		ft_changedir(const char *dir);

#endif
