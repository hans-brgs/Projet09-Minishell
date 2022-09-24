/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 10:00:34 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/06 10:00:34 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLIST_H
# define CMDLIST_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_cmdlist
{
	struct s_cmdlist	*prev;
	char				**full_cmd;
	char				*full_path;
	pid_t				pid;
	int					in;
	int					out;
	struct s_cmdlist	*next;
}				t_cmdlist;

/* ----------------------------------------
				   LIST
------------------------------------------*/
t_cmdlist	*cmd_create_node(void);
void		cmd_insert_end(t_cmdlist **start);
int			cmd_list_size(t_cmdlist *cmd);
void		cmd_free_list(t_cmdlist **cmd);
void		cmd_print_list(t_cmdlist *cmd);

#endif