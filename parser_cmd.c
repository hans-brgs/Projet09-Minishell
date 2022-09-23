/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:50:30 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/04 14:50:30 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Count the number of characters until a quote is encountered.
*/
static int	len_btw_quotes(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == c)
			return (len);
		len++;
	}
	return (len);
}

static int	count_quotes(char *str)
{
	int		len;
	char	c;
	char	*str_bis;

	len = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			len++;
			c = *str;
			str++;
			str_bis = ft_strchr(str, c);
			if (str_bis)
			{
				str = str_bis;
				len++;
			}
		}
		str++;
	}
	return (len);
}

/*
	Trims quotes from strings before displaying them in the terminal.
*/
char	*trim_quotes(char *str)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(str) - count_quotes(str) + 1);
	if (!new_str)
		return (NULL);
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			len = len_btw_quotes(str + 1, *str);
			str++;
			while (len--)
				new_str[i++] = *(str++);
			str++;
		}
		else
			new_str[i++] = *str++;
	}
	return (new_str);
}

/*
	Count the number of cmd based on the number of [PIPE: |].
*/
static int	count_cmd_args(t_tknlist *tkn)
{
	int	count;

	count = 0;
	while (tkn && *tkn->str != '|')
	{
		if (*tkn->str && ft_strchr("<>", *tkn->str))
			tkn = tkn->next->next;
		else
		{
			count++;
			tkn = tkn->next;
		}
	}
	return (count);
}

/*
	Fill the array of strings from the tokens
	previously created by the lexer and expander.
*/
char	**fill_cmd(t_tknlist *tkn)
{
	char	**full_cmd;
	int		count;
	int		i;

	i = 0;
	count = count_cmd_args(tkn);
	full_cmd = ft_calloc(count + 1, sizeof(char *));
	if (!full_cmd)
		return (NULL);
	while (tkn && count)
	{
		if (*tkn->str && ft_strchr("<>", tkn->str[0]))
			tkn = tkn->next->next;
		else
		{
			full_cmd[i] = trim_quotes(tkn->str);
			i++;
			tkn = tkn->next;
			count--;
		}
	}
	return (full_cmd);
}
