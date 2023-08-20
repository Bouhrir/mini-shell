/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:07:47 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/28 19:07:47 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}

void	sh_cleaner(t_mini *sh)
{
	free_env(sh->commands);
	sh->commands = NULL;
	free_env(sh->args);
	sh->args = NULL;
	free_env(sh->env);
	sh->env = NULL;
}