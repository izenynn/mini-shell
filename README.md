# minishell

## Contents

- [Info](#markdown-header-info)
- [How to use](#markdown-header-how-to-use)
	- [Clone repo and submodules](#markdown-header-clone-repo-and-submodules)
	- [Linux dependencies](#markdown-header-linux-dependencies)
	- [MAC dependencies](#markdown-header-mac-dependencies)
	- [Compile and execute](#markdown-header-compile-and-execute)
	- [Install](#markdown-header-install)
- [Features](#markdown-header-features)
	- [Built-in commands](#markdown-header-built-in-commands)
- [Aproach](#markdown-header-aproach)
- [Shell grammar](#markdown-header-shell-grammar)
- [Screenshots](#markdown-screenshots)

## Info

This project aims to recreate most of the bash shell.

- Status: on development
- Result: n/a
- Observations:
	- It is compatible with Linux and Mac OS.
	- It does not use `VT100` escape characters.

*developed by: [izenynn](https://github.com/izenynn) and [0xk0sta](https://github.com/0xk0sta)*

## How to use

### Clone repo and submodule

```sh
git clone --recurse-submodules https://github.com/0xk0sta/minishell.git
```

### Linux dependencies

Install readline library:

- On Debian based platforms, like Ubuntu:

```sh
sudo apt install libreadline-dev
```

- Platforms with `yum`, like SUSE:

```sh
yum install readline-devel
```

- For other platform please search for the package name on google, thx :)

### MAC dependencies

- Install readline library:

```sh
brew install readline
```

### Compile and execute

Run `make` (make rules: `all`, `clean`, `fclean` and `re`)

```sh
cd ./minishell && make
```

Execute the `./minishell` binary generated after running `make`

```sh
./minishell
```

### Install

To install minishell in your machine and be able to use it in any directory like any other command, run `make install` (make sure you have the correct access rights).

```sh
sudo make install
```

To change the install directory specify the `BIN_DIR` variable on make

```sh
sudo make install -D 'BIN_DIR=/usr/local/bin'
```

## Features

- Recreates most of the bash shell.
- support for config file `.minishrc` (like bash `.bashrc`).
- comments with `#` (NOTE: `#` must be at the start of the line).
- Pipes `|` works like in bash.
- Redirections `<`, `>`, `<<`, `>>` work like in bash.
- `;`, `&&` and `||` work like in bash.
- Parenthesis: `(` and `)` works with `&&`, `||` and `;` for priorities.
- `$?` works like in bash.
- wildcards `*` and `?` works for the current directory.
- Handle signals: `Ctrl-C`, `Ctrl-D` and `Ctrl-\` like in bash.
- Enviroments variables.
- Arrow keys.
- History (command history).
- Auto-complete with tab key.

### Built-in commands

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Aproach

minishell is formed by 3 components:

1. Lexical analyzer: parse the input line into tokens.

2. Parser: parse tokens into an abstract syntax tree (ast).

3. Executor: execute the commands

To see how it works, go to `src/main/handle_line.c`, uncomment the functions `print_ast` and `print_tokens`, in line 18 and 78, add the following lines to the `handle_line` function and run `make` again:

```diff
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
+	print_tokens(&lex);
 	if (lex.n_toks == 0 || parse(&lex, &ast))
 	{
 		free_all(&lex, ast);
 		return ;
 	}
+	print_ast(ast, 0); printf("---------------------------------\n");
 	if (exec_heredoc(ast) == 0)
 		exec_ast(ast);
 	free_all(&lex, ast);
 }
```

## Shell grammar

```txt
Grammar

<command line>	:	<and or> ';' <command line>
		|	<and or> ';'
		|	<and or>
		;

<and or>	:	<job> && <and or>
		|	<job> || <and or>
		|	<job>
		|	'(' <command line> ')' && <and or>
		|	'(' <command line> ')' || <and or>
		|	'(' <command line> ')'
		;

<job>		:	'(' <command> ')' '|' <job>
		|	    <command>     '|' <job>
		|	'(' <command> ')'
		|	    <command>
		;

<command>	:	<token list>
		;

<token list>	:	<name> <token list>
		|	<token> <token list>
		|	<redir> <token list>
		|	(null)
		;

<redir>		:	<redir in>
		|	<redir out>
		;

<redir in>	:	'<<' <file>
		|	'<' <file>
		;

<redir in>	:	'<<' <file>
 		|	'<' <file>
 		;
```

## Screenshots

TODO add screenshots :D

##

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/you-didnt-ask-for-this.svg)](https://forthebadge.com)
