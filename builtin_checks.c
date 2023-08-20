/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:30:52 by amahdiou          #+#    #+#             */
/*   Updated: 2023/08/06 14:30:52 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_exec(t_mini *sh)
{
	int	ret;

	ret = 0;
	env_cleaner("_", sh->env);
	ret = export(sh, NULL);
	return (ret);
}

char	*lower(char *input)
{
	int		i;
	char	*output;
	char	*tmp;

	tmp = ft_strdup(input);
	output = ft_calloc(1, ft_strlen(tmp) + 1);
	i = 0;
	while (tmp[i])
	{
		output[i] = ft_tolower(tmp[i]);
		i++;
	}
	free(tmp);
	output[i] = '\0';
	return (output);
}

int	env_exec(t_mini *sh)
{
	char	*low;
	char	*path;
	char	*backup;

	low = lower(sh->args[0]);
	if (ft_strcmp(low, "env"))
	{
		path = get_path(sh);
		backup = ft_strjoin("_=", path);
		free(path);
		export(sh, backup);
		free(backup);
		free(low);
		return (environment(sh, sh->env));
	}
	free(low);
	return (0);
}

int	builtin_checker(t_mini *sh)
{
	int		ret;
	char	*backup;

	ret = 0;
	if (ft_strcmp(sh->args[0], "exit"))
		to_exit(sh);
	else if (ft_strcmp(sh->args[0], "echo"))
		ret = echo_printer(sh->args + 1);
	else if (ft_strcmp(sh->args[0], "cd"))
		ret = cd(sh);
	else if (ft_strcmp(sh->args[0], "pwd"))
		ret = pwd_cmd();
	else if (ft_strcmp(sh->args[0], "export"))
		ret = exp_exec(sh);
	else if (ft_strcmp(sh->args[0], "unset"))
		ret = unset(sh);
	else
		return (env_exec(sh));
	backup = update_lastarg(sh->args);
	export(sh, backup);
	free(backup);
	return (ret);
}
