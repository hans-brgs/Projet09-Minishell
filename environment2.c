/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 08:26:47 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/18 08:26:47 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_len_var(char *var)
{
	int		len_var;
	int		len_val;
	char	*getenv;

	len_var = 0;
	if (ft_strchr(var, '='))
	{
		len_var = ft_strlen(var);
		getenv = ft_strchr(var, '=');
		len_val = ft_strlen(getenv);
		len_var = len_var - len_val;
	}
	return (len_var);
}

/*
	Searches the environment for a variable [VAR]
	passed as an argument and returns its value.
*/
char	*my_getenv(char *name, char **env, int len)
{
	int		len_var;
	char	*getenv;
	int		i;

	i = 0;
	while (env[i])
	{
		len_var = check_len_var(env[i]);
		getenv = ft_strchr(env[i], '=');
		if (ft_strnstr(env[i], name, ft_strlen(name)) && len_var == len)
			return (getenv + 1);
		i++;
	}
	return (NULL);
}

static char	*modify_varenv(char *to_modify, char *value, int len)
{
	char	*new_var;
	char	*tmp;

	new_var = ft_substr(to_modify, 0, len + 1);
	tmp = new_var;
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	tmp = to_modify;
	to_modify = new_var;
	free(tmp);
	return (to_modify);
}

static char	*create_varenv(char *var, char *value)
{
	char	*new_var;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

char	**my_setenv(char *var, char *value, t_prompt *p, int len)
{
	char	*new_var;
	int		len_var;
	int		i;

	if (my_getenv(var, p->env, len) == NULL)
	{
		new_var = create_varenv(var, value);
		extend_env(p, new_var);
		free(new_var);
	}
	i = 0;
	while (p->env[i])
	{
		if (ft_strnstr(p->env[i], var, ft_strlen(var)))
		{
			len_var = check_len_var(p->env[i]);
			if (len_var == len)
				p->env[i] = modify_varenv(p->env[i], value, len);
		}
		i++;
	}
	return (p->env);
}
