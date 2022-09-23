/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:41:37 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/08 13:41:37 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

/*
	Expand variable $VAR to her value.
	Equally variable enclosed with single quotes ['  '] .
*/
static char	*expand_heredoc(char *str, char **env, pid_t pid)
{
	t_tknlist	*expd;
	char		*new_str;
	char		*sub_str;
	int			len;

	expd = NULL;
	len = 0;
	while (*str)
	{
		len = expd_token_length(str);
		sub_str = ft_substr(str, 0, len);
		tkn_insert_end(&expd, expand_dollar(sub_str, env, 0, pid));
		free(sub_str);
		str = str + len;
	}
	len = total_strlst_len(expd);
	new_str = fill_array(len, expd);
	tkn_free_list(&expd);
	return (new_str);
}

/*
	This function uses readline in a while loop to read the inputs of a user.
	
	The set of entries is stored in a string, each entry is joined with the
	previous entry by adding a delimiter between each entry.

	If the input is the same as the delimiter, the loop is interrupted.

	The string containing all entries is returned.	
*/
static void	get_here_line(char **str, char *delim, char **env, pid_t pid)
{
	char	*tmp;
	char	*buf;

	g_status = 0;
	while (g_status != 130)
	{
		buf = readline("> ");
		if (!buf)
		{
			ft_heredoc_error(0, delim);
			break ;
		}
		if (!buf || (ft_strncmp(buf, delim, ft_strlen(delim)) == 0
				&& ft_strlen(buf) == ft_strlen(delim)))
			break ;
		buf = expand_heredoc(buf, env, pid);
		tmp = buf;
		buf = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = *str;
		*str = ft_strjoin(tmp, buf);
		free(buf);
		free(tmp);
	}
	free(buf);
}

static void	child_heredoc(char *hrdoc_str, char *delim, char **env, pid_t pid)
{
	char	*trim_delim;

	signal(SIGINT, handle_heredoc);
	signal(SIGQUIT, handle_heredoc);
	trim_delim = trim_quotes(delim);
	get_here_line(&hrdoc_str, trim_delim, env, pid);
	free(trim_delim);
}

/*
	To handle the signals correctly,
	a new process is created (fork) to run the heredoc.
*/
int	heredoc(char *delim, char **env, pid_t pid)
{
	char	*heredoc_str;
	pid_t	pid_heredoc;
	int		fd[2];

	heredoc_str = NULL;
	if (pipe(fd) != 0)
		ft_error(PIPERR, 1, NULL, NULL);
	pid_heredoc = fork();
	if (pid_heredoc == 0)
	{
		child_heredoc(heredoc_str, delim, env, pid);
		write(fd[1], heredoc_str, ft_strlen(heredoc_str));
		free(heredoc_str);
		exit(0);
	}
	waitpid(pid_heredoc, &g_status, 0);
	close(fd[1]);
	g_status = (g_status >> 8) & 0xff;
	if (g_status != 0)
		return (-1);
	return (fd[0]);
}
