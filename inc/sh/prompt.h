/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:13:46 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 01:04:57 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

/*** PROTOYPES ***/

/* prompt/prompt.c */
char	*get_prompt(void);

/* prompt/init_prompt.c */
void	init_prompt(void);
void	print_prompt_cwd(void);

#endif
