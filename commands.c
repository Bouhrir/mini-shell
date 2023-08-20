/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:50:38 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/31 15:50:38 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **set_args(char *str)
{
	char	**args;
	char	*bs;
	int		i;

	if (!str)
		return (NULL);
	args = lexical_analysis(str, ' ');
	i = 0;
	while (args[i])
	{
		bs = bs_parse(args[i], 2);
		free(args[i]);
		args[i] = ft_strdup(bs);
		free(bs);
		i++;
	}
	if (!args)
		return (NULL);
	return (args);
}

void	get_args(t_mini *sh, int i)
{
	char	*exp;

	exp = expansion(sh, sh->commands[i]);
	sh->args = set_args(exp);
	free(exp);
	if (sh->args[0])
		sh->first_arg = ft_strdup(sh->args[0]);
}

char	*append_pwd(char *value)
{
	char	pwd[1024];
	char	*hold;
	int		size;
	int		i;

	size = ft_strlen(value);
	hold = value;
	i = 0;
	if (getcwd(pwd, 1024))
	{
		if (value[0] == ':')
			return (ft_strjoin(pwd, value));
		if (value[size - 1] == ':')
			return (ft_strjoin(value, pwd));
		while (hold[i])
		{
			hold = ft_strchr(hold, ':');
			if (!hold)
				break ;
			if (hold[i + 1] == ':')
				return (ft_strjoin(value, pwd));
			i++;
		}
	}
	return (ft_strdup(value));
}

char	*get_path(t_mini *sh)
{
	char	*value;
	char	*pwd;
	char	**paths;
	char	*backup;

	value = get_env(sh, "PATH");
	if (!value || !ft_strlen(value))
	{
		free(value);
		pwd = search_binary__in_pwd(sh);
	}
	else
	{
		backup = append_pwd(value);
		paths = ft_split(backup, ':');
		pwd = search_bin(sh, paths);
		free(value);
		free(backup);
		free_env(paths);
	}
	if (!access(sh->args[0], X_OK))
			pwd = sh->args[0];
	return (pwd);
}

int exit_permission(t_mini *sh, char *txt, char *path, int exit_stat)
{
	sh->exit_status = exit_stat;
	ft_error(txt, path);
	return (0);
}

int permissions(t_mini __unused *sh, char __unused *path)
{
	struct stat	st;

	if (stat(path, &st) != -1)
	{
		if (st.st_mode & S_IFDIR)
			return (exit_permission(sh, " is a directory", sh->first_arg, 126));
		if (sh->binary == 1 && (!(st.st_mode & S_IXUSR)))
			return (exit_permission(sh, " Permission denied", path, 126));
		else if (sh->binary == 0
			&& (!(st.st_mode & S_IXUSR) || !(st.st_mode & S_IRUSR)))
			return (exit_permission(sh, " Permission denied", path, 126));
		return (1);
	}
	return (0);
}

void exev_args(t_mini *sh)
{
	char	*path;

	if (!builtin_checker(sh))
	{
		path = get_path(sh);
		if (path == NULL)
		{
			printf("minishell: %s: command not found\n", sh->args[0]);
			exit(127);
		}
		if (execve(path, sh->args, sh->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
	}
}

int	child_proc(t_mini *sh, int p[2], int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		if (sh->commands[i + 1])
			dup2(p[1], 1);
		check_redirections(sh);
		exev_args(sh);
		close(p[1]);
		exit(sh->exit_status);
	}
	close(p[1]);
	return (pid);
}

void duplicate_fd(t_help *n)
{
	n->i = 0;
	n->std_in = dup(0);
	n->std_out = dup(1);
}

void duplicate1_fd(t_help *n)
{
	dup2(n->std_in, 0);
	dup2(n->std_out, 1);
}

int count_pipe(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i - 1);
}
void check_pipe(t_mini *sh, t_help *n)
{
	duplicate_fd(n);
	while (n->i <= sh->count)
	{
		get_args(sh, n->i);
		pipe(n->p);
		n->pid = child_proc(sh, n->p, n->i);
		dup2(n->p[0], 0);
		if (sh->commands[n->i])
			waitpid(n->pid, &sh->exit_status, WNOHANG);
		sh->exit_status = WEXITSTATUS(sh->exit_status);
		close(n->p[0]);
		free_env(sh->args);
		if (*sh->first_arg)
			free(sh->first_arg);
		n->i++;
	}
	n->top = wait(&sh->exit_status);
	while (n->top > 0)
	{
		if (n->top < n->pid)
			sh->exit_status = WEXITSTATUS(sh->exit_status);
		n->top = wait(&sh->exit_status);
	}
	sh->exit_status = WEXITSTATUS(sh->exit_status);
	duplicate1_fd(n);
}

