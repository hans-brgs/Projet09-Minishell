/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:27:03 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/26 16:27:03 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static char	*error_str(int err_type)
{
	static char	er[19][100];

	ft_strlcpy(er[QUOTE], ": Closing quote not found\n", 100);
	ft_strlcpy(er[PIPEN], "syntax error near unexpected token `|'\n", 100);
	ft_strlcpy(er[SUPERR], "syntax error near unexpected token `>'\n", 100);
	ft_strlcpy(er[INFERR], "syntax error near unexpected token `<'\n", 100);
	ft_strlcpy(er[DSUPERR], "syntax error near unexpected token `>>'\n", 100);
	ft_strlcpy(er[DINFERR], "syntax error near unexpected token `<<'\n", 100);
	ft_strlcpy(er[NL], "syntax error near unexpected token `newline'\n", 100);
	ft_strlcpy(er[NDIR], ": No such file or directory\n", 100);
	ft_strlcpy(er[NPERM], ": permission denied\n", 100);
	ft_strlcpy(er[PIPERR], "error creating pipe\n", 100);
	ft_strlcpy(er[FORKERR], "fork failed\n", 100);
	ft_strlcpy(er[NCMD], ": command not found\n", 100);
	ft_strlcpy(er[DUPERR], "dup2 failed\n", 100);
	ft_strlcpy(er[OPT], ": invalid option\n", 100);
	ft_strlcpy(er[INVID], ": not a valid identifier\n", 100);
	ft_strlcpy(er[HNOSET], ": HOME not set\n", 100);
	ft_strlcpy(er[TOOARGS], ": too many arguments\n", 100);
	ft_strlcpy(er[NUMARGS], ": numeric argument required\n", 100);
	return (er[err_type]);
}

int	ft_error(int err_type, int status_err, char *str1, char *str2)
{
	g_status = status_err;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	if (err_type == 0)
		perror(str2);
	else
		ft_putstr_fd(str2, 2);
	ft_putstr_fd(error_str(err_type), 2);
	return (EXIT_FAIL);
}

void	ft_exit(int err_type, int status_err, char *str, t_cmdlist *cmd)
{
	if (err_type == 0)
		return ;
	g_status = status_err;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (err_type == 0)
		perror(str);
	else
		ft_putstr_fd(error_str(err_type), 2);
	if (cmd)
	{
		while (cmd->prev)
			cmd = cmd->prev;
		cmd_free_list(&cmd);
	}
	if (err_type != 0)
		exit(g_status);
}

int	ft_heredoc_error(int status_err, char *str)
{
	g_status = status_err;
	ft_putstr_fd("minishell: warning: ", 2);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("')\n", 2);
	return (EXIT_FAIL);
}
