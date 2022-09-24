/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:56:30 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/28 18:56:30 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Catch "<>" && "><" and return an error.
	Our minishell does not handle these operators.	
*/
static int	supinf_error(char *str, char *supinf, int err[3])
{
	char	*ptr_str;
	int		i;

	ptr_str = str;
	while (*ptr_str)
	{
		ptr_str = skip_quotes_to_end(ptr_str);
		if (!*ptr_str)
			return (0);
		if (*ptr_str == supinf[0] && *(ptr_str + 1) == supinf[1])
			return (err[0]);
		i = 0;
		while (ptr_str[i] && ptr_str[i] == supinf[0])
			i++;
		if (i == 3)
			return (err[1]);
		else if (i > 3)
			return (err[2]);
		else
			ptr_str++;
	}
	return (0);
}

/*
	Catch pipe error :
	|| -> error
*/
static int	pipe_error(char *str, t_tknlist *tkn)
{
	char	*ptr_str;
	int		i;
	int		len;

	ptr_str = str;
	len = tkn_len_list(tkn);
	if (*ptr_str && ptr_str[0] == '|' && len == 1)
		return (PIPEN);
	while (*ptr_str)
	{
		ptr_str = skip_quotes_to_end(ptr_str);
		if (!*ptr_str)
			return (0);
		i = 0;
		while (ptr_str[i] && ptr_str[i] == '|')
			i++;
		if (i > 1)
			return (PIPEN);
		else
			ptr_str++;
	}
	return (0);
}

/*
	Return an error if the operator is the last character of the command.
*/
static int	op_before_nl(char *str)
{
	while (*str)
		str++;
	if (*(str - 1) == '|' || *(str - 1) == '>' || *(str - 1) == '<')
		return (NL);
	return (0);
}

/*
	Handle operator error.
*/
int	check_operator(t_tknlist **tkn)
{
	t_tknlist	*ptr;
	int			err;

	err = 0;
	ptr = *tkn;
	while (ptr && err == 0)
	{
		err = pipe_error(ptr->str, *tkn);
		if (err != 0)
			break ;
		err = supinf_error(ptr->str, "><", (int []){INFERR, SUPERR, DSUPERR});
		if (err != 0)
			break ;
		err = supinf_error(ptr->str, "<>", (int []){SUPERR, INFERR, DINFERR});
		if (err != 0)
			break ;
		if (!ptr->next)
			err = op_before_nl(ptr->str);
		ptr = ptr->next;
	}
	if (err != 0)
		return (ft_error(err, 2, NULL, NULL));
	else
		return (0);
}
