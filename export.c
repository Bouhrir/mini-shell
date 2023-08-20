/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 16:32:15 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/26 16:32:15 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_env(char **env)
{
	char	**backup_env;
	char	*backup;
	char	*backup1;
	int		i;

	i = 0;
	backup_env = strdup_env(env);
	while (backup_env[i])
	{
		backup = ft_strjoin("declare -x ", backup_env[i]);
		backup1 = write_q_and_bslash(backup);
		free(backup_env[i]);
		free(backup);
		backup_env[i] = backup1;
		i++;
	}
	free(backup1);
	return (backup_env);
}

char **evvv(char __unused **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (ft_strchr(str[i - 1], '='))
		return (str - 1);
	return (str);
}
void	do_export(t_mini *sh, char *var , int j)
{
	int		i;
	int		var_len;
	char	*var_value;
	char	*backup;
	char	**backup_env;

	i = 0;
	if (var)
		var_value = ft_strdup(var);
	else
		var_value = ft_strdup(sh->args[j]);
	backup = ft_strchr(var_value, '=');
	if (!backup)
		var_len = ft_strlen(var_value);
	else
		var_len = ft_strlen(var_value) - ft_strlen(backup);
	while (sh->env[i] && ft_strncmp_res(sh->env[i], var_value, var_len))
		i++;
	backup = ft_strdup(var_value);
	free(var_value);
	var_value = bs_parse(backup, 3);
	free(backup);
	backup_env = renew_env(&var_value, sh->env, i);
	free_env(sh->env);
	free(var_value);
	sh->env = backup_env;
}

int	write_env(t_mini *sh)
{
	char	**backup_env;
	char	**backup_env1;

	backup_env = strdup_env(sh->env);
	backup_env1 = check_env(backup_env);
	environment(sh, backup_env1);
	// free_env(backup_env);
	// free_env(backup_env1);
	return (1);
}

int	alpha(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}
int export(t_mini *sh, char *var)
{
    char *backup;
    int i;
    
    i = 1;
    if (var && check_valid_name(var))
        do_export(sh, var, 0);
    else if (var)
        invalid_export(sh, var, "export");
	else if (!sh->args[i])
		return(write_env(sh));
	else
	{
		while (sh->args[i])
		{
			if (!check_valid_name(sh->args[i]))
				invalid_export(sh,sh->args[i], "export");
			else if ((backup = ft_strchr(sh->args[i], '=')) && backup != sh->args[i])
				do_export(sh, var, i);
			else if (alpha(sh->args[i]) && !(ft_strchr(sh->args[i], '=')))
			{
				do_export(sh, sh->args[i], i);
			}
			i++;
		}
	}
	return (1);
}
