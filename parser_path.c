/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:30:41 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/08 11:30:41 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Retrieves the value of the $PATH variable.

	Join each directory path of the $PATH variable
	with the function to execute.
	
	When the combination "path + function", matches an executable path
	THEN that total path to the function is returned.
*/
char	*parse_path(t_cmdlist *cmd, char **env)
{
	char	**all_paths;
	char	*folder_path;
	char	*full_path;
	size_t	i;

	i = 0;
	all_paths = ft_split(my_getenv("PATH", env, 4), ':');
	if (!all_paths)
		return (ft_strdup(""));
	while (all_paths[i])
	{
		folder_path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(folder_path, cmd->full_cmd[0]);
		free(folder_path);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_array(all_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(all_paths);
	return (ft_strdup(cmd->full_cmd[0]));
}
