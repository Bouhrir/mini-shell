/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:28:19 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/31 15:28:19 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_symbolic_link(char *path)
{
	struct stat	box;

	if (!lstat(path, &box))
		return (S_ISLNK(box.st_mode));
	return (0);
}

void	change_loc(t_mini *sh, char *path)
{
	char	*oldclw;
	char	*clw;
	char	*backup;

	oldclw = malloc(1024);
	clw = malloc(1024);
	if (!chdir(path))
	{
		getcwd(clw, 1024);
		backup = get_env(sh, "PWD");
		if (backup)
			get_olddir(sh, backup);
		else
			get_olddir(sh, "");
		free(backup);
		set_path(sh, "PWD=", clw);
	}
	else
		dir_changer_err(sh, path);
	free(oldclw);
	free(clw);
}

int	home_check(t_mini *sh, char *path)
{
	char	*backup;

	free(path);
	path = NULL;
	backup = ft_strdup(sh->first_arg);
	ft_error(" HOME not set", backup);
	free(backup);
	return (1);
}

int	too_args(t_mini *sh)
{
	ft_error(" too many arguments", sh->first_arg);
	return (1);
}

int	cd(t_mini *sh)
{
	char	*path;
	char	*loc;

	loc = sh->args[1];
	if (!loc || !ft_strncmp(loc, "~", 2))
	{
		path = get_env(sh, "HOME");
		if (ft_strcmp(path, ""))
			return (home_check(sh, path));
	}
	else if (!ft_strncmp(loc, ".", 2) || !ft_strncmp(loc, "", 1))
		path = get_env(sh, "PWD");
	else if (!ft_strncmp(loc, "-", 2))
		path = get_env(sh, "OLDPWD");
	else if (sh->args[2])
	{
		path = ft_strdup(loc);
		if (sh->args[3])
			return (too_args(sh));
	}
	else
		path = ft_strdup(loc);
	change_loc(sh, path);
	free(path);
	return (1);
}
