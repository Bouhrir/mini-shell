/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:12:16 by amahdiou          #+#    #+#             */
/*   Updated: 2023/08/03 12:12:16 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_key_name(char *s)
{
	int	i;

	i = 0;
	if (!s || ft_isdigit(s[i]) || s[i] == '=')
		return (0);
	while (s[i])
	{
		if (invalid_char(s, i) || s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	unset(t_mini *sh)
{
    int i;

    i = 1;

    while(sh->args[i])
    {
        if(valid_key_name(sh->args[i]))
            env_cleaner(sh->args[i], sh->env);
        else
            invalid_export(sh, sh->args[i], "unset");
        i++;
    }
    return (1);
}