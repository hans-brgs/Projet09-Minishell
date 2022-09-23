/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:24:32 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/25 11:24:32 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_spaces(char *s)
{
	while (*s)
	{
		if (!ft_strchr("\t \n\v\f\r", *s))
			return (0);
		s++;
	}
	return (1);
}

/*
	Check if a string is enclosed with quotes.
*/
static int	closed_quotes(char *s)
{
	char	c;

	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			c = *s;
			s++;
			s = ft_strchr(s, c);
			if (!s)
				return (EXIT_FAIL);
		}
		s++;
	}
	return (EXIT_SUCCESS);
}

/*
	Computes the length of strings that do not contain spaces.
	Or the length of the string between quotes, including spaces.
*/
static int	token_len(char *str)
{
	int		len;
	char	c;

	len = 0;
	while (str[len] && str[len] != ' ')
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			c = str[len];
			len++;
			while (str[len] && str[len] != c)
				len++;
		}
		len++;
	}
	return (len);
}

/*
	Lexer analyser for "[SPACE] [QUOTE : " ']"
	- Check for unclosed QUOTE.

	- String are split by [SPACE] & stores each space-separated
	string in a new node of a linked list.

	- Strings containing spaces but enclosed in quotes are not split.
*/
int	lexer_quotes_spaces(t_tknlist **tkn, char *str)
{
	int	len;

	if (only_spaces(str))
		return (EXIT_FAILURE);
	if (closed_quotes(str) == -1)
		return (ft_error(QUOTE, 1, strerror(1), NULL));
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (!*str)
			break ;
		len = token_len(str);
		tkn_insert_end(tkn, ft_substr(str, 0, len));
		str = str + len;
	}
	return (EXIT_SUCCESS);
}
