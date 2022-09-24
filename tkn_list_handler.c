/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:06:33 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/07/25 09:06:33 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tknlist	*tkn_create_node(char *str)
{
	t_tknlist	*tkn;

	tkn = (t_tknlist *)malloc(sizeof(t_tknlist));
	if (!tkn)
		return (NULL);
	tkn->next = NULL;
	tkn->prev = NULL;
	tkn->str = str;
	return (tkn);
}

void	tkn_insert_end(t_tknlist **start, char *str)
{
	t_tknlist	*new_node;
	t_tknlist	*tmp_lst;

	tmp_lst = *start;
	new_node = tkn_create_node(str);
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

void	tkn_insert_after(t_tknlist **start, char *str)
{
	t_tknlist	*new_node;
	t_tknlist	*prev_node;

	new_node = tkn_create_node(str);
	if (*start == NULL)
	{
		*start = new_node;
		return ;
	}
	prev_node = *start;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
	new_node->prev = prev_node;
	if (new_node->next != NULL)
	{
		new_node->next->prev = new_node;
	}
}

void	tkn_free_list(t_tknlist **tkn)
{
	t_tknlist	*next;

	if (!(*tkn))
		return ;
	while (*tkn)
	{
		if ((*tkn)->str)
			free((*tkn)->str);
		next = (*tkn)->next;
		free (*tkn);
		*tkn = next;
	}
	return ;
}

int	tkn_len_list(t_tknlist *tkn)
{
	int	len;

	len = 0;
	while (tkn)
	{
		len++;
		tkn = tkn->next;
	}
	return (len);
}
