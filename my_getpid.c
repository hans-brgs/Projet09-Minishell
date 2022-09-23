/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_getpid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:08:20 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/16 14:08:20 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function forks the minishell, gets the PID of the child process and
	subtracts 1 from it to get the PID of the parent,
	i.e. the PID of the minishell.
*/
int	my_getpid(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit(FORKERR, 1, NULL, NULL);
	if (!pid)
		exit(1);
	waitpid(pid, NULL, 0);
	pid = pid - 1;
	return (pid);
}
