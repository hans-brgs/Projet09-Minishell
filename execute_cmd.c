/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:27:33 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/11 08:27:33 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
	Child process from the fork.
	IF the open file descriptor is different from the standard input,
	THEN the standard input is refered to the newly created file descriptor.

	IF the open file descriptor is different from the standard output,
	THEN the standard output is refered to the newly created file descriptor.

	ELSE If we are in a process communicating via a pipe,
	then the std output refers to the pipe input, open for writing only.

	Exec the command.
*/
static void	child(t_cmdlist *cmd, t_prompt *p, int *tube)
{
	if (cmd->in != STDIN_FILENO)
	{
		if (dup2(cmd->in, STDIN_FILENO) == -1)
			ft_exit(PERROR, 1, "dup2", cmd);
		close(cmd->in);
	}
	if (cmd->out != STDOUT_FILENO)
	{
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			ft_exit(PERROR, 1, NULL, cmd);
		close(cmd->out);
	}
	else if (cmd->next)
	{
		close(tube[0]);
		if (dup2(tube[1], STDOUT_FILENO) == -1)
			ft_exit(PERROR, 1, NULL, cmd);
	}
	exec_cmd(cmd, p);
}

static void	close_fd(t_cmdlist *cmd, int *tube)
{
	if (cmd->next)
	{
		close(tube[1]);
		if (cmd->next->in == STDIN_FILENO)
			cmd->next->in = tube[0];
	}
	if (cmd->in > 2)
		close(cmd->in);
	if (cmd->out > 2)
		close(cmd->out);
}

/*
	Fork the minishell, to later execute the command in the child process.
*/
static int	exec_fork(t_cmdlist *cmd, t_prompt *p, int *tube)
{
	t_cmdlist	*ptr_cmd;

	ptr_cmd = cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		cmd_free_list(&ptr_cmd);
		return (ft_error(PERROR, 1, NULL, NULL));
	}
	if (cmd->pid == 0)
		child(cmd, p, tube);
	else
		close_fd(cmd, tube);
	return (EXIT_SUCCESS);
}

/*
	Wait for the end of child processes.
	Manage exit codes for child processes.
*/
static void	multiple_wait(t_cmdlist *cmd, t_prompt *p)
{
	int	built_error;

	while (cmd)
	{
		waitpid(cmd->pid, &g_status, 0);
		built_error = builtin_parent(cmd, p);
		if (g_status == 2)
			g_status = 130;
		else if (p->is_exit == 0 && built_error < -1)
			g_status = (g_status >> 8) & 0xff;
		cmd = cmd->next;
	}
}

/*
	Manages the signal of the child processes.
	Browse the commands and create the Pipe IF there are several commands
	AND we are not at the last one.
*/
int	execute(t_cmdlist *cmd, t_prompt *p)
{
	int			tube[2];
	t_cmdlist	*ptr_cmd;

	ptr_cmd = cmd;
	signal(SIGINT, handle_fork_sigint);
	signal(SIGQUIT, handle_fork_sigint);
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(tube) != 0)
				return (ft_error(PERROR, 1, NULL, NULL));
		}
		if (exec_fork(cmd, p, tube) != 0)
			return (EXIT_FAIL);
		cmd = cmd->next;
	}
	multiple_wait(ptr_cmd, p);
	cmd_free_list(&ptr_cmd);
	return (EXIT_SUCCESS);
}
