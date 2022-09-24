/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:00:01 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/06 09:00:01 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Find the first open quote,
	then find the closing quote and return the string after it.
*/
char	*skip_quotes(char *str)
{
	char	quote;

	if (ft_strchr("\"'",*str))
	{
		quote = *str;
		str++;
		str = ft_strchr(str, quote);
		str++;
	}
	return (str);
}

char	*skip_quotes_to_end(char *str)
{
	char	quote;

	while (*str && ft_strchr("\"'", *str))
	{
		quote = *str;
		str++;
		str = ft_strchr(str, quote);
		str++;
	}
	return (str);
}
