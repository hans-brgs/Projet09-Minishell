/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:20:54 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/29 15:20:54 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_special_envar(t_cmdlist *cmd, t_prompt *p)
{
	int	i;

	i = 0;
	while (cmd->full_cmd[i])
		i++;
	p->env = my_setenv("_", cmd->full_cmd[i - 1], p, 1);
	return (p->env);
}

/*
 */
char	**init_env(char **argv, t_prompt *p)
{
	char	*str;

	str = getcwd(NULL, 0);
	p->env = my_setenv("PWD", str, p, 3);
	free(str);
	str = my_getenv("SHLVL", p->env, 5);
	if (!str)
		p->env = my_setenv("SHLVL", "1", p, 5);
	str = my_getenv("PATH", p->env, 4);
	if (!str)
		p->env = my_setenv("PATH",
				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", p, 4);
	str = my_getenv("_", p->env, 1);
	if (!str)
		p->env = my_setenv("_", argv[0], p, 1);
	return (p->env);
}
