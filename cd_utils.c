/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:21:35 by amahdiou          #+#    #+#             */
/*   Updated: 2023/08/03 23:21:35 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_path(t_mini *sh ,char *path, char *key)
{
    int     i;
    int     size;
    char    *var;
    char    **backup;

    size = ft_strlen(key) + 1;
    i = 0;
    while (sh->env[i])
    {
        if(ft_strnstr(sh->env[i], key, size))
        {
            var = ft_strjoin(key, path);
            backup = renew_env(&var, sh->env, i);
            free(var);
            free_env(sh->env);
            sh->env = backup;
        }
        i++;
    }
    
}

void    dce(t_mini *sh, char *path, char *print_err)
{
    char    *err_msg;
    char    *backup;

    path = ft_strjoin(" ", path);
    backup = ft_strdup(path);
    free(path);
    err_msg = ft_strjoin(backup, print_err);
    free(backup);
    ft_error(err_msg, sh->first_arg);
    free(err_msg);
}

void    dir_changer_err(t_mini *sh, char *path)
{
    struct stat d;
    if(stat(path, &d) != -1)
    {
        if(d.st_mode & S_IFDIR)
            dce(sh, path, ": Permission denied");
        else
            ft_error(" not a directory:", sh->first_arg);
    }
    else
        dce(sh, path, ": No such file or directory");
}

void    get_olddir(t_mini *sh,  char *oldpwd)
{
    char    *backup;

    backup = ft_strjoin("OLDPWD=", oldpwd);
    export(sh, backup);
    free(backup);
}
