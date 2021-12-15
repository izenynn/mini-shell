# minishell

## Info

This project aims to recreate most of the bash shell.

- Status: on development
- Result: n/a
- Observations:
	- It is compatible with Linux and Mac OS.
	- It uses `VT100` escape characters (it is a 42 project, and `ncurses` lib was not allowed).

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

## Screenshots

TODO add screenshots :D

##

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/you-didnt-ask-for-this.svg)](https://forthebadge.com)
