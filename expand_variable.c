/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:05:40 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/29 15:05:40 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Parses each of the token strings created by the lexer,
	as soon as a dollar is found, 
	it is isolated in a new node of the new @expd list and extended.

	Then the @expd list is convert to a new string token.
*/
static char	*expand(t_tknlist **expd, char *str, char **env, pid_t pid)
{
	char	*new_str;
	char	*sub_str;
	char	*ptr_str;
	int		state;
	int		len;

	len = 0;
	ptr_str = str;
	state = 0;
	while (*str)
	{
		len = expd_token_length(str);
		sub_str = ft_substr(str, 0, len);
		state = is_quoted_dollar(ptr_str, ft_strlen(ptr_str) - ft_strlen(str));
		tkn_insert_end(expd, expand_dollar(sub_str, env, state, pid));
		free(sub_str);
		str = str + len;
	}
	free(ptr_str);
	len = total_strlst_len(*expd);
	new_str = fill_array(len, *expd);
	return (new_str);
}

/*
	Browse token list create by lexer, and expand "$"".
*/
void	line_expander(t_tknlist *tkn, char **env, pid_t pid)
{
	char		*str;
	t_tknlist	*expd;

	expd = NULL;
	while (tkn)
	{
		str = expand(&expd, tkn->str, env, pid);
		tkn_free_list(&expd);
		tkn->str = str;
		tkn = tkn->next;
	}
}
