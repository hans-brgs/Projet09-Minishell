/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 13:58:35 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/06 13:58:35 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmds(t_tknlist *tkn)
{
	int	count;

	count = 1;
	while (tkn)
	{
		if (*tkn->str == '|')
		{
			tkn = tkn->next;
			count++;
		}
		else
			tkn = tkn->next;
	}
	return (count);
}

/*
	Browse until next "|".
*/
t_tknlist	*next_pipe(t_tknlist *tkn)
{
	while (tkn)
	{
		if (tkn->str[0] == '|')
		{
			tkn = tkn->next;
			break ;
		}
		tkn = tkn->next;
	}
	return (tkn);
}

static void	add_cmds(t_cmdlist **cmd, t_tknlist *tkn)
{
	int			count;

	count = count_cmds(tkn);
	while (count > 0)
	{
		cmd_insert_end(cmd);
		count--;
	}
}

/*
	Create a linked list containing : 
		@full_path - a string containing the path to the executable.
		@full_command - An array of strings, containing as the first
			argument the name of the command to be executed and in 
			the following strings the arguments of the command.
		@in - A file descriptor of the command's input.
		@out - A file descriptor of the command's output.
*/
int	parse(t_cmdlist **cmd, t_tknlist *tkn, char **env, pid_t pid)
{
	t_cmdlist	*ptr_cmd;
	t_tknlist	*ptr_tkn;

	ptr_tkn = tkn;
	add_cmds(cmd, tkn);
	ptr_cmd = *cmd;
	while (tkn)
	{
		ptr_cmd->full_cmd = fill_cmd(tkn);
		ptr_cmd->full_path = parse_path(ptr_cmd, env);
		ptr_cmd->in = parse_input(STDIN_FILENO, tkn, env, pid);
		if (ptr_cmd->in == -1)
			return (EXIT_FAIL);
		ptr_cmd->out = parse_output(STDOUT_FILENO, tkn);
		if (ptr_cmd->out == -1)
			return (EXIT_FAIL);
		tkn = next_pipe(tkn);
		ptr_cmd = (ptr_cmd)->next;
	}
	tkn_free_list(&ptr_tkn);
	return (EXIT_SUCCESS);
}
