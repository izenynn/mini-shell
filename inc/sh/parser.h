/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:34 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/16 12:23:52 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*** INCLUDES ***/
# include <sh/lexer.h>
# include <sh/ast.h>

/*** PROTOTYPES ***/
int	parse(t_lexer *lex, t_ast *ast);

#endif
