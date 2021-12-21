/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:25:09 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 20:46:21 by dpoveda-         ###   ########.fr       */
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
		printf("type: %s, data: %s\n", type, root->data);
	else
		printf("type: %s\n", type);
	free(type);

	// process left child
	print_ast(root->left, space);
}*/

/* print tokens */
/*static void print_tokens(t_lexer *lex)
{
	t_tok *tmp;

	printf("------------------------------------\n");
	printf("n_tok: %d\n", lex->n_toks);
	tmp = lex->tok_lst;
	while (tmp)
	{
		printf("type: %d, data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
	printf("------------------------------------\n");
}*/

/************************* TEST FUNC. *************************/

/* free line if was allocated */
static void	free_line(char *line, t_bool is_alloc)
{
	if (is_alloc == TRUE)
		free(line);
}

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

/* check if line is valid */
static int	check_line(char *line, t_bool is_alloc)
{
	char	*aux;

	if (line == NULL || *line == '\0' || *line == '\n' || is_comment(line))
	{
		free_line(line, is_alloc);
		return (1);
	}
	aux = line;
	while (*aux != '\0')
	{
		if (ft_isblank(*aux) == 0)
			break ;
		aux++;
	}
	if (*aux == '\0')
	{
		free_line(line, is_alloc);
		return (1);
	}
	return (0);
}

/* handle line -> lexer, parser and exec */
void	handle_line(char *line, t_bool is_alloc)
{
	t_lexer	lex;
	t_ast	*ast;
	int		ret;

	ast = NULL;
	if (check_line(line, is_alloc) == 1)
		return ;
	ret = lexer_build(line, ft_strlen(line), &lex);
	if (ret <= 0)
	{
		if (ret == 0 && g_sh.tokdel == FALSE)
			write(STDERR_FILENO, "error: syntax error\n", 20);
		free_line(line, is_alloc);
		lexer_del(&lex);
		return ;
	}
	free_line(line, is_alloc);
	if (lex.n_toks == 0 || parse(&lex, &ast))
	{
		free_all(&lex, ast);
		return ;
	}
	if (exec_heredoc(ast) == 0)
		exec_ast(ast);
	free_all(&lex, ast);
}