void	waitsignal(int sig)
{
	(void)sig;
	signal(SIGINT, waitsignal);
}

char	*update_lastarg(char **arg)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	while (arg[i])
		i++;
	tmp = ft_strchr(arg[i - 1], '=');
	if (tmp)
		*tmp = '\0';
	res = ft_strjoin("_=", arg[i - 1]);
	return (res);
}

void	monitor_cmd(t_mini *sh)
{
	pid_t	pid;
	char	*path;
	char	*backup;

	sh->binary = 0;
	path = get_path(sh);
	pid = fork();
	if (pid == 0)
	{
		if (path == NULL)
		{
			ft_error(" command not found", sh->first_arg);
			exit(127);
		}
		if (execve(path, sh->args, sh->env) == -1)
		{
			perror("minishell: execve");
			exit(126);
		}
	}
	signal(SIGINT, waitsignal);
	waitpid(pid, &sh->exit_status, 0);
	if (WIFEXITED(sh->exit_status))
		sh->exit_status = WEXITSTATUS(sh->exit_status);
	if (sh->exit_status == -1)
		ft_putchar_fd('\n', 1);
	backup = update_lastarg(sh->args);
	export(sh, backup);
	free(backup);
	free(path);
}

void	check_commands(t_mini *sh)
{
	char	*exp;

	exp = expansion(sh, sh->commands[0]);
	sh->args = set_args(exp);
	if (!sh->args[0])
		return ;
	sh->first_arg = ft_strdup(sh->args[0]);
	if (check_redirections(sh) != -1)
	{
		if (sh->args[0] && !(builtin_checker(sh)))
			monitor_cmd(sh);
	}
	free_env(sh->args);
	free(exp);
	free(sh->commands[0]);
	free(sh->first_arg);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
// char **set_args(char *str)
// {
// 	char **args;
// 	char *bs;
// 	int	i;

// 	if (!str)
// 		return (NULL);
// 	args = lexical_analysis(str, ' ');
// 	i = 0;
// 	while (args[i])
// 	{
// 		bs = bs_parse(args[i], 2);
// 		free(args[i]);
// 		args[i] = ft_strdup(bs);
// 		free(bs);
// 		i++;
// 	}
// 	if (!args)
// 		return (NULL);
// 	return (args);
// }
// void get_args(t_mini *sh, int i)
// {
// 	char *exp;

// 	exp = expansion(sh, sh->commands[i]);
// 	sh->args = set_args(exp);
// 	free(exp);
// 	sh->first_arg = ft_strdup(sh->args[0]);
// }

// char *append_pwd(char *value)
// {
// 	char pwd[1024];
// 	char *hold;
// 	int	size;
// 	int	i;

// 	size = ft_strlen(value);
// 	hold = value;
// 	i = 0;
// 	if (getcwd(pwd, 1024))
// 	{
// 		if (value[0] == ':')
// 			return (ft_strjoin(pwd, value));
// 		if (value[size - 1] == ':')
// 			return (ft_strjoin(value, pwd));
// 		while (hold[i])
// 		{
// 			hold = ft_strchr(hold, ':');
// 			if (!hold)
// 				break ;
// 			if (hold[i + 1] == ':')
// 				return (ft_strjoin(value, pwd));
// 			i++;
// 		}
// 	}
// 	return (ft_strdup(value));
// }
// char *get_path(t_mini *sh)
// {
// 	char	*value;
// 	char	*pwd;
// 	char	**paths;
// 	char	*backup;

// 	value = get_env(sh, "PATH");
// 	if (!value || !ft_strlen(value))
// 	{
// 		free(value);
// 		pwd = search_binary__in_pwd(sh);
// 	}
// 	else
// 	{
// 		backup = append_pwd(value);
// 		paths = ft_split(backup, ':');
// 		pwd = search_bin(sh, paths);
// 		free(value);
// 		free(backup);
// 		free_env(paths);
// 	}
// 	return (pwd);
// }
// int exit_permission(t_mini *sh, char *txt, char *path, int exit_stat)
// {
// 	sh->exit_status = exit_stat;
// 	ft_error(txt, path);
// 	return (0);
// }

// int permissions(t_mini *sh, char *path)
// {
// 	struct stat st;

// 	if (stat(path, &st) != -1)
// 	{
// 		if (st.st_mode & S_IFDIR)
// 			return (exit_permission(sh, " is a directory", sh->first_arg, 126));
// 		if (sh->binary == 1 && (!(st.st_mode & S_IXUSR)))
// 			return (exit_permission(sh,  " Permission denied", path, 126));
// 		else if (sh->binary == 0 &&
// 				(!(st.st_mode & S_IXUSR) || !(st.st_mode & S_IRUSR)))
// 			return (exit_permission(sh, " Permission denied", path, 126));
// 		return (1);
// 	}
// 	return (0);
// }

// void exev_args(t_mini *sh)
// {
// 	char *path;

// 	if (!builtin_checker(sh))
// 	{
// 		path = get_path(sh);
// 		if (path)
// 		{
// 			if (*path != '\0')
// 				if (execve(path, sh->args, sh->env) == - 1)
// 				{
// 					ft_error(" command not found", path);
// 					exit(127);
// 				}
// 		}
// 	}
// }
// int child_proc(t_mini *sh, int i, int p[2])
// {
// 	pid_t pid;

// 	if (!(pid = fork()))
// 	{
// 		close(p[0]);
// 		if (sh->commands[i + 1])
// 			dup2(p[1], 1);
// 		check_redirections(sh);
// 		exev_args(sh);
// 		close(p[1]);
// 		exit(sh->exit_status);
// 	}
// 	close(p[1]);
// 	return (pid);
// }

// void check_pipe(t_mini *sh, t_help *n)
// {
// 	n->std_in = dup(0);
// 	n->std_out = dup(1);
// 	n->i = 0;
// 	while (sh->commands[n->i])
// 	{
// 		get_args(sh, n->i);
// 		pipe(n->p);
// 		n->pid = child_proc(sh, n->i, n->p);
// 		dup2(n->p[0], 0);
// 		if (sh->commands[n->i])
// 			waitpid(n->pid, &sh->exit_status, WNOHANG);
// 		sh->exit_status = WEXITSTATUS(sh->exit_status);
// 		close(n->p[0]);
// 		free_env(sh->args);
// 		free(sh->first_arg);
// 		n->i++;
// 	}
// 	while ((n->top = wait(&sh->exit_status)) > 0)
// 		if (n->top < n->pid)
// 			sh->exit_status = WEXITSTATUS(sh->exit_status);
// 	sh->exit_status = WEXITSTATUS(sh->exit_status);
// 	dup2(n->std_in, 0);
// 	dup2(n->std_out, 1);
// }
// void waitsignal(int sig)
// {
// 	(void)sig;
// 	signal(SIGINT, waitsignal);
// }

// char *update_lastarg(char **arg)
// {
// 	char	*res;
// 	char	*tmp;
// 	int 	i;

// 	i = 0;
// 	while (arg[i])
// 		i++;
// 	if ((tmp = ft_strchr(arg[i - 1], '=')))
// 		*tmp = '\0';
// 	res = ft_strjoin("_=", arg[i - 1]);
// 	return (res);
// }
// void monitor_cmd(t_mini *sh)
// {
// 	pid_t	pid;
// 	char	*path;
// 	char	*backup;

// 	sh->binary = 0;
// 	path = get_path(sh);
// 	if (path)
// 	{
// 		if ((pid = fork()) == 0 /*&& permissions(sh, path)*/)
// 		{
// 			execve(path, sh->args, sh->env);
// 			exit(127);
// 		}
// 		signal(SIGINT, waitsignal);
// 		waitpid(pid, &sh->exit_status, 0);
// 		if (WIFEXITED(sh->exit_status))
// 			sh->exit_status = WEXITSTATUS(sh->exit_status);
// 		if (sh->exit_status == -1)
// 			ft_putchar_fd('\n', 1);
// 		backup = update_lastarg(sh->args);
// 		export(sh, backup);
// 		free(backup);
// 	}
// 	free(path);
// }
// void	check_commands(t_mini *sh, t_help *help)
// {
// 	char *exp;

// 	if (*(sh->commands + 1))
// 		check_pipe(sh, help);
// 	else if (sh->commands[0])
// 	{
// 		exp = expansion(sh, sh->commands[0]);
// 		sh->args = set_args(exp);
// 		if (!sh->args[0])
// 			return ;
// 		sh->first_arg = ft_strdup(sh->args[0]);
// 		if (check_redirections(sh) != -1)
// 		{
// 			if (sh->args[0] && !(builtin_checker(sh)))
// 				monitor_cmd(sh);
// 		}
// 		free_env(sh->args);
// 		free(exp);
// 		free(sh->commands[0]);
// 		free(sh->first_arg);
// 	}
// }
