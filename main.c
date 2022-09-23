/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:59:36 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/13 13:59:36 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

static void	init(t_prompt *p)
{
	t_tknlist	*tkn;
	t_cmdlist	*cmd;

	cmd = NULL;
	tkn = NULL;
	if (lexer_quotes_spaces(&tkn, p->input))
	{
		free(p->input);
		return ;
	}
	if (lexer_operator(&tkn))
		return ;
	line_expander(tkn, p->env, p->pid);
	if (parse(&cmd, tkn, p->env, p->pid))
	{
		tkn_free_list(&tkn);
		cmd_free_list(&cmd);
		return ;
	}
	if (execute(cmd, p))
	{
		cmd_free_list(&cmd);
		return ;
	}
}

static t_prompt	*init_prompt(char **argv, char **env)
{
	t_prompt	*p;

	p = (t_prompt *)malloc(sizeof(t_prompt));
	p->argv = argv;
	p->env = ft_dup_matrix(env);
	p->env = init_env(argv, p);
	p->input = NULL;
	p->pimped_ms = NULL;
	p->is_exit = 0;
	p->pid = my_getpid();
	return (p);
}

static int	check_input(t_prompt *p)
{
	if (!p->input)
	{
		ft_putstr_fd("exit\n", 2);
		g_status = 0;
		ft_free_array(p->env);
		free(p);
		exit(g_status);
	}
	else if (p->input[0] == '\0')
		return (EXIT_FAIL);
	else
		add_history(p->input);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	*p;

	message();
	p = init_prompt(argv, env);
	while (argc && argv)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		p->pimped_ms = pimp_my_minishell(p->env);
		p->input = readline(p->pimped_ms);
		free(p->pimped_ms);
		if (!check_input(p))
		{
			init(p);
			if (p->is_exit == 1)
			{
				ft_free_array(p->env);
				free(p);
				exit(g_status);
			}
		}
	}
}
