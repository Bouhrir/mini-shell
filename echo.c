/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:13:55 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/29 15:13:55 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_printer(char **var)
{
	int		here;
	int		i;

	i = 0;
	here = 1;
	while (var[i])
	{
		if (!ft_strncmp(var[i], "-n", 2))
		{
			here = 0;
			i++;
		}
		else
			break ;
	}
	while (var[i])
	{
		ft_putstr_fd(var[i], 1);
		if (var[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (here)
		ft_putchar_fd('\n', 1);
	return (1);
}
