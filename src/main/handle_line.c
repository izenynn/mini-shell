/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:25:09 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/16 21:55:02 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/************************* TEST FUNC. *************************/

/* print binary tree in 2d */
/*static void print_ast(t_ast *root, int space)
{
	// spaces between levels
	#define COUNT 10

	int		nd;
	char	*type;

	if (root == NULL)
		return;

	// increase distance between levels
	space += COUNT;

	// process right child
	print_ast(root->right, space);

	// print current node
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	// get ast node type
	nd = ast_gettype(root);
	if (nd & AST_PIPE)
		type = ft_strdup("|");
	else if (nd & AST_SEQ)
		type = ft_strdup(";");
	else if (nd & AST_AND)
		type = ft_strdup("&&");
	else if (nd & AST_OR)
		type = ft_strdup("||");
	else if (nd & AST_REDIR)
		type = ft_strdup("redir");
	else if (nd & AST_RD_TRUNC)
		type = ft_strdup(">");
	else if (nd & AST_RD_APPEND)
		type = ft_strdup(">>");
	else if (nd & AST_RD_HDOC)
		type = ft_strdup("<<");
	else if (nd & AST_RD_INFILE)
		type = ft_strdup("<");
	else if (nd & AST_CMD)
		type = ft_strdup("cmd");
	else if (nd & AST_ARG)
		type = ft_strdup("arg");
	else
		type = ft_strdup("error: unknow type");

	// print type and data
	if (root->type & AST_DATA)
		printf("t: %s, s: %s\n", type, root->data);
	else
		printf("t: %s\n", type);
	free(type);

	// process left child
	print_ast(root->left, space);
}*/

/* print tokens */
static void print_tokens(t_lexer *lex)
{
	t_tok *tmp;

	printf("n_tok: %d\n", lex->n_toks);
	tmp = lex->tok_lst;
	while (tmp)
	{
		printf("type: %d, data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
	printf("------------------------------------\n");
}

/************************* TEST FUNC. *************************/

/* free all before exit */
static void	free_all(t_lexer *lex, t_ast *ast)
{
	if (lex != NULL)
		lexer_del(lex);
	if (ast != NULL)
		ast_del(ast);
}

/* check is line is a commet */
static int	is_comment(char *line)
{
	int	i;

	i = 0;
	while (ft_isblank(line[i]))
		i++;
	if (line[i] == '#')
		return (1);
	return (0);
}

/* handle line -> lexer, parser and exec */
void	handle_line(char *line)
{
	t_lexer	lex;
	t_ast	*ast;

	ast = NULL;
	if (line == NULL || *line == '\0' || *line == '\n' || is_comment(line))
	{
		free(line);
		return ;
	}
	if (lexer_build(line, ft_strlen(line), &lex) == 0)
	{
		write(STDERR_FILENO, "error: syntax error\n", 20);
		free(line);
		lexer_del(&lex);
		return ;
	}
	free(line);
	print_tokens(&lex);
	if (lex.n_toks == 0 || parse(&lex, &ast))
	{
		free_all(&lex, ast);
		return ;
	}
	if (exec_heredoc(ast) == 0)
		exec_ast(ast);
	free_all(&lex, ast);
}
