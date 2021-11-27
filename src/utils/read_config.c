/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:57:38 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/27 14:10:21 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	exec_line(char *line)
{
	t_lexer	lex;
	t_ast	*ast;

	if (lexer_build(line, ft_strlen(line), &lex) == 0)
	{
		lexer_del(&lex);
		return ;
	}
	if (lex.n_toks == 0 || parse(&lex, &ast))
		return ;
	exec_ast(ast);
	lexer_del(&lex);
	ast_del(ast);
}

/* read config from .minishrc */
void	read_config(void)
{
	char	*home;
	char	*file;
	char	*line;
	int		fd;

	home = ft_getenv("HOME");
	if (home == NULL)
		return ;
	file = dir_join(home, RC_FILE);
	free(home);
	if (access(file, R_OK))
	{
		free(file);
		return ;
	}
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return ;
	line = ft_get_next_line(fd);
	while (line)
	{
		exec_line(line);
		free(line);
		line = ft_get_next_line(fd);
	}
	free(line);
}
