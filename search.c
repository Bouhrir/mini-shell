/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:35:02 by amahdiou          #+#    #+#             */
/*   Updated: 2023/08/05 15:35:02 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_binary__in_pwd(t_mini *sh)
{
	struct stat		dir_stat;
	struct dirent	*dirinfo;
	DIR				*dir_str;

	if (stat(".", &dir_stat) != -1 && dir_stat.st_mode & S_IFDIR)
	{
		dir_str = opendir(".");
		if (!dir_str)
			return (NULL);
		dirinfo = readdir(dir_str);
		while (dirinfo)
		{
			if (ft_strcmp(dirinfo->d_name, sh->args[0]))
			{
				closedir(dir_str);
				return (generate_absolute_path(".", sh->first_arg));
			}
			dirinfo++;
			dirinfo = readdir(dir_str);
		}
		closedir(dir_str);
	}
	sh->exit_status = 127;
	ft_error(" No such file or directory", sh->first_arg);
	return (NULL);
}

int	binary_path_ex(t_mini *sh, char *path, char *b_name, struct stat *st)
{
	DIR				*dir_str;
	struct dirent	*dir_info;

	if (stat(path, st) != -1 && st->st_mode & S_IFDIR)
	{
		dir_str = opendir(path);
		if (!dir_str)
			return (0);
		dir_info = readdir(dir_str);
		while (dir_info)
		{
			if (ft_strcmp(dir_info->d_name, b_name))
			{
				sh->binary = 1;
				closedir(dir_str);
				free(b_name);
				return (1);
			}
			dir_info++;
			dir_info = readdir(dir_str);
		}
		closedir(dir_str);
	}
	return (0);
}

char	*search_bin(t_mini *sh, char **path)
{
	int			i;
	struct stat	st;
	char		*b_name;

	i = 0;
	b_name = ft_strdup(sh->args[0]);
	to_lower(b_name);
	while (path[i])
	{
		if (binary_path_ex(sh, path[i], b_name, &st))
			return (generate_absolute_path(path[i], sh->args[0]));
		i++;
	}
	return (NULL);
}
