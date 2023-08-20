/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:28:35 by obouhrir          #+#    #+#             */
/*   Updated: 2023/07/27 17:28:35 by obouhrir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *msg, char *bin)
{
	ft_putstr_fd("minishell: \0", 2);
	if (bin)
	{
		ft_putstr_fd(bin, 2);
		ft_putchar_fd(':', 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}
