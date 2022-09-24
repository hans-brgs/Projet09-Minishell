/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 10:02:31 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/06 10:02:31 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlist	*cmd_create_node(void)
{
	t_cmdlist	*cmd;

	cmd = (t_cmdlist *) malloc(sizeof(t_cmdlist));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->in = 0;
	cmd->out = 1;
	return (cmd);
}

void	cmd_insert_end(t_cmdlist **start)
{
	t_cmdlist	*new_node;
	t_cmdlist	*tmp_lst;

	tmp_lst = *start;
	new_node = cmd_create_node();
	if (*start == NULL)
	{
		*start = new_node;
		return ;
	}
	while (tmp_lst->next != NULL)
	{
		tmp_lst = tmp_lst->next;
	}
	tmp_lst->next = new_node;
	new_node->prev = tmp_lst;
	return ;
}

void	cmd_free_list(t_cmdlist **cmd)
{
	if (!*cmd)
		return ;
	while (*cmd)
	{
		if ((*cmd)->full_cmd)
			ft_free_array((*cmd)->full_cmd);
		if ((*cmd)->full_path)
			free((*cmd)->full_path);
		if ((*cmd)->next)
		{
			*cmd = (*cmd)->next;
			free((*cmd)->prev);
		}
		else
		{
			free(*cmd);
			break ;
		}
	}
	return ;
}

void	cmd_print_list(t_cmdlist *cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd)
	{
		printf("---	CMD %d	---\n", j);
		i = 0;
		while (cmd->full_cmd[i])
		{
			printf("fullcmd[%d] : %s\n", i, cmd->full_cmd[i]);
			i++;
		}
		printf("fullpath : %s\n", cmd->full_path);
		printf("cmd->in : %d   |    cmd->out : %d\n", cmd->in, cmd->out);
		cmd = cmd->next;
		j++;
	}
	return ;
}

int	cmd_list_size(t_cmdlist *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	printf("count : %d\n", count);
	return (count);
}
