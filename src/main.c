/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/27 14:35:01 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* global var */
t_sh	g_sh;

/* main */
int	main(void)
{
	char	*line;

	init_shell();
	while (1)
	{
		line = read_prompt();
		if (line == NULL || ft_strlen(line) <= 0)
			continue ;
		add_history(line);
		handle_line(line);
		/*if (lexer_build(line, ft_strlen(line), &lex) == 0)
		{
			lexer_del(&lex);
			continue ;
		}
		free(line);
		//print_tokens(&lex);
		if (lex.n_toks == 0 || parse(&lex, &ast))
		{
			lexer_del(&lex);
			ast_del(ast);
			continue ;
		}
		//print_ast(ast, 0);
		exec_ast(ast);
		lexer_del(&lex);
		ast_del(ast);*/
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

//void leaks(void)
//{
//	system("leaks -q minishell");
//}
//
///* main for builtins testing */
//
//int	main(void)
//{
//	extern char	**environ;
//	int i;
//	i = -1;
//	atexit(leaks);
//	while (environ[++i])
//		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(environ[i])));
//	char **export;
//	export = malloc(sizeof(char *) * 3);
//	char **unset;
//	unset = malloc(sizeof(char *) * 3);
//	export[0] = ft_strdup("a=1");
//	export[1] = ft_strdup("b=2");
//	export[2] = NULL;
//	unset[0] = ft_strdup("a");
//	unset[1] = ft_strdup("b");
//	unset[2] = NULL;
//	ft_env();
//	printf("\n\n");
//	ft_export(NULL);
//	printf("\n\n");
//	ft_export(export);
//	ft_env();
//	printf("\n\n");
//	ft_unset(unset);
//	ft_env();
//	printf("%s\n", ft_get_env("PATH"));
//	ft_lstclear(&g_sh.env, free);
//	ft_exit(1);
//}
