/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:21:40 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/16 16:21:40 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
	If our input is a relative path, then it is of the form "./command".
	OR @excve needs a path of the form "././command" to find the command.
	So we add "./" in front of our input relative path.

	We also check the access to the command file to be executed.
*/
static void	relative_path(t_cmdlist *cmd, t_prompt *p)
{
	char	*tmp;
	char	*num;

	tmp = cmd->full_path;
	cmd->full_path = ft_strjoin("./", tmp);
	free(tmp);
	if (access(cmd->full_path, F_OK) == -1)
		ft_exit(NCMD, 127, cmd->full_cmd[0], cmd);
	else if (access(cmd->full_path, X_OK) == -1)
		ft_exit(NPERM, 126, cmd->full_cmd[0], cmd);
	if (!ft_strncmp(cmd->full_cmd[0], "./minishell", 11)
		&& ft_strlen(cmd->full_cmd[0]) == 11)
	{
		tmp = my_getenv("SHLVL", p->env, 5);
		num = ft_itoa(ft_atoi(tmp) + 1);
		p->env = my_setenv("SHLVL", num, p, 5);
		free(num);
	}
}

/*
	IF our input has at least one "\",
	THEN it is considered by the shell to be a path to an executable.

	We therefore test the existence and permission of the executable file.	
*/
static void	absolute_path(t_cmdlist *cmd)
{
	if (access(cmd->full_path, F_OK) == -1)
		ft_exit(NCMD, 127, cmd->full_cmd[0], cmd);
	else if (access(cmd->full_path, X_OK) == -1)
		ft_exit(NPERM, 126, cmd->full_cmd[0], cmd);
}

/*
	Check if the input is :
	-Builtin
	-Relative Path
	-Absolute Path
	-Command

	AND execute.
*/
void	exec_cmd(t_cmdlist *cmd, t_prompt *p)
{
	int	built;

	built = is_builtin(cmd);
	if (built == 1)
	{
		builtin_child(cmd, p);
		exit(g_status);
	}
	else if (built == 0 && !ft_strncmp(cmd->full_cmd[0], "./", 2))
		relative_path(cmd, p);
	else if (built == 0 && ft_strrchr(cmd->full_cmd[0], '/'))
		absolute_path(cmd);
	if (built == 0 && execve(cmd->full_path, cmd->full_cmd, p->env) == -1)
		ft_exit(NCMD, 127, cmd->full_cmd[0], cmd);
}
