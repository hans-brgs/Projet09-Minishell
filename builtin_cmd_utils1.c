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

int	export_error(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] == '-')
		return (ft_error(OPT, 1, "export: ", cmd));
	else if (cmd[0] == '=')
		return (ft_error(INVID, 1, "export: ", cmd));
	else if (ft_isalpha(cmd[0]) == 0 && cmd[0] != '_')
		return (ft_error(INVID, 1, "export: ", cmd));
	while (cmd[i] && cmd[i] != '=')
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
			return (ft_error(INVID, 1, "export: ", cmd));
		i++;
	}
	return (0);
}

void	export_var(char *cmd, t_prompt *p)
{
	char	*var;
	char	*val;
	int		len;

	len = check_len_var(cmd);
	if (ft_strchr(cmd, '='))
	{
		val = ft_strchr(cmd, '=');
		val = val + 1;
		var = ft_substr(cmd, 0, len);
		my_setenv(var, val, p, len);
		free(var);
	}
}
