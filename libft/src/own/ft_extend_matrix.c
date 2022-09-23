/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:44:06 by hbourgeo          #+#    #+#             */
/*   Updated: 2022/09/17 16:44:06 by hbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_extend_matrix(char **mat, char *add)
{
	char	**new_mat;
	int		len;

	len = 0;
	if (!mat || !add)
		return (NULL);
	while (mat && mat[len])
		len++;
	new_mat = ft_calloc(len + 2, sizeof (char *));
	if (!new_mat)
		return (NULL);
	len = 0;
	while (mat[len])
	{
		new_mat[len] = ft_strdup(mat[len]);
		if (!new_mat[len])
		{
			ft_free_array(new_mat);
			return (NULL);
		}
		len++;
	}
	new_mat[len] = ft_strdup(add);
	ft_free_array(mat);
	return (new_mat);
}
