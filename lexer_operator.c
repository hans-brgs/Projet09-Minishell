/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:19:17 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/26 18:19:17 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Check that the operator is quoted.
*/
static char	*quoted_operator(char *str)
{
	char	c;

	c = 0;
	while (*str && !ft_strchr("<|>", *str))
	{
		if (*str == '\'' || *str == '\"')
		{
			c = *str;
			str++;
			while (*str != c)
				str++;
		}
		str++;
	}
	return (str);
}

/*
	Checks whether the string contains an operator.
*/
static int	is_operator(char *str)
{
	str = quoted_operator(str);
	if (ft_strlen(str) > 1)
	{
		if (*str == '>' && *(str + 1) == '>')
			return (1);
		if (*str == '<' && *(str + 1) == '<')
			return (1);
	}
	if (ft_strchr(str, '|'))
		return (1);
	if (ft_strchr(str, '>'))
		return (1);
	if (ft_strchr(str, '<'))
		return (1);
	return (0);
}

/*
	Count the number of characters until an operator is found.
	
	If the string starts with an operator,
	the function counts the length of the successive operators.
*/
static int	token_length(char *str)
{
	int	len;

	len = 0;
	if (*str == '<' || *str == '>' || *str == '|')
	{
		if (*(str + 1) == *str)
			len++;
		return (++len);
	}
	while (*str)
	{
		if (*str == '|' || *str == '<' || *str == '>')
			return (len);
		str++;
		len++;
	}
	return (len);
}

/*
	This function isolates the operators from the words in a linked list.
	The words are isolated from the operators.

	A new node is created either to store an operator,
	OR to store a string of characters.
*/
static t_tknlist	*operator_tkn(t_tknlist *ptr_tkn)
{
	int		len;
	char	*new_str;

	len = 0;
	while (*ptr_tkn->str && is_operator(ptr_tkn->str) == 1)
	{
		len = token_length(ptr_tkn->str);
		if (ptr_tkn->str[len])
		{
			new_str = ft_substr(ptr_tkn->str, 0, len);
			tkn_insert_after(&ptr_tkn, ft_strdup(&ptr_tkn->str[len]));
			free(ptr_tkn->str);
			ptr_tkn->str = new_str;
		}
		ptr_tkn = ptr_tkn->next;
	}
	return (ptr_tkn);
}

/*
	Lexical analyser for operator : "| << >> < >".
	Each token created by the quote and space lexical analyser is
	again analysed by this function.
*/
int	lexer_operator(t_tknlist **tkn)
{
	t_tknlist	*ptr_tkn;

	ptr_tkn = *tkn;
	if (check_operator(tkn) == -1)
	{
		tkn_free_list(tkn);
		return (EXIT_FAIL);
	}
	while (ptr_tkn)
	{
		ptr_tkn = operator_tkn(ptr_tkn);
		ptr_tkn = ptr_tkn->next;
	}
	return (EXIT_SUCCESS);
}
