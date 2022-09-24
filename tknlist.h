/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tknlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:50:50 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/08/04 14:50:50 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKNLIST_H
# define TKNLIST_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_tknlist
{
	struct s_tknlist	*prev;
	char				*str;
	struct s_tknlist	*next;
}				t_tknlist;

/* ----------------------------------------
				   LIST
------------------------------------------*/
t_tknlist	*tkn_create_node(char *str);
void		tkn_insert_end(t_tknlist **start, char *str);
void		tkn_insert_after(t_tknlist **current, char *str);
void		tkn_free_list(t_tknlist **tkn);
int			tkn_len_list(t_tknlist *tkn);

#endif