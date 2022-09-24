/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 07:45:14 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/19 07:45:14 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_prompt *p)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = my_getenv("PWD", p->env, 3);
	pwd = getcwd(NULL, 0);
	my_setenv("OLDPWD", old_pwd, p, 6);
	my_setenv("PWD", pwd, p, 3);
	free(pwd);
}

void	cd_to_home(t_cmdlist *cmd, t_prompt *p)
{
	char	*home;

	home = my_getenv("HOME", p->env, 4);
	if (!home)
	{
		ft_error(HNOSET, 1, "cd", NULL);
		return ;
	}
	if (chdir(home))
	{
		ft_error(PERROR, 1, "cd: ", cmd->full_cmd[1]);
		return ;
	}
	update_pwd(p);
}
