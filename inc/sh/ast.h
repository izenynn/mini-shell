/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:04:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 10:37:44 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/*** DATA ***/

typedef enum e_asttype{
	AST_PIPE =		(1 << 0),
	AST_BG =		(1 << 1),
	AST_SEQ =		(1 << 2),
	AST_REDIR_IN =	(1 << 3),
	AST_REDIR_OUT =	(1 << 4),
	AST_CMD =		(1 << 5),
	AST_ARG =		(1 << 6),
	AST_DATA =		(1 << 7),
}	t_asttype;

typedef struct s_ast	t_ast;

struct s_ast {
	int		type;
	char	*data;
	t_ast	*left;
	t_ast	*right;
};

/*** PROTOTYPES ***/

/* ast_utils.c */
int		ast_gettype(t_ast *ast);
void	ast_del(t_ast *ast);
void	ast_attach(t_ast *root, t_ast *right, t_ast *left);
void	ast_settype(t_ast *ast, t_asttype type);
void	ast_setdata(t_ast *ast, char *data);

#endif
