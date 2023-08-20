/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahdiou <amahdiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:05:30 by amahdiou          #+#    #+#             */
/*   Updated: 2023/07/28 20:05:30 by amahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int     esc_char(char c)
{
	if (c == '$' || c == '\\' || c == '\"')
		return (1);
	return (0);
}

int     count_s_char(char *s)
{
    int counter;
    int i;

    counter = 0;
    i = 0;
    while (s[i])
    {
        if(esc_char(s[i]))
            counter++;
        i++;
    }
    return(counter);
}
char	*write_q_and_bslash(char *s)
{
    char    *box;
    int     i;
    int     j;
    int size;

    i = 0;
    j = 0;
	size = ft_strlen(s);
    box = malloc((sizeof(char) * (size + count_s_char(s)) * 13));
    if(!box)
        return(NULL);
    while(s[i])
    {
        if(esc_char(s[i]))
            box[j] = '\\';
        box[j] = s[i];
        if(s[i] == '=')
            box[++j] = '\"';
        i++;
		j++;
    }
	if (ft_strchr(s, '='))
    	box[j++] = '\"';
    box[j] = '\0';
    return(box);
}