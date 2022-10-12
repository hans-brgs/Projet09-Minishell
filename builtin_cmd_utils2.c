/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:03:39 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/10/12 09:03:39 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '-')
		return (ft_error(OPT, 1, "unset: ", cmd));
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0 && cmd[i] != '_')
			return (ft_error(INVID, 1, "unset: ", cmd));
		i++;
	}
	return (0);
}

static char	**sort_env(char **env)
{
	int		i;
	int		len;
	char	*tmp;

	len = ft_matrix_len(env);
	while (len != 0)
	{
		i = 0;
		while (i < len - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], 100) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		len--;
	}
	return (env);
}

void	export_print_env(t_prompt *p)
{
	int		i;
	int		len;
	char	*val;
	char	**env;

	env = sort_env(p->env);
	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		len = check_len_var(env[i]);
		val = ft_strchr(env[i], '=');
		write(1, env[i], len);
		write(1, "=\"", 2);
		write(1, val + 1, ft_strlen(val) - 1);
		write(1, "\"\n", 2);
		i++;
	}
}
