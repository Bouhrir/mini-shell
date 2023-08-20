/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:03:11 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/28 22:03:11 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_mini *sh, char *var)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], var, size))
			return (ft_strdup(ft_strchr(sh->env[i], '=') + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	env_cleaner(char *args, char **env)
{
	int	i;
	int	size;

	size = ft_strlen(args);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(args, env[i], size))
			break ;
		i++;
	}
	if (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
		while (env[i])
		{
			env[i - 1] = env[i];
			i++;
		}
		env[i - 1] = NULL;
	}
}

void	path_search(char **env)
{
	int		i;
	char	*swap;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			swap = env[i];
			env[i] = env[i + 1];
			env[i + 1] = swap;
			i++;
		}
		i++;
	}
}

int	environment(t_mini *sh, char **var)
{
	int		i;
	char	**env_writer;

	if (sh->args[1])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (1);
	}
	i = 0;
	env_writer = var;
	path_search(env_writer);
	while (env_writer[i])
		ft_putendl_fd(env_writer[i++], 1);
	export(sh, "_=env");
	return (1);
}
