/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:11:26 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/28 19:11:26 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_lvl(t_mini *sh, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], str, len))
			return (ft_strdup(ft_strchr(sh->env[i], '=') + 1));
		i++;
	}
	return (ft_strdup(""));
}

void	get_shlvl(t_mini *sh)
{
	char	*shlvl;
	int		lvl;
	char	*store;

	shlvl = get_lvl(sh, "SHLVL=");
	if (!shlvl)
	{
		free(shlvl);
		shlvl = "0";
	}
	lvl = ft_atoi(shlvl) + 1;
	free(shlvl);
	if (lvl > 65535)
	{
		ft_putendl_fd("warnign: shell level too high, resetting to 1 ...", 2);
		lvl = 1;
	}
	shlvl = ft_itoa(lvl);
	store = ft_strjoin("SHLVL=", shlvl);
	export(sh, store);
	free(store);
	free(shlvl);

}
