/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:08:46 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/19 12:08:46 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	echo_n_flag(t_cmdlist *cmd, int i)
{
	while (cmd->full_cmd[i])
	{
		ft_putstr_fd(cmd->full_cmd[i], STDOUT_FILENO);
		if (cmd->full_cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

static int	echo_check_flag(t_cmdlist *cmd, int *flag)
{
	int	i;
	int	j;

	i = 1;
	*flag = 0;
	while (cmd->full_cmd[i] && !ft_strncmp(cmd->full_cmd[i], "-n", 2))
	{
		*flag = 1;
		j = 1;
		while (cmd->full_cmd[i][j])
		{
			if (cmd->full_cmd[i][j] != 'n')
			{
				*flag = 0;
				break ;
			}
			j++;
		}
		if (*flag == 0)
			break ;
		i++;
	}
	return (i);
}

void	echo_no_flag(t_cmdlist *cmd)
{
	int	i;

	i = 1;
	while (cmd->full_cmd[i])
	{
		ft_putstr_fd(cmd->full_cmd[i], STDOUT_FILENO);
		if (cmd->full_cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	my_echo(t_cmdlist *cmd)
{
	int	flag;
	int	i;

	g_status = 0;
	if (!cmd->full_cmd[1])
		ft_putstr_fd("\n", STDOUT_FILENO);
	else
	{
		i = echo_check_flag(cmd, &flag);
		if (flag == 0)
			echo_no_flag(cmd);
		else
			echo_n_flag(cmd, i);
	}
	return (EXIT_SUCCESS);
}

int	my_pwd(t_cmdlist *cmd)
{
	char	*pwd;

	g_status = 0;
	pwd = NULL;
	if (cmd->full_cmd[1] && cmd->full_cmd[1][0] == '-')
		return (ft_error(OPT, 1, "pwd: ", cmd->full_cmd[1]));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_error(PERROR, 1, "pwd", NULL));
	else
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd);
	}
	return (EXIT_SUCCESS);
}
