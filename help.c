/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:30:25 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/27 17:30:25 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_spaces(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	**reallocation(char **env, int added)
{
	char	**backup;
	int		i;

	i = 0;
	while (env[i])
		i++;
	backup = malloc((i + added + 1) * sizeof(char *));
	if (!backup)
		return (NULL);
	return (backup);
}
char	**renew_env(char **var, char **env, int pos)
{
	char	**backup;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (env[pos])
		backup = reallocation(env, 0);
	else
		backup = reallocation(env, 1);
	backup[pos] = ft_strdup(*var);
	while (env[i])
	{
		if (j != pos)
			backup[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	if (j != pos)
		backup[j] = NULL;
	else
		backup[i + 1] = NULL;
	return (backup);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	return (1);
}

char	*generate_absolute_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, bin);
	free(tmp);
	return (path);
}