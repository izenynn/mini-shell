/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 13:12:34 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* global var */
t_sh	g_sh;

/************************* TEST FUNC. *************************/

/* spaces between levels */
#define COUNT 10

/* print binary tree in 2d */
/*static void print_ast(t_ast *root, int space)
{
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
	char *type;
	if (ast_gettype(root) & AST_PIPE)
		type = ft_strdup("pipe");
	else if (ast_gettype(root) & AST_BG)
		type = ft_strdup("background");
	else if (ast_gettype(root) & AST_SEQ)
		type = ft_strdup("seq");
	else if (ast_gettype(root) & AST_REDIR_IN)
		type = ft_strdup("redir_in");
	else if (ast_gettype(root) & AST_REDIR_OUT)
		type = ft_strdup("redir_out");
	else if (ast_gettype(root) & AST_CMD)
		type = ft_strdup("cmd");
	else if (ast_gettype(root) & AST_ARG)
		type = ft_strdup("arg");
	else
		type = ft_strdup("error: unknow type");

	// print type and data
	if (root->type & AST_DATA)
		printf("t: %s, s: %s\n", type, root->data);
	else
		printf("t: %s\n", type);

	// process left child
	print_ast(root->left, space);
}*/

/* print tokens */
/*static void print_tokens(t_lexer *lex)
{
	t_tok *tmp;

	tmp = lex->tok_lst;
	while (tmp)
	{
		printf("type: %d, data: %s\n", tmp->type, tmp->data);
		tmp = tmp->next;
	}
}*/

/************************* TEST FUNC. *************************/

/* main */
int	main(void)
{
	char	*line;
	t_lexer	lex;
	t_ast	*ast;

	init_shell();
	// TODO handle signals
	init_prompt();
	while (1)
	{
		line = prompt_read_input();
		if (line == NULL || ft_strlen(line) <= 0)
			continue ;
		if (!lexer_build(line, ft_strlen(line), &lex))
			continue ;
		free(line);
		//print_tokens(&lex);
		if (lex.n_toks == 0 || parse(&lex, &ast))
			continue ;
		//print_ast(ast, 0);
		// TODO execute parse ast
		lexer_del(&lex);
		ast_del(ast);
	}
	return (EXIT_SUCCESS);
}

/* MAIN TO TEST BUILTINS */

//int	main(void)
//{
//	extern char	**environ;
//	char		*line;
//	t_lexer		lex;
//	t_list		*env;
//
//	/* initialise lex */
//	(void)line;
//	env = NULL;
//	lex.tok_lst = NULL;
//	env = fill_list(env, environ);
//	g_sh.env = env;
//	/* initialise shell */
//	init_shell();
//
//	/* initialise terminal */
//	init_prompt();

//	/* minishell loop */
//	/*while (1)
//	{
//		line = prompt_read_input();
// 		prompt_process_input();
//
//		 TESTS
//		printf("\nline: %s\n\n", line);
//
//		/* lexer */
////		lexer_build(line, ft_strlen(line), &lex);
//
////		t_tok *tmp;
////		tmp = lex.tok_lst;
////		while (tmp)
////		{
////			printf("type: %d, data: %s\n", tmp->type, tmp->data);
////			tmp = tmp->next;
////		}
//
////		 TODO parse the tokens into an abstract syntax tree
////
//// 		TODO free all before looping again
////	}
//
//	/* shutdown and cleanup */
//// 		TODO
//	char **xport;
//	xport = malloc(sizeof(char *) * 3);
//	xport[0] = ft_strdup("a=1");
//	xport[1] = ft_strdup("b=2");
//	xport[2] = NULL;
//	ft_export(NULL);
//	printf("\n\n\n\n");
//	ft_export(xport);
//	ft_env();
//	ft_unset("b");
//	ft_env();
//	return (EXIT_SUCCESS);
//}
