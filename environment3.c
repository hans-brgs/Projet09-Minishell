/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:39:28 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/19 19:39:28 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Searches the environment for a variable [VAR]
	passed as an argument and returns its index.
*/
static int	my_getenv_index(char *name, char **env, int len)
{
	int		len_var;
	int		i;

	i = 0;
	while (env[i])
	{
		len_var = check_len_var(env[i]);
		if (ft_strnstr(env[i], name, ft_strlen(name)) && len_var == len)
			return (i);
		i++;
	}
	return (0);
}

static char	*ft_strdup_free(char *env, char **new_mat)
{
	char	*ptr;

	ptr = ft_strdup(env);
	if (!ptr)
	{
		ft_free_array(new_mat);
		return (NULL);
	}
	return (ptr);
}

void	drop_env(t_prompt *p, char *drop)
{
	char	**new_mat;
	char	**ptr;
	int		len;
	int		index;

	new_mat = ft_calloc(ft_matrix_len(p->env), sizeof(char *));
	if (!new_mat)
		return ;
	ptr = new_mat;
	index = my_getenv_index(drop, p->env, ft_strlen(drop));
	len = 0;
	while (p->env[len])
	{
		if (len != index)
		{
			*ptr = ft_strdup_free(p->env[len], new_mat);
			if (!*ptr)
				return ;
			ptr++;
		}
		len++;
	}
	ft_free_array(p->env);
	p->env = new_mat;
}

void	extend_env(t_prompt *p, char *add)
{
	char	**new_mat;
	int		len;

	new_mat = ft_calloc(ft_matrix_len(p->env) + 2, sizeof(char *));
	if (!new_mat)
		return ;
	len = 0;
	while (p->env[len])
	{
		new_mat[len] = ft_strdup_free(p->env[len], new_mat);
		if (!new_mat[len])
			return ;
		len++;
	}
	new_mat[len] = ft_strdup(add);
	ft_free_array(p->env);
	p->env = new_mat;
}
