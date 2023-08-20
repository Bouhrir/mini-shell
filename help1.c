/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:09:35 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/28 19:09:35 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strdup_env(char **env)
{
	char **tmp;
	int	lenth;
	int	i;

	lenth = 0;
	i = 0;
	while (env[lenth])
		lenth++;
	tmp = malloc(sizeof(char *) * (lenth + 1));
	if (!tmp)
		return NULL;
	while (*env && env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	signal_check(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		signal(sig, signal_check);
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		signal(sig, signal_check);
	}
}

