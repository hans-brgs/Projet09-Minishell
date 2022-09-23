/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:12:05 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/03 10:12:05 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
	Checks whether the dollar ($) is enclosed in a single or double quotes.
*/
int	is_quoted_dollar(char *str, int len)
{
	int		state;
	char	*str2;
	char	*ptr_str;
	char	c;

	ptr_str = str;
	state = 0;
	while (*str)
	{
		if (ft_strchr("'\"", *str) != NULL)
		{
			c = *str;
			str++;
			str2 = ft_strchr(str, c);
			if (str2 != NULL
				&& (&ptr_str[len] >= &str[0] && &str2[0] > &ptr_str[len]))
			{
				if (c == '\'')
					state = 1;
			}
			str = str2;
		}
		str++;
	}
	return (state);
}

/*
	Find the length of the string consisting of "$"" and its associated token.
*/
int	expd_token_length(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
	{	
		i++;
		if (str[1] == '$' || str[1] == '?')
			return (++i);
		while (str[i] && !ft_strchr(SPE_CHAR, str[i]))
			i++;
		return (i);
	}
	while (str[i] && str[i] != '$')
		i++;
	return (i);
}

/*
	ADD the length of each node to get the new size of our token. 
*/
int	total_strlst_len(t_tknlist *expd)
{
	int	len;

	len = 0;
	while (expd)
	{
		len = len + ft_strlen(expd->str);
		expd = expd->next;
	}
	return (len);
}

/*
	Expand the dollar, if :
	$$		->	PID of the minishell
	$?		->	Error code of the most recent command.
	'$USER'	->	THEN the @state = 0, and the variable is not expanded.
	"$USER"	->	The variable is extended to its value,
				by searching in the environment.
*/
char	*expand_dollar(char *str, char **env, int state, pid_t pid)
{
	char	*new_str;

	if (str[0] != '$')
		return (ft_strdup(str));
	else if (str[0] == '$')
	{
		if (ft_strlen(str) == 1)
			return (ft_strdup("$"));
		if (str[1] == '$' && state == 0)
			return (ft_itoa(pid));
		if (str[1] == '?' && state == 0)
			return (ft_itoa(g_status));
		if (state == 0)
		{
			new_str = my_getenv(&str[1], env, ft_strlen(&str[1]));
			if (new_str)
				return (ft_strdup(new_str));
			else
				return (ft_strdup(""));
		}
		if (state == 1)
			return (ft_strdup(str));
	}
	return (NULL);
}

/*
	Conversion of a chained list into a single string.

	The objective is to convert the nodes created during the expansion
	into a new single token.
*/
char	*fill_array(int len, t_tknlist *expd)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (expd)
	{
		i = 0;
		while (expd->str[i])
		{
			new_str[j] = expd->str[i];
			i++;
			j++;
		}
		expd = expd->next;
	}
	return (new_str);
}
