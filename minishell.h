/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:03:41 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/19 18:07:52 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define DOLLAR 1

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>

typedef struct s_mini
{
	char	*input;
	char	**inst;
	char	**args;
	char	**env;
	char	**commands;
	int		exit_status;
	char	*parse;
	int		exit_prev;
	char	*first_arg;
	int		binary;
	int		count;
	int		test;
}t_mini;

typedef struct s_help
{
	char	*in_quote;
	char	*buff;
	char	*tmp;
	int		i;
	int		start;
	int		end;
	pid_t	pid;
	pid_t	top;
	int		p[2];
	int		std_in;
	int		std_out;
}t_help;

//MAIN
void	shell(char *input, t_mini *sh, t_help *help);
void	rl_replace_line (const char *text, int clear_undo);
// string.h
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);

// HELPER FUNCTION
char	*ft_strdup(char *s1);
char	*ft_strjoin(char	*s1, char	*s2);
char	**strdup_env(char **env);
int		ft_error(char *msg, char *bin);
int		check_after_pipe(char *line, int i);
int		monitor_valide(t_mini *sh, char *input, int sep, int i);
int		check_after_pipe(char *input, int i);
int		invalid_err(t_mini *sh, char *input, int sep, int i);
int		token_priority(char *line, int i, int token);
void	check_commands(t_mini *sh);
int		validate_input(char *input, t_mini *sh);
void	free_env(char **str);
void	signal_check(int sig);
void	get_shlvl(t_mini *sh);
char	*get_lvl(t_mini *sh, char *str);
void	to_lower(char *in);
void	get_olddir(t_mini *sh, char *oldpwd);
void	dir_changer_err(t_mini *sh, char *path);
void	dce(t_mini *sh, char *path, char *print_err);
void	set_path(t_mini *sh, char *path, char *key);
char	*update_lastarg(char **arg);
char	**renew_env(char **var, char **env, int pos);
int		check_spaces(int c);
void	sh_cleaner(t_mini *sh);
void	exev_args(t_mini *sh);
int		whitespaces(char c);
int		valide_redirection(t_mini *sh, char *str);
void	check_pipe(t_mini *sh, t_help *n);
int		count_pipe(char **arg);

//parse
char	*parsing(char *input, t_help *norm);
char	*quotes_parse(char *input, t_help *norm);
char	*parse_join(char *input, char *in_quote, char *buff, int start);
char	*quote_join(char *input, char *in_quote, char *buff, int start);
char	*rm_quotes(char *input, int *start, int *end);
int		bs_previous(char *input, int start);
char	**lexical_analysis(char *input, int c);
char	*endof_quote(char *input, char quote, int start, int *end);
void	quote_error(char quote);
char	*between_quotes(char *input, int start, int end, char quote);
char	*qalloc(char *input, int start, int end, char quote);
char	*expansion(t_mini *sh, char *command);
int		special_chars_count(char *input, int start, int end, char quote);
int		special_char(char c);
int		specialchar_check(char c, int check);
int		bs_previous(char *input, int start);
char	*bs_parse(char *str, int bs_check);
int		check_redirections(t_mini *sh);
char	*escape_bs(char *str, int c);
int		check_heredoc(t_mini *sh);
int		herdoc(t_mini *sh, int i);

// EXEC
int		export(t_mini *sh, char *var);
void	env_cleaner(char *args, char **env);
int		environment(t_mini *sh, char **var);
int		write_env(t_mini *sh);
int		ft_strncmp_res(char *s1, char *s2, int len);
int		invalid_char(char *var, int i);
int		check_valid_name(char *var);
int		invalid_export(t_mini *sh, char *var, char *cmd);
char	*write_q_and_bslash(char *s);
int		count_s_char(char *s);
int		esc_char(char c);
char	*search_binary__in_pwd(t_mini *sh);
int		binary_path_ex(t_mini *sh, char *path, char *b_name, struct stat *st);
int		cmd_exist(t_mini *sh, char *b_name, struct stat stat);
char	*check_cmd(t_mini *sh);
char	*search_bin(t_mini *sh, char **path);
char	*generate_absolute_path(char *path, char *bin);
char	*get_env(t_mini *sh, char *var);
int		builtin_checker(t_mini *sh);
char	*get_path(t_mini *sh);

// BUILTINS

int		cd(t_mini *sh);
int		echo_printer(char **var);
void	to_exit(t_mini *sh);
int		pwd_cmd(void);
int		unset(t_mini *sh);



void print_arr(char **arr);

#endif
