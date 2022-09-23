/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 09:35:06 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/17 09:35:06 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pimp_user(char *user)
{
	char	*tmp;

	if (user)
	{
		if (!ft_strncmp(user, "root", 4))
			user = ft_strjoin(RED, user);
		else
			user = ft_strjoin(GREEN, user);
	}
	else
		user = ft_strdup("\001\033[1;92m\002guest");
	tmp = user;
	user = ft_strjoin(user, "@minishell ");
	free(tmp);
	return (user);
}

static char	*pimp_pwd(char *pwd)
{
	char	*tmp;

	if (pwd)
	{
		pwd = ft_strjoin(BLUE, pwd);
		tmp = pwd;
		pwd = ft_strjoin(tmp, DEFAULT);
		free(tmp);
	}
	else
		pwd = ft_strdup(DEFAULT);
	return (pwd);
}

/*
	Finds the last slash of a PATH.
	Returns the slash + the rest of the string.
*/
char	*find_last_slash(char *path)
{
	if (!path)
		return (NULL);
	while (*path && ft_strchr(path, '/'))
	{
		path = ft_strchr(path, '/');
		path++;
		if (!ft_strchr(path, '/'))
		{
			path--;
			break ;
		}
	}
	return (path);
}

char	*pimp_my_minishell(char **env)
{
	char	*user;
	char	*pwd;
	char	*pimped_minishell;

	user = my_getenv("USER", env, 4);
	user = pimp_user(user);
	pwd = my_getenv("PWD", env, 3);
	pwd = find_last_slash(pwd);
	pwd = pimp_pwd(pwd);
	pimped_minishell = ft_strjoin(user, pwd);
	if (user)
		free(user);
	if (pwd)
		free(pwd);
	return (pimped_minishell);
}

void	message(void)
{
	printf("\n\n\n%s              $$\\           $$\\", GREEN);
	printf("                 $$\\\n");
	printf("              \\__|          \\__|                $$ |\n");
	printf("$$$$$$\\$$$$\\  $$\\ $$$$$$$\\  $$\\        ");
	printf("$$$$$$$\\ $$$$$$$\\\n");
	printf("$$  _$$  _$$\\ $$ |$$  __$$\\ $$ |      $$  _____|$$  __$$\\\n");
	printf("$$ / $$ / $$ |$$ |$$ |  $$ |$$ |      \\$$$$$$\\  $$ |  $$ |\n");
	printf("$$ | $$ | $$ |$$ |$$ |  $$ |$$ |       \\____$$\\ $$ |  $$ |\n");
	printf("$$ | $$ | $$ |$$ |$$ |  $$ |$$ |      $$$$$$$  |$$ |  $$ |\n");
	printf("\\__| \\__| \\__|\\__|\\__|  \\__|\\__|");
	printf("      \\_______/ \\__|  \\__|\n\n%s", GRAY);
	printf("hbourgeo & bkhatib are pleased to present their ");
	printf("version of the minishell.\n");
	printf("Have fun! 😽\n\n\n");
	return ;
}
