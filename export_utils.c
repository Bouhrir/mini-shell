/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:53:34 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/24 15:53:34 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strncmp_res(char *s1, char *s2, int len)
{
	while(*s1 && *s2 && len)
	{
		if(*s1 != *s2)
			return(1);
		s1++;
		s2++;
		len--;
	}
	if(*s1 == *s2)
		return(0);
	return(1);
}

int invalid_char(char *var, int i)
{
   if (var[i] == '$' || var[i] == '&' ||
		var[i] == '@' || var[i] == '!' ||
		var[i] == ';' || var[i] == ' ' ||
		var[i] == '\"' || var[i] == '\\' ||
		var[i] == '-' ||
		(var[i] == '\\' && var[i + 1] != '_' && !ft_isdigit(var[i + 1])))
		return (1);
	return (0);
}
	
int check_valid_name(char *var)  
{
	int i;
	
	i = 0;

	if(!*var || ft_isdigit(*var) || *var == '=')
		return(0);
	while (var[i] && var[i] != '=')
	{
		if (invalid_char(var, i))
			return(0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;
	i = 0;

	while(src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	return(dest);
}

int invalid_export(t_mini *sh, char *var, char *cmd)
{
    char *print_err;
    char *backup;
    int size;

    size = ft_strlen(var);
    print_err = malloc((sizeof(char) * (size + 28)));
    if (!print_err)
		return (0);
    backup = NULL;
    backup = ft_strjoin(" `", var);
    if (!backup)
        return (free(print_err), 0);
    ft_strcpy(print_err, backup);
    free(backup);
    backup = ft_strjoin(print_err, "': not a valid identifier");
    if (!backup)
        return (free(print_err), 0);
    ft_strcpy(print_err, backup);
    free(backup);
    sh->exit_status = 1;
    ft_error(print_err, cmd);
    free(print_err);
    return (1);
}
