/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 08:34:37 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/18 08:34:37 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	is_builtin(t_cmdlist *cmd)
{
	int	len;

	if (!cmd->full_cmd)
		return (0);
	if (cmd->full_cmd[0] && ft_strrchr(cmd->full_cmd[0], '/'))
		return (0);
	len = ft_strlen(cmd->full_cmd[0]);
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "env", len) && len == 3)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "cd", len) && len == 2)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "export", len) && len == 6)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "unset", len) && len == 5)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "echo", len) && len == 4)
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "exit", len) && len == 4)
		return (1);
	return (0);
}

int	builtin_parent(t_cmdlist *cmd, t_prompt *p)
{
	int	len;

	if (!cmd->full_cmd)
		return (-1);
	if (cmd->full_cmd[0] && ft_strchr(cmd->full_cmd[0], '/'))
		return (-1);
	len = ft_strlen(cmd->full_cmd[0]);
	if (!ft_strncmp(cmd->full_cmd[0], "cd", len) && len == 2)
		return (my_cd(cmd, p));
	if (!ft_strncmp(cmd->full_cmd[0], "export", len) && len == 6)
		return (my_export(cmd, p));
	if (!ft_strncmp(cmd->full_cmd[0], "unset", len) && len == 5)
		return (my_unset(cmd, p));
	if (!ft_strncmp(cmd->full_cmd[0], "exit", len) && len == 4)
		return (my_exit(cmd, p));
	return (-1);
}

int	builtin_child(t_cmdlist *cmd, t_prompt *p)
{
	int	len;

	if (!cmd->full_cmd)
		return (-1);
	if (cmd->full_cmd[0] && ft_strchr(cmd->full_cmd[0], '/'))
		return (-1);
	len = ft_strlen(cmd->full_cmd[0]);
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", len) && len == 3)
		return (my_pwd(cmd));
	if (!ft_strncmp(cmd->full_cmd[0], "env", len) && len == 3)
		return (my_env(cmd, p));
	if (!ft_strncmp(cmd->full_cmd[0], "echo", len) && len == 4)
		return (my_echo(cmd));
	return (-1);
}
