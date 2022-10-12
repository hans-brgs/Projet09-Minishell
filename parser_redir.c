/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:31:21 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/08 11:31:21 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	output_redir(char *str, char *op)
{
	int		output;
	char	*trim;

	output = 1;
	trim = trim_quotes(str);
	if (access(trim, F_OK) == 0)
	{
		if (access(trim, W_OK) == -1)
			ft_error(PERROR, 1, trim, " ");
		else if (ft_strlen(op) == 1)
			output = open(trim, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else if (ft_strlen(op) == 2)
			output = open(trim, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
	else if (ft_strlen(op) == 1)
		output = open(trim, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (ft_strlen(op) == 2)
		output = open(trim, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (output == -1)
		ft_error(NDIR, 1, trim, " ");
	free(trim);
	return (output);
}

/*
	Checks all tokens containing output redirection operators,
	and opens the correct file descriptor.
*/
int	parse_output(int output, t_tknlist *tkn)
{
	char	*op;

	while (tkn && tkn->str[0] != '|')
	{
		op = tkn->str;
		if (op[0] == '>')
		{
			if (output != 1)
				close(output);
			tkn = tkn->next;
			output = output_redir(tkn->str, op);
			if (output == -1)
				return (EXIT_FAIL);
		}
		else
			tkn = tkn->next;
	}
	return (output);
}

/*
	Tries to access the file to be opened.

	Returns an error if the path to the file does not exist,
	or if the user does not have the rights.
*/
static int	input_redir(char *str)
{
	int		input;
	char	*trim;

	input = 0;
	trim = trim_quotes(str);
	if (access(trim, F_OK) == -1 || access(trim, R_OK) == -1)
		ft_error(PERROR, 1, trim, " ");
	else
		input = open(trim, O_RDONLY);
	free(trim);
	return (input);
}

/*
	Checks all tokens containing input redirection operators,
	and opens the correct file descriptor.

	If the redirection operator is "<<", execute the here document.
*/
int	parse_input(int input, t_tknlist *tkn, char **env, pid_t pid)
{
	char	*op;

	while (tkn && tkn->str[0] != '|')
	{
		op = tkn->str;
		tkn = tkn->next;
		if (op[0] == '<' && ft_strlen(op) == 1)
		{
			input = input_redir(tkn->str);
			if (input == -1)
				return (EXIT_FAIL);
		}
		else if (op[0] == '<' && ft_strlen(op) == 2)
		{
			input = heredoc(tkn->str, env, pid);
			if (input == -1)
				return (EXIT_FAIL);
		}
	}
	return (input);
}
